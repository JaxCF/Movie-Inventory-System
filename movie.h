/*
Project:            343-lab4
File:               movie.h
Author:             Jaxen Fullerton
Description:        Contains the declarations for the movie class,
                    as well as the three child classes: Comedy,
                    Drama, & Classic.
*/
#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

/*
____________________________ Movie ____________________________
Description:    The parent class of the three main movie types:
                Comedy, Drama, & Classic.
*/
class Movie {
public:
    struct MovieNode;

    Movie() : stock(0), director(""), title(""), year(0), notation('M') {}
    virtual ~Movie() {}

    void setStock( int );
    void setDirector( std::string );
    void setTitle( std::string );
    void setYear( int );

    int getStock() const;
    std::string getDirector() const;
    std::string getTitle() const;
    int getYear() const;
    virtual char getNotation() const;

    void print() const;

    bool operator==( const Movie& ) const;

    bool whatIsEmpty( bool&, bool&, bool&, bool& ) const;

protected:
    int stock;
    std::string director;
    std::string title;
    int year;
    char notation;

};

/*
__________________________ MovieNode __________________________
Description:    Acts as a single node for the borrowed and
                history linked lists in the customer class
*/
struct MovieNode {
    Movie movie;
    MovieNode* next;

    MovieNode() : next( NULL ) {}
    MovieNode( Movie movie ) : movie( movie ), next( NULL ) {}
};

/*
________________________ Comedy:Movie _________________________
Description:    Child class of Movie, denotes a movie of type:
                Comedy, represented by the NOTATION 'F'.
*/
class Comedy : public Movie {
public:
    Comedy() : Movie() { notation = 'F'; }
    
    bool operator>( const Comedy& );
    bool operator<( const Comedy& );

private:
    bool compare( Comedy ) const;
};

/*
________________________ Drama:Movie __________________________
Description:    Child class of Movie, denotes a movie of type:
                Drama, represented by the NOTATION 'D'.
*/
class Drama : public Movie {
public:
    Drama() : Movie() { notation = 'D'; }
    
    bool operator>( const Drama& );
    bool operator<( const Drama& );

private:
    bool compare( Drama ) const;
};

/*
________________________ Comedy:Movie _________________________
Description:    Child class of Movie, denotes a movie of type:
                Classic, represented by the NOTATION 'C'.
*/
class Classic : public Movie {
public:
    Classic() : Movie(), month(0), majorActor("") { notation = 'C'; }

    void setMonth( int );
    void setMajorActor( std::string );

    void print() const;

    bool operator>( const Classic& ) const;
    bool operator<( const Classic& ) const;
    bool operator!=( const Classic& ) const;
    bool operator==( const Classic& ) const;

private:
    int month;
    std::string majorActor;

    bool compare( Classic ) const;
};

#endif