/*
Project:            343-lab4
File:               store.h
Author:             Jaxen Fullerton
Description:        Contains the declaration for the MovieStore class,
                    which represents a movie store
*/
#ifndef STORE_H
#define STORE_H

#include "movie.h"
#include "customer.h"
#include "trie.h"
#include "AVL.h"
#include <iostream>
#include <unordered_map>

class MovieStore {
public:
    MovieStore() {}
    ~MovieStore()
    {
        for ( auto& entry : customers )
        {
            delete entry.second;
        }
        customers.clear();
    }

    void pullCustomers( std::string );
    void pullInventory( std::string );
    void parseCommands( std::string );

    void inventory() const; // prints inventory

    void borrowed( int ); // prints borrowed movies of the customer
    void history( int ); // prints customer history

    int borrowMovie( int, std::string, int, char ); // returns stock after update
    int returnMovie( int, std::string, int, char ); // returns stock after update

private:
    Trie comedies;
    Trie dramas;
    AVL classics;

    std::unordered_map<int, Customer*> customers;

    std::string removeWS( std::string );
    void processMovie( std::string, std::stringstream& );
    void processBorrow( std::string, std::stringstream&, int );
    void processReturn( std::string, std::stringstream&, int );

};

#endif