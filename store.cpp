/*
Project:            343-lab4
File:               store.cpp
Author:             Jaxen Fullerton
Description:        Contains the implementation of the MovieStore
                    class and its methods.
*/
#include "store.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void MovieStore::pullCustomers( std::string filename )
{
    std::ifstream input( filename );

    if ( !input.is_open() )
    {
        std::cout << "Failed to retrieve customer information" << std::endl;
        return;
    }

    int ID;
    std::string first, last;

    while ( input >> ID >> first >> last )
    {
        Customer* temp = new Customer();
        temp->setFirstName( first );
        temp->setLastName( last );

        customers.insert( { ID, temp } );
    }

    input.close();
}

void MovieStore::pullInventory( std::string filename )
{
    std::ifstream input( filename );

    if ( !input.is_open() )
    {
        std::cout << "Failed to retrieve inventory data" << std::endl;
        return;
    }

    std::string line;

    while ( std::getline( input, line ) )
    {
        std::stringstream sstream( line );
        std::string genre;

        std::getline( sstream, genre, ',' );
        genre = removeWS( genre );

        processMovie( genre, sstream );
    }

    input.close();
}

void MovieStore::parseCommands( std::string filename )
{
    std::ifstream input( filename );

    if ( !input.is_open() )
    {
        std::cout << "Failed to open commands file" << std::endl;
        return;
    }

    std::string line;

    while ( !input.eof() )
    {
        std::getline( input, line );
        std::stringstream sstream( line );

        char command;
        sstream >> command;

        std::cout << "COMMAND :: " << command << std::endl;
        
        if ( command == 'I' )
        {
            this->inventory();
        }
        if ( command == 'H' )
        {
            std::string IDStr;
            int ID;

            std::getline( sstream, IDStr );
            IDStr = removeWS( IDStr );

            ID = stoi( IDStr );

            history( ID );
        }
        if ( command == 'B' )
        {
            std::string IDStr, mediaType, genre;
            int ID;

            std::getline( sstream, IDStr, ' ' ); // throwaway
            std::getline( sstream, IDStr, ' ' );
            IDStr = removeWS( IDStr );

            ID = stoi( IDStr );

            std::getline( sstream, mediaType, ' ' );
            mediaType = removeWS( mediaType );

            if ( mediaType != "D" ) continue;

            std::getline( sstream, genre, ' ' );
            genre = removeWS( genre );

            processBorrow( genre, sstream, ID );
        }
        if ( command == 'R' )
        {
            std::string IDStr, mediaType, genre;
            int ID;

            std::getline( sstream, IDStr, ' ' ); // throwaway
            std::getline( sstream, IDStr, ' ' );
            IDStr = removeWS( IDStr );

            ID = stoi( IDStr );

            std::getline( sstream, mediaType, ' ' );
            mediaType = removeWS( mediaType );

            if ( mediaType != "D" ) continue;

            std::getline( sstream, genre, ' ' );
            genre = removeWS( genre );

            processReturn( genre, sstream, ID );
        }

    }

}

void MovieStore::inventory() const
{
    comedies.printAll( comedies.getRoot(), "" );
    dramas.printAll( dramas.getRoot(), "" );
    classics.printAll( classics.getRoot() );
}

void MovieStore::borrowed( int ID )
{
    Customer* customer = customers[ID];

    if ( customer == NULL )
    {
        std::cout << "Error :: ID [" << ID << "] not found" << std::endl;
    }

    customer->printList( customer->getRootB() );
}

void MovieStore::history( int ID )
{
    Customer* customer = customers[ID];

    customer->printList( customer->getRootH() );
}

