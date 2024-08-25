/*
Project:            343-lab4
File:               customer.h
Author:             Jaxen Fullerton
Description:        Contains the declarations for the customer
                    class, which represents a single customer.
*/
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "movie.h"
#include <iostream>
#include <string>

/*
____________________________ Customer ____________________________
Description:    A class to represent a single customer, contains
                information regarding identification and current
                borrowing status
*/
class Customer {
public:
    Customer() : firstName(""), lastName(""), borrowed(NULL),
                 history(NULL) {}
    ~Customer()
    {
        deleteList( borrowed );
        deleteList( history );
    }

    void printList( MovieNode* node );
    MovieNode* getRootB() const;
    MovieNode* getRootH() const;

    void pushBorrowed( Movie );
    void pushHistory( Movie );
    void setFirstName( std::string );
    void setLastName( std::string );

    bool returnBorrowed( Movie );

private:
    std::string firstName;
    std::string lastName;
    MovieNode* borrowed;    // LinkedList in lessRecent->recent order
    MovieNode* history;     // LinkedList in recent->lessRecent order

    void deleteList( MovieNode* );

};

#endif