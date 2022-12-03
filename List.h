//
// Created by Максим Лейхнер on 03.12.2022.
//
#include "MoviesException.h"

#ifndef MOVIELIBRARY_LIST_H
#define MOVIELIBRARY_LIST_H


template<class T>
class List{
public:
    int getSize(){
        return this->size;
    }

    void insert(int index, T * element) {
        if (index >= this->size || index < 0) throw bad_addr_exception();
        auto newElement = new Element(element);
        if (index == 0){
            newElement->next = this->first;
            this->first = newElement;
            this->size++;
        }
        else if (index == size - 1){
            this->add(element);
        }
        else
        {
            auto current = this->first;
            for(int i = 0; i < index - 1; i++){
                current = current->next;
            }
            newElement->next = current->next;
            current->next = newElement;
            this->size++;
        }
    }

    void add(T * element) {
        auto newElement = new Element(element);
        if(this->size != 0){
            this->last->next = newElement;
            this->last = newElement;
        }
        else
        {
            this->first = newElement;
            this->last = newElement;
        }
        this->size++;
    }

    void remove(int index){
        if (index >= this->size || index < 0) throw bad_addr_exception();
        if(index == 0){
            auto toDelete = this->first;
            this->first = this->first->next;
            delete toDelete;
            this->size--;
        }
        else if(index == size - 1){
            auto toDelete = this->last;
            auto current = this->first;
            while(current->next != toDelete){
                current = current->next;
            }
            current->next = nullptr;
            this->last = current;
            delete toDelete;
            this->size--;
        }
        else{
            auto current = this->first;
            for(int i = 0; i < index - 1; i++){
                current = current->next;
            }
            auto toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
            this->size--;
        }
    }

    T * operator[](int index) {
        if (index >= this->size) throw bad_addr_exception();
        auto current = this->first;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return current->data;
    }

    void operator+=(List<T> list){
        for (int i = 0; i < list.getSize(); i++){
            this->add(list[i]);
        }
        this->size += list.size;
    }

private:
    struct Element{
        explicit Element(T * data){
            this->data = data;
        }
        T * data = nullptr;
        Element * next = nullptr;
    };
    Element * first = nullptr;
    Element * last = nullptr;
    int size = 0;
};

#endif //MOVIELIBRARY_LIST_H
