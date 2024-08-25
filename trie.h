/*
Project:            343-lab4
File:               trie.h
Author:             Jaxen Fullerton
Description:        Contains the declaration for the trie data
                    structure, designed to hold Comedy:Movie
                    and Drama:Movie instances.
*/
#ifndef TRIE_H
#define TRIE_H

#include "movie.h"
#include <iostream>
#include <vector>

/*
____________________________ Trie ____________________________
Description:    A class to represent a Trie data structure,
                used for storing Comedy & Drama movies
*/
class Trie {
public:
    static const int ALPHABET_SIZE = 26; // ????

    /*
    __________________________ TrieNode ______________________
    Description:    A struct used in the Trie class to act as
                    an individual node.
    */
    struct TrieNode
    {
        TrieNode* children[Trie::ALPHABET_SIZE];
        Movie* info;
        int wordCount;
        bool isWordEnd;

        TrieNode() : info( NULL ), wordCount( 0 )
        {
            for ( int i = 0; i < Trie::ALPHABET_SIZE; i++ )
            {
                children[i] = NULL;
            }
        }
        ~TrieNode()
        {
            delete info;
        }
    };

    Trie() : root( NULL ) {}
    ~Trie()
    {
        deleteTrie( root );
    }

    void insert( Movie, char );
    bool remove( std::string );
    int changeStock( std::string, int, char type);

    int search( std::string, Movie*& ) const;
    TrieNode* getRoot() const;

    void printAll( TrieNode*, std::string ) const;

private:
    TrieNode* root;

    bool hasChildren( TrieNode* );

    void deleteTrie( TrieNode* );
};

#endif