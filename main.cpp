#include <iostream>
#include "List.h"
#include "DataTypes.h"

int main() {

    List<Human> directors;

    directors.add(new Human("Рената", "Литвинова"));
    directors.add(new Human("Кристофер", "Нолан"));
    directors.add(new Human("Дэвид", "Финчер"));

    directors[0]->addMovie(new Movie("Северный ветер", 2021));
    directors[0]->addMovie(new Movie("Зеленый театр в Земфире", 2008));
    directors[0]->getMovies()[0]->addActor(directors[0]);

    directors[1]->addMovie(new Movie("Интерстеллар", 2014));
    directors[1]->addMovie(new Movie("Начало", 2010));

    directors[2]->addMovie(new Movie("Бойцовский клуб", 1999));
    directors[2]->addMovie(new Movie("Чужой 3", 1992));

    for(int i = 0; i < directors.getSize(); i++){
        std::cout << i + 1 << ". " << directors[i]->getFullName() << std::endl;
        auto movies = directors[i]->getMovies();
        for(int j = 0; j < movies.getSize(); j++){
            std::cout << "\t" << j + 1 << ". " << movies[j]->getTitle() << ", " << movies[j]->getYear() << std::endl;
            auto actors = movies[j]->getActors();
            for(int k = 0; k < actors.getSize(); k++){
                std::cout << "\t\t" << k + 1 << ". " << actors[k]->getFullName() << std::endl;
            }
        }
    }

    return 0;
}
