/*
Project:            343-lab4
File:               movie.cpp
Author:             Jaxen Fullerton
Description:        Contains implementations for the methods of
                    the movie class, as well as the three child
                    classes: Comedy, Drama, & Classic.
*/
#include "movie.h"

//____________________________PUBLIC____________________________
/*
::                        Movie 'Setters'                       ::
Description:    Each sets the variable of the instance to rval
                for their respective function
*/
void Movie::setStock( int rval )
{
    stock = rval;
}
void Movie::setDirector( std::string rval )
{
    director = rval;
}
void Movie::setTitle( std::string rval )
{
    title = rval;
}
void Movie::setYear( int rval )
{
    year = rval;
}
/*
::                        Movie 'Getters'                       ::
Description:    Each gets the variable of the respective data
                for their function
*/
int Movie::getStock() const
{
    return stock;
}
std::string Movie::getDirector() const
{
    return director;
}
std::string Movie::getTitle() const
{
    return title;
}
int Movie::getYear() const
{
    return year;
}
char Movie::getNotation() const
{
    return notation;
}

bool Movie::operator==( const Movie& rval ) const
{
    if ( director != rval.director ) return false;
    if ( title != rval.title ) return false;
    if ( year != rval.year ) return false;

    return true;
}

/*
::                       Movie::whatIsEmpty                     ::
Description:    Checks if each variable is empty, and returns
                true if all variables are empty
*/
bool Movie::whatIsEmpty( bool& emptyStock, bool& emptyDirector,
                         bool& emptyTitle, bool& emptyYear ) const
{
    if ( stock <= 0 ) emptyStock = true;
    if ( director == "" ) emptyDirector = true;
    if ( title == "" ) emptyTitle = true;
    if ( year <= 0 ) emptyYear = true;

    if ( emptyStock && emptyDirector && emptyTitle && emptyYear )
        return true;
    else return false;
}



//____________________________PUBLIC____________________________
/*
::                        Comedy::Print                       ::
Description:    Prints the data of the instance to the console
*/

void Movie::print() const
{
    bool s, d, t, y;
    if ( whatIsEmpty( s, d, t, y ) )
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    std::cout << notation;
    if ( !s )
        std::cout << ", " << stock;
    if ( !d )
        std::cout << ", " << director;
    if ( !t )
        std::cout << ", " << title;
    if ( !y )
        std::cout << ", " << year;

    std::cout << std::endl;
}

bool Comedy::operator>( const Comedy& rval )
{
    return !compare( rval );
}
bool Comedy::operator<( const Comedy& rval )
{
    return compare( rval );
}

//____________________________PRIVATE___________________________
/*
::                        Comedy::Print                       ::
Description:    Compares two instances of the Comedy class and
                returns true if the lvalue should be printed
                first
*/
bool Comedy::compare( Comedy rval ) const
{
    if ( title != rval.title ) // skip if ==
    {
        for ( int i = 0; title[i] != title.back() &&
            rval.title[i] != rval.title.back(); i++ )
        {
            // find first letter that is different
            if ( toupper( title[i] ) < toupper( rval.title[i] ) )
            return true; // return true if before in alphabet
            else return false; // return false if after in alphabet
        }
        // if they are the same but one has more characters
        // choose the one with less characters
        if ( title.length() < rval.title.length() ) return true;
        else return false;
    }

    // check year second
    if ( year <= rval.year ) return true;

    return false; // return false if neither are true
}





//____________________________PUBLIC____________________________

bool Drama::operator>( const Drama& rval )
{
    return !compare( rval );
}
bool Drama::operator<( const Drama& rval )
{
    return compare( rval );
}
//____________________________PRIVATE___________________________
/*
::                         Drama::Compare                        ::
Description:    Compares two instances of the Drama class and
                returns true if the lvalue should be printed
                first
*/
bool Drama::compare( Drama rval ) const
{
    if ( director != rval.director ) // skip if ==
    {
        for ( int i = 0; director[i] != director.back() &&
            rval.director[i] != rval.director.back(); i++ )
        {
            // find first letter that is different
            if ( toupper( director[i] ) < toupper( rval.director[i] ) )
            return true; // return true if before in alphabet
            else return false; // return false if after in alphabet
        }
        // if they are the same but one has more characters
        // choose the one with less characters
        if ( director.length() < rval.director.length() ) return true;
        else return false;
    }

    if ( title != rval.title ) // skip if ==
    {
        for ( int i = 0; title[i] != title.back() &&
            rval.title[i] != rval.title.back(); i++ )
        {
            // find first letter that is different
            if ( toupper( title[i] ) < toupper( rval.title[i] ) )
            return true; // return true if before in alphabet
            else return false; // return false if after in alphabet
        }
        // if they are the same but one has more characters
        // choose the one with less characters
        if ( title.length() < rval.title.length() ) return true;
        else return false;
    }

    return false;
}




//____________________________PUBLIC____________________________

void Classic::setMonth( int month )
{
    this->month = month;
}

void Classic::setMajorActor( std::string majorActor )
{
    this->majorActor = majorActor;
}

/*
::                        Classic::Print                       ::
Description:    Prints the data of the instance to the console
*/
void Classic::print() const
{
    bool s, d, t, y;
    if ( whatIsEmpty( s, d, t, y ) )
    {
        std::cout << "EMPTY" << std::endl;
        return;
    }

    std::cout << notation;
    if ( !s )
        std::cout << ", " << stock;
    if ( !d )
        std::cout << ", " << director;
    if ( !t )
        std::cout << ", " << title;
    if ( majorActor != "" )
        std::cout << ", " << majorActor;
    if ( month > 0 )
        std::cout << ", " << month;
    if ( !y )
        std::cout << ", " << year;

    std::cout << std::endl;
}

bool Classic::operator>( const Classic& rval ) const
{
    return !compare( rval );
}
bool Classic::operator<( const Classic& rval ) const
{
    return compare( rval );
}
bool Classic::operator!=( const Classic& rval ) const
{
    if ( year != rval.year ) return true;
    if ( month != rval.month) return true;

    return false;
}
bool Classic::operator==( const Classic& rval ) const
{
    if ( year != rval.year ) return false;
    if ( month != rval.month ) return false;

    return true;
}
//____________________________PRIVATE___________________________
/*
::                        Classic::Compare                     ::
Description:    Compares two instances of the Classic class and
                returns true if the lvalue should be printed
                first
*/
bool Classic::compare( Classic rval ) const
{
    // check year first
    if ( year < rval.year ) return true;
    if ( year > rval.year ) return false;

    // just compares by first name
    if ( majorActor < rval.majorActor ) return true;
    if ( majorActor > rval.majorActor ) return true;

    return false;
}