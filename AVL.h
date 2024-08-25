/*
Project:            343-lab4
File:               AVL.h
Author:             Jaxen Fullerton
Description:        Contains the declaration for the AVL data
                    structure that is used to store Classic
                    movies.
*/
#ifndef AVL_H
#define AVL_H

#include "movie.h"
#include <iostream>

/*
__________________________ AVLNode __________________________
Description:    Represents a single node in an AVL tree
*/
struct AVLNode{
    Classic* data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode() : left( NULL ), right( NULL ),
                height( 0 ) {}
    AVLNode( const Classic& classic ) : left( NULL ), right( NULL ), height( 0 )
            { data = new Classic( classic ); }
    ~AVLNode()
    {
        if ( data != NULL ) delete data;
    }
};
/*
____________________________ AVL ____________________________
Description:    A class to represent an AVL binary search
                tree data structure, used for storing
                Classic movies
*/
class AVL {
public:
    AVL() : root( NULL ) {}
    ~AVL() { deleteTree( root ); }

    AVLNode* insert( AVLNode*, Classic );
    AVLNode* remove( AVLNode*, Classic );
    int changeStock( Classic, int );

    bool search( AVLNode*, int, Classic*& );
    AVLNode* getRoot() const;

    void printAll( AVLNode* ) const;

private:
    AVLNode* root;

    int nodeHeight( AVLNode* );
    int nodeBalance( AVLNode* );
    AVLNode* lowestValNode( AVLNode* );

    AVLNode* rotateR( AVLNode* );
    AVLNode* rotateL( AVLNode* );

    void deleteTree( AVLNode* );
};

#endif