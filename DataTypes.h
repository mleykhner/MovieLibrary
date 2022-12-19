//
// Created by Максим Лейхнер on 03.12.2022.
//

#ifndef MOVIELIBRARY_DATATYPES_H
#define MOVIELIBRARY_DATATYPES_H

#include <string>
#include "SFML/Graphics.hpp"

#define NO_IMAGE "/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/images/no_image.png"

class Human;

class Searchable{
public:
    virtual float getRelevanceIndex(std::string query) = 0;
};

class Movie : public Searchable{
public:
    Movie(const std::string& title, int year, int id){
        this->title = title;
        this->year = year;
        this->id = id;
    }

    void setSynopsis(const std::string& value){
        this->synopsis = value;
    }
    std::string getSynopsis(){
        return this->synopsis;
    }

    int getId() const {
        return this->id;
    }

    void setCountries(const std::string& value){
        this->countries = value;
    }
    std::string getCountries(){
        return this->countries;
    }

    void setBudget(int USD){
        this->budgetUSD = USD;
    }
    int getBudgetUSD() const{
        return this->budgetUSD;
    }

    void setBoxOffice(int USD){
        this->boxOfficeUSD = USD;
    }
    int getBoxOfficeUSD() const{
        return this->boxOfficeUSD;
    }

    void setRate(float value){
        this->rate = value;
    }

    float getRate() const{
        return this->rate;
    }

    std::string getTitle(){
        return this->title;
    }

    int getYear() const{
        return this->year;
    }

    float getRelevanceIndex(std::string query) override{
        //TODO: Реализовать
        return 0.0f;
    }

    void setDirector(Human * person){
        this->director = person;
    }

    Human * getDirector(){
        return this->director;
    }

    void addActor(Human * actor){
        this->actors.add(actor);
    }

    CircularList<Human> & getActors(){
        return actors;
    }

    sf::Texture * getPoster(){
        return &this->poster;
    }

    std::string getPosterPath(){
        return this->posterPath;
    }

    bool setPoster(std::string path){
        if(path.empty()){
            return this->poster.loadFromFile(NO_IMAGE);
        }
        this->posterPath = path;
        return this->poster.loadFromFile(path);
    }

private:
    int id;
    std::string title;
    std::string synopsis;
    int year;
    std::string countries;
    Human * director = nullptr;
    int budgetUSD = 0;
    int boxOfficeUSD = 0;
    float rate = 0.0f;
    CircularList<Human> actors;
    sf::Texture poster;
    std::string posterPath;
};

class Human : public Searchable{
public:
    Human(const std::string& name, const std::string& surname, int id){
        this->name = name;
        this->surname = surname;
        this->id = id;
    }

    std::string getName(){
        return this->name;
    }

    std::string getSurname(){
        return this->surname;
    }

    std::string getFullName(){
        return this->name + " " + this->surname;
    }

    int getId() const{
        return this->id;
    }

    void setBio(const std::string& text){
        this->bio = text;
    }

    std::string getBio(){
        return this->bio;
    }

    void addMovie(Movie * movie){
        for(int i = 0; i < this->movies.getSize(); i++){
            if(movie == this->movies[i]) return;
        }
        this->movies.add(movie);
    }

    List<Movie> & getMovies(){
        return movies;
    }

    Movie * getMovie(int index){
        return movies[index];
    }

    float getRelevanceIndex(std::string query) override{
        //TODO: Реализовать
        return 0.0f;
    }

    bool isDirector() const{
        return this->director;
    }

    void setDirector(bool state) {
        this->director = state;
    }

    sf::Texture * getPortrait(){
        return &this->portrait;
    }

    std::string getPortraitPath(){
        return this->portraitPath;
    }

    bool setPortrait(std::string path){
        if(path.empty()){
            return this->portrait.loadFromFile(NO_IMAGE);
        }
        this->portraitPath = path;
        return this->portrait.loadFromFile(path);
    }

private:
    int id;
    std::string name;
    std::string surname;
    std::string bio;
    bool director = false;
    List<Movie> movies;
    sf::Texture portrait;
    std::string portraitPath;
};

#endif //MOVIELIBRARY_DATATYPES_H
