#include "json.hpp"
#include "DataArrays.h"
#include "DataTypes.h"
#include "jsonHandler.h"
#include "Functions.h"
#include "SFML/Graphics.hpp"
#include "TextButton.h"
#include "TextBox.h"
#include "movieScroller.h"
using json = nlohmann::json;

#define UI_SCALE 1.4f

int main() {

    //Настройки окна программы
    sf::String title = L"Фильмотека";
    const int windowHeight = (int)(1024 * UI_SCALE);
    const int windowWidth = (int)(1440 * UI_SCALE);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    //Вызов окна
    sf::RenderWindow window(
            sf::VideoMode(
                    windowWidth,
                    windowHeight),
                    sf::String::fromUtf32(
                            title.begin(),
                            title.end()),
                            sf::Style::Close,
                            settings);
    window.setFramerateLimit(60);

    //Генерируем текстуру фона
    sf::Texture backgroundTexture = createBackgroundTexture(
            windowWidth,
            windowHeight,
            sf::Color(65, 65, 65));
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(windowWidth, windowHeight));
    background.setTexture(&backgroundTexture);

    //Подключаем файлы шрифтов
    sf::Font helveticaNeue_Light;
    sf::Font helveticaNeue_Regular;
    sf::Font helveticaNeue_Medium;
    sf::Font helveticaNeue_Bold;
    if(!(helveticaNeue_Light.loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/fonts/HelveticaNeueCyr-Light.ttf") &&
            helveticaNeue_Regular.loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/fonts/HelveticaNeueCyr-Roman.ttf") &&
            helveticaNeue_Medium.loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/fonts/HelveticaNeueCyr-Medium.ttf") &&
            helveticaNeue_Bold.loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/fonts/HelveticaNeueCyr-Bold.ttf"))){
        throw res_file_not_loaded();
    }

    //Подключаем файлы текстур
    sf::Texture searchTexture;
    if(!(searchTexture.loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/textures/textBox_texture.png"))){
        throw res_file_not_loaded();
    }

    //Загружаем курсоры мыши из системы
    sf::Cursor arrowCursor;
    sf::Cursor handCursor;
    sf::Cursor textCursor;
    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);
    textCursor.loadFromSystem(sf::Cursor::Text);

    //Инициализируем элементы интерфейса
    TextBox searchBox(&searchTexture, 49 * UI_SCALE);
    searchBox.setPosition(sf::Vector2f(992 * UI_SCALE, 38 * UI_SCALE));
    searchBox.setFont(helveticaNeue_Medium);
    searchBox.setArrowCursor(&arrowCursor);
    searchBox.setTextCursor(&textCursor);

    TextButton searchType(&helveticaNeue_Bold, 49 * UI_SCALE);
    searchType.setPosition(sf::Vector2f(86 * UI_SCALE, 38 * UI_SCALE));
    searchType.setText(L"Фильмы");
    searchType.setArrowCursor(&arrowCursor);
    searchType.setHandCursor(&handCursor);

    //Загружаем базу данных из файла
    List<Human> * database;
    database = deserializeJSON(loadFromFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/input.json"));

    MovieScroller searchResults(123 * UI_SCALE, 176 * UI_SCALE);
    searchResults.setPosition(86 * UI_SCALE, 107 * UI_SCALE);
    searchResults.setGap(18 * UI_SCALE);
    for(int i = 0; i < database->getSize(); i++){
        for(int j = 0; j < database->operator[](i)->getMovies().getSize(); j++){
            searchResults.addMovie(database->operator[](i)->getMovies().operator[](j));
        }
    }



    //Обновление кадра
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(searchResults.isMouseOver(window)) searchResults.setDragging(true, sf::Mouse::getPosition(window).x);
                    else if(searchBox.isMouseOver(window)){
                        searchBox.setSelected(true);
                    }
                    else{
                        searchBox.setSelected(false);
                    }
                    break;
                case sf::Event::TextEntered:
                    searchBox.typedOn(event);
                    break;
                case sf::Event::MouseButtonReleased:
                    searchResults.setDragging(false);
                    break;
                default:
                    break;
            }
        }

        window.clear();
        window.draw(background);
        searchBox.drawTo(window);
        //window.draw(films);
        searchType.onHover(window, searchType.isMouseOver(window));
        searchBox.onHover(window, searchBox.isMouseOver(window));
        searchType.drawTo(window);
        searchResults.onDrag(sf::Mouse::getPosition(window).x);
        searchResults.drawTo(window);
        window.display();
    }

    writeToFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/output.json", serializeJSON(database).dump(4));
    return 0;
}
