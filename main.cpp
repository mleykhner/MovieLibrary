#include <iostream>
#include <fstream>
#include "json.hpp"
#include "List.h"
#include "DataTypes.h"
#include "jsonHandler.h"


using json = nlohmann::json;

int main() {
//    directors.add(new Human("Рената", "Литвинова"));
//    directors.add(new Human("Кристофер", "Нолан"));
//    directors.add(new Human("Дэвид", "Финчер"));
//
//    directors[0]->addMovie(new Movie("Северный ветер", 2021));
//    directors[0]->addMovie(new Movie("Зеленый театр в Земфире", 2008));
//    directors[0]->getMovies()[0]->addActor(directors[0]);
//
//    directors[1]->addMovie(new Movie("Интерстеллар", 2014));
//    directors[1]->addMovie(new Movie("Начало", 2010));
//
//    directors[2]->addMovie(new Movie("Бойцовский клуб", 1999));
//    directors[2]->addMovie(new Movie("Чужой 3", 1992));

    List<Human> * directors;

    std::ifstream iFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/input.json");
    std::string query;
    while(!iFile.eof()){
        auto * newLine = new char;
        iFile.getline(newLine, 1024);
        query += newLine;
    }
    std::cout << query << std::endl;
    //directors = parseJSON(query);
    directors = deserializeJSON(query);

    //directors->operator[](1)->getMovies().operator[](0)->addActor(new Human("Антошка", "Шагин", 124236));

    std::ofstream oFile("/Users/mleykhner/Documents/Курсовая 3 сем/MovieLibrary/resources/output.json");
    oFile.clear();
    oFile << serializeJSON(directors).dump(4);

    return 0;
}