int MovieStore::borrowMovie( int ID, std::string string, int year, char type )
{
    auto customerIterator = customers.find( ID );
    if ( customerIterator == customers.end() )
    {
        std::cout << "Invalid Customer ID" << std::endl;
        return -1;
    }

    Customer* customer = customerIterator->second;

    if ( type == 'F' ) // what type of movie
    {
        Movie* movie = NULL;
        comedies.search( string, movie );

        if ( !movie )
        {
            std::cout << "Error :: Movie not found" << std::endl;
            return -1;
        }

        customer->pushBorrowed( *movie );
        customer->pushHistory( *movie );

        return comedies.changeStock( string, -1, type ); // change stock depending on movie
    }
    else if ( type == 'D' )
    {
        Movie* movie = NULL;
        comedies.search( string, movie );

        if ( !movie )
        {
            std::cout << "Error :: Movie not found" << std::endl;
            return -1;
        }

        customer->pushBorrowed( *movie );
        customer->pushHistory( *movie );

        return dramas.changeStock( string, -1, type );
    }
    else if ( type == 'C' )
    {
        Classic* classic = NULL;
        classics.search( classics.getRoot(), year, classic );

        if ( !classic )
        {
            std::cout << "Error :: Movie not found" << std::endl;
            return -1;
        }

        customer->pushBorrowed( *classic );
        customer->pushHistory( *classic );

        return classics.changeStock( *classic, -1 );
    }

    std::cout << "Could Not Borrow" << std::endl;
    return -1;
}

/*
                    returnMovie
Description:    Returns the 'movie' borrowed with the customer's 'ID' to
                the inventory and returns the new stock of the movie
*/
int MovieStore::returnMovie( int ID, std::string string, int year, char type )
{
    Customer* customer = customers[ID];
    
    if ( type == 'F' ) // what type of movie
    {
        Movie* movie;
        comedies.search( string, movie );

        if ( !customer->returnBorrowed( *movie ) )
        {
            std::cout << "Could Not Return" << std::endl;
        }

        return comedies.changeStock( string, 1, type ); // change stock depending on movie
    }
    else if ( type == 'D' )
    {
        Movie* movie;
        comedies.search( string, movie );

        if ( !customer->returnBorrowed( *movie ) )
        {
            std::cout << "Could Not Return" << std::endl;
        }

        return dramas.changeStock( string, 1, type );
    }
    else if ( type == 'C' )
    {
        Classic* classic;
        classics.search( classics.getRoot(), year, classic );

        return classics.changeStock( *classic, 1 );
    }

    std::cout << "Could Not Return" << std::endl;
    return -1;
}

// removes the whitespace on the beginning & end of a string
std::string MovieStore::removeWS( std::string string )
{
    auto start = string.find_first_not_of( " \t" );
    if ( start == std::string::npos ) return "";

    auto end = string.find_last_not_of( " \t" );
    return string.substr( start, end - start + 1 );
}

void MovieStore::processMovie( std::string genre, std::stringstream& sstream )
{
    std::string stockStr, director, title, yearStr;
    int stock, year;

    std::getline( sstream, stockStr, ',' );
    stockStr = removeWS( stockStr );

    std::getline( sstream, director, ',' );
    director = removeWS( director );
    
    std::getline( sstream, title, ',' );
    title = removeWS( title );

    stock = std::stoi( stockStr );

    if ( genre == "F" )
    {
        std::getline( sstream, yearStr, ',' );
        yearStr = removeWS( yearStr );

        year = std::stoi( yearStr );

        Comedy newMovie; 
        newMovie.setStock( stock );
        newMovie.setDirector( director );
        newMovie.setTitle( title );
        newMovie.setYear( year );
        comedies.insert( newMovie, 'F' );
    }
    else if ( genre == "D" )
    {
        std::getline( sstream, yearStr, ',' );
        yearStr = removeWS( yearStr );

        year = std::stoi( yearStr );

        Drama newMovie; 
        newMovie.setStock( stock );
        newMovie.setDirector( director );
        newMovie.setTitle( title );
        newMovie.setYear( year );

        dramas.insert( newMovie, 'D' );
    }
    else if ( genre == "C" )
    {
        std::string majorActor, majorActorFirst, majorActorLast, monthStr;
        int month;

        std::getline( sstream, majorActor, ' ' ); // throwaway

        std::getline( sstream, majorActorFirst, ' ' );
        majorActorFirst = removeWS( majorActorFirst );

        std::getline( sstream, majorActorLast, ' ' );
        majorActorLast = removeWS( majorActorLast );

        majorActor = majorActorFirst + " " + majorActorLast;

        std::getline( sstream, monthStr, ' ' );
        monthStr = removeWS( monthStr );

        std::getline( sstream, yearStr, ' ' );
        yearStr = removeWS( yearStr );

        month = std::stoi( monthStr );
        year = std::stoi( yearStr );

        Classic newMovie;
        newMovie.setStock( stock );
        newMovie.setDirector( director );
        newMovie.setTitle( title );
        newMovie.setMajorActor( majorActor );
        newMovie.setMonth( month );
        newMovie.setYear( year );

        classics.insert( classics.getRoot(), newMovie );
    }
}

