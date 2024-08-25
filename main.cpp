/*
Project:        343-lab4
File:           main.cpp
Author:         Jaxen Fullerton
Description:    Main file to test classes and their associated
                member functions.
*/
#include "store.h"
#include <iostream>

using namespace std;

int main()
{

    MovieStore store;

    store.pullCustomers( "data4customers.txt" );
    std::cout << "DONE PULLING CUSTOMERS" << std::endl;

    store.pullInventory( "data4movies.txt" );
    std::cout << "DONE PULLING MOVIES" << std::endl;

    store.parseCommands( "data4commands.txt" );
    std::cout << "DONE PARSING COMMANDS" << std::endl;

    /*
    If you would like to test individual functions you can comment out
    the if statements that cause trouble in the "parseCommands()" method.

    pullCustomers and pullInventory both work as intended, and the sorting
    within the data structures work as well.

    The only major issue was the lacking comments and partially failing
    return command due to time constraints.
    */



    return 0;
}