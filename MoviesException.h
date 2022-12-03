//
// Created by Максим Лейхнер on 03.12.2022.
//

#ifndef MOVIELIBRARY_MOVIESEXCEPTION_H
#define MOVIELIBRARY_MOVIESEXCEPTION_H

#include <exception>

class bad_addr_exception : virtual public std::exception{
    const char * what() const noexcept override {
        return "Trying to reach non-existent element";
    }
};

#endif //MOVIELIBRARY_MOVIESEXCEPTION_H