//
// Created by Максим Лейхнер on 04.12.2022.
//
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
#include "List.h"
#include "DataTypes.h"

List<Human> * parseJSON(const std::string& query){
    json newObject = json::parse(query);
    auto * result = new List<Human>;
    for (auto& director : newObject)
    {
        auto * newDirector = new Human(director["name"], director["surname"]);
        newDirector->setBio(director["bio"].is_null() ? "" : director["bio"]);
        for(auto& movie : director["movies"]){
            auto * newMovie = new Movie(movie["title"], (int)movie["year"]);
            newMovie->setSynopsis(movie["synopsis"].is_null() ? "" : movie["synopsis"]);
            newMovie->setBudget(movie["budgetUSD"].is_null() ? 0 : (int)movie["budgetUSD"]);
            newMovie->setBoxOffice(movie["boxOfficeUSD"].is_null() ? 0 : (int)movie["boxOfficeUSD"]);
            newMovie->setCountries(movie["countries"].is_null() ? "" : movie["countries"]);
            newMovie->setRate(movie["rate"].is_null() ? 0 : (float)movie["rate"]);
            newDirector->addMovie(newMovie);
        }
        result->add(newDirector);
    }
    return result;
}

json serializeJSON(List<Human> directors){
        json j = json::array();

    for(int i = 0; i < directors.getSize(); i++){
        std::cout << i + 1 << ". " << directors[i]->getFullName() << std::endl;
        json director;
        director["name"] = directors[i]->getName();
        director["surname"] = directors[i]->getSurname();
        director["bio"] = directors[i]->getBio();
        director["movies"] = json::array();
        auto movies = directors[i]->getMovies();
        for(int j = 0; j < movies.getSize(); j++){
            std::cout << "\t" << j + 1 << ". " << movies[j]->getTitle() << ", " << movies[j]->getYear() << std::endl;
            json movie;
            movie["title"] = movies[j]->getTitle();
            movie["year"] = movies[j]->getYear();
            movie["synopsis"] = movies[j]->getSynopsis();
            movie["countries"] = movies[j]->getCountries();
            movie["budgetUSD"] = movies[j]->getBudgetUSD();
            movie["boxOfficeUSD"] = movies[j]->getBoxOfficeUSD();
            movie["rate"] = movies[j]->getRate();
//            auto actors = movies[j]->getActors();
//            for(int k = 0; k < actors.getSize(); k++){
//                std::cout << "\t\t" << k + 1 << ". " << actors[k]->getFullName() << std::endl;
//            }
            director["movies"].push_back(movie);
        }
        j.push_back(director);
    }
    return j;
}
