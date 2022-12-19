#include "SFML/Graphics.hpp"
#include "DataArrays.h"
#include "DataTypes.h"
#include "MoviesException.h"

using namespace sf;

class MovieScroller{
public:
    MovieScroller(int posterWidth, int posterHeight){
        this->posterSize = Vector2i(posterWidth, posterHeight);
    }

    void setGap(int value){
        this->gap = value;
    }

    void setPosition(int x, int y){
        this->position = Vector2i(x, y);
    }

    void addMovie(Movie * movie){
        this->movies.add(movie);
        auto poster = new RectangleShape();
        poster->setSize(Vector2f(posterSize));
        poster->setTexture(movie->getPoster());
        this->posters.add(poster);
    }

    void drawTo(RenderWindow & window){
        for(int i = 0; i < numberOfVisible; i++){
            auto currentPosition = Vector2i(this->position.x + (offset % (gap + posterSize.x)) + (this->posterSize.x + this->gap) * i, this->position.y);
            posters[i - dataOffset]->setPosition(Vector2f(currentPosition));
            window.draw(*posters[i - dataOffset]);
        }
        for(int i = 0; i < movieInfo.getSize(); i++){
            window.draw(*movieInfo[i]);
        }
    }

    bool isMouseOver(sf::RenderWindow &window) const {
        int mouseY = sf::Mouse::getPosition(window).y;
        int btnPosY = position.y;
        int btnYPosHeight = position.y + posterSize.y;

        if ( mouseY < btnYPosHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }

    void onDrag(int mouseXPos){
        if(this->dragging){
            offset += mouseXPos - previousMouseXPosition;
            if (offset > 0) offset = 0;
            previousMouseXPosition = mouseXPos;
            dataOffset = offset / (int)(gap + posterSize.x);
        }
    }

    void setDragging(bool state, int mouseXPos = 0){
        this->dragging = state;
        if (state) initialX = mouseXPos;
        else{
            if(initialX == previousMouseXPosition){
                tap(initialX);
            }
        }
        previousMouseXPosition = mouseXPos;
    }

    void clear(){
        while (true){
            try{
                this->movies.pop();
                this->posters.pop();
            }
            catch (bad_addr_exception e){
                break;
            }
        }

    }

private:

    void tap(int mouseXPos){
        int index = (mouseXPos - position.x - offset % (gap + posterSize.x)) / (posterSize.x + gap) - dataOffset;
        renderMovieInfo(movies.operator[](index));
    }

    void renderMovieInfo(Movie * movie, float uiScale = 1.4f){
        movieInfo.clear();
        auto poster = new sf::RectangleShape;
        poster->setSize(sf::Vector2f(429 * uiScale, 614 * uiScale));
        poster->setTexture(movie->getPoster());
        poster->setPosition(sf::Vector2f(86 * uiScale, 317 * uiScale));
        movieInfo.add(poster);
    }

    Vector2i posterSize;
    int gap = 0;
    int offset = 0;
    int dataOffset = 0;
    bool dragging = false;
    Vector2i position;
    int numberOfVisible = 11;
    CircularList<Movie> movies;
    CircularList<RectangleShape> posters;
    int previousMouseXPosition = 0;
    int initialX = 0;

    List<sf::Drawable> movieInfo;
};