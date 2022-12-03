//
// Created by Максим Лейхнер on 03.12.2022.
//

#ifndef MOVIELIBRARY_DATATYPES_H
#define MOVIELIBRARY_DATATYPES_H

#include <string>

class Human;

class Searchable{
public:
    virtual float getRelevanceIndex(std::string query) = 0;
};

class Movie : public Searchable{
public:
    Movie(const std::string& title, int year){
        this->title = title;
        this->year = year;
    }

    void setSynopsis(const std::string& value){
        this->synopsis = value;
    }
    std::string getSynopsis(){
        return this->synopsis;
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

    void setDirector(Human * director){
        this->director = director;
    }

    Human * getDirector(){
        return this->director;
    }

    void addActor(Human * actor){
        this->actors.add(actor);
    }

    List<Human> & getActors(){
        return actors;
    }

private:
    std::string title;
    std::string synopsis;
    int year;
    std::string countries;
    Human * director = nullptr;
    int budgetUSD = 0;
    int boxOfficeUSD = 0;
    float rate = 0.0f;
    List<Human> actors;
};

class Human : public Searchable{
public:
    Human(const std::string& name, const std::string& surname){
        this->name = name;
        this->surname = surname;
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

    void setBio(const std::string& text){
        this->bio = text;
    }

    std::string getBio(){
        return this->bio;
    }

    void addMovie(Movie * movie){
        movie->setDirector(this);
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

private:
    std::string name;
    std::string surname;
    std::string bio;
    List<Movie> movies;
};

#endif //MOVIELIBRARY_DATATYPES_H