void MovieStore::processBorrow( std::string genre, std::stringstream& sstream, int ID )
{
    std::string director, title, yearStr;
    int year;
    
    if ( genre == "F" )
    {
        std::getline( sstream, title, ',' );
        title = removeWS( title );

        std::getline( sstream, yearStr, ' ' ); // throwaway
        std::getline( sstream, yearStr, ' ' );
        yearStr = removeWS( yearStr );

        year = std::stoi( yearStr );

        if ( borrowMovie( ID, title, 0, 'F' ) < 0 )
        {
            std::cout << "Error :: Couldn't borrow movie" << std::endl;
        }
    }
    else if ( genre == "D" )
    {
        std::getline( sstream, director, ',' );
        director = removeWS( director );

        std::getline( sstream, title, ',' );
        title = removeWS( title );

        if ( borrowMovie( ID, director, 0, 'D' ) < 0 )
        {
            std::cout << "Error :: Couldn't borrow movie" << std::endl;
        }
    }
    else if ( genre == "C" )
    {
        std::string majorActor, majorActorFirst, majorActorLast, monthStr;
        int month;

        // std::getline( sstream, monthStr, ' ' );
        std::getline( sstream, monthStr, ' ' );
        monthStr = removeWS( monthStr );

        std::getline( sstream, yearStr, ' ' );
        yearStr = removeWS( yearStr );

        std::getline( sstream, majorActor, ' ' ); // throwaway

        std::getline( sstream, majorActorFirst, ' ' );
        majorActorFirst = removeWS( majorActorFirst );

        std::getline( sstream, majorActorLast, ' ' );
        majorActorLast = removeWS( majorActorLast );

        majorActor = majorActorFirst + " " + majorActorLast;

        month = std::stoi( monthStr );
        year = std::stoi( yearStr );

        if ( borrowMovie( ID, "", year, 'C' ) < 0 )
        {
            std::cout << "Error :: Couldn't borrow movie" << std::endl;
        }
    }
}

void MovieStore::processReturn( std::string genre, std::stringstream& sstream, int ID )
{
    std::string director, title, yearStr;
    int year;
    
    if ( genre == "F" )
    {
        std::getline( sstream, title, ',' );
        title = removeWS( title );

        std::getline( sstream, yearStr, ' ' ); // throwaway
        std::getline( sstream, yearStr, ' ' );
        yearStr = removeWS( yearStr );

        year = std::stoi( yearStr );

        if ( returnMovie( ID, title, 0, 'F' ) )
        {
            std::cout << "Error :: Couldn't return movie" << std::endl;
        }
    }
    else if ( genre == "D" )
    {
        std::getline( sstream, director, ',' );
        director = removeWS( director );

        std::getline( sstream, title, ',' );
        title = removeWS( title );

        if ( returnMovie( ID, director, 0, 'D' ) )
        {
            std::cout << "Error :: Couldn't return movie" << std::endl;
        }
    }
    else if ( genre == "C" )
    {
        std::string majorActor, majorActorFirst, majorActorLast, monthStr;
        int month;

        // std::getline( sstream, monthStr, ' ' );
        std::getline( sstream, monthStr, ' ' );
        monthStr = removeWS( monthStr );

        std::getline( sstream, yearStr, ' ' );
        yearStr = removeWS( yearStr );

        std::getline( sstream, majorActor, ' ' ); // throwaway

        std::getline( sstream, majorActorFirst, ' ' );
        majorActorFirst = removeWS( majorActorFirst );

        std::getline( sstream, majorActorLast, ' ' );
        majorActorLast = removeWS( majorActorLast );

        majorActor = majorActorFirst + " " + majorActorLast;

        month = std::stoi( monthStr );
        year = std::stoi( yearStr );

        if ( returnMovie( ID, "", year, 'C' ) )
        {
            std::cout << "Error :: Couldn't return movie" << std::endl;
        }
    }
}