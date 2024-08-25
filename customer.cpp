/*
Project:            343-lab4
File:               customer.cpp
Author:             Jaxen Fullerton
Description:        Contains the implementation of the Customer
                    class and its methods.
*/
#include "customer.h"


void Customer::printList( MovieNode* node )
{
    if ( node == NULL ) return;

    if ( node->movie.getNotation() == 'F' ) // what type of movie
    {
        node->movie.print();
    }
    else if ( node->movie.getNotation() == 'D' )
    {
        node->movie.print();
    }
    else if ( node->movie.getNotation() == 'C' )
    {
        Classic* classic = dynamic_cast<Classic*>( &node->movie );

        classic->print();
    }

    printList( node->next );
}

MovieNode* Customer::getRootB() const
{
    return borrowed;
}

MovieNode* Customer::getRootH() const
{
    return history;
}

void Customer::pushBorrowed( Movie movie )
{
    MovieNode* temp = new MovieNode( movie );
    temp->next = borrowed;
    borrowed = temp;
}
void Customer::pushHistory( Movie movie )
{
    if ( history == NULL )
        history = new MovieNode( movie );
    else
    {
        MovieNode* currentNode = history;
        while ( currentNode->next != NULL )
            currentNode = currentNode->next;
        currentNode->next = new MovieNode( movie );
    }
}

void Customer::setFirstName( std::string first )
{
    firstName = first;
}

void Customer::setLastName( std::string last )
{
    lastName = last;
}

bool Customer::returnBorrowed( Movie movie )
{
    if ( borrowed == NULL ) return false;
    if ( borrowed->movie == movie ) return true;

    MovieNode* currentNode = borrowed;
    while ( currentNode->next != NULL )
    {
        if ( currentNode->next->movie == movie )
        {
            MovieNode* temp = currentNode->next->next;
            delete currentNode->next;
            currentNode->next = temp;

            return true;
        }

        currentNode = currentNode->next;
    }

    return false;
}

void Customer::deleteList( MovieNode* node )
{
    if ( node == NULL ) return;

    deleteList( node->next );

    delete node;
}