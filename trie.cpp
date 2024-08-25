/*
Project:            343-lab4
File:               trie.cpp
Author:             Jaxen Fullerton
Description:        Contains the implementation of the Trie
                    data structure
*/
#include "trie.h"
#include <stack>

void Trie::insert( Movie movie, char type )
{
    if ( root == NULL )
    {
        root = new TrieNode();
    }    

    Trie::TrieNode* currentNode = root;
    std::string string = "";

    if ( type == 'F' )
    {
        string = movie.getTitle();
    }
    else if ( type == 'D' )
    {
        string = movie.getDirector();
    }
    else return;

    for ( char currentChar : string )
    {
        currentChar = tolower(currentChar);

        if ( currentChar < 'a' || currentChar > 'z' ) continue;

        int index = currentChar - 'a';

        if ( currentNode->children[index] == NULL )
        {
            currentNode->children[index] = new TrieNode();
        }

        currentNode = currentNode->children[index];
    }

    currentNode->isWordEnd = true;
    if ( currentNode->info == NULL )
    {
        currentNode->info = new Movie( movie );
    }
    else
    {
        *currentNode->info = movie;
    }

    currentNode->wordCount++;
}

bool Trie::remove( std::string string )
{
    Trie::TrieNode* currentNode = root;
    std::stack<std::pair<TrieNode*, char>> nodes;

    for ( char currentChar : string )
    {
        int index = tolower(currentChar) - 'a';

        if ( currentNode->children[index] == NULL )
        {
            return false;
        }
    
        nodes.push( { currentNode, currentChar } );
        currentNode = currentNode->children[index];
    }

    currentNode->isWordEnd = false;

    while ( !nodes.empty() )
    {
        TrieNode* node = nodes.top().first;
        char nodeChar = nodes.top().second;
        nodes.pop();

        int index = tolower( nodeChar ) - 'a';
        
        if ( node->children[index]->isWordEnd || hasChildren( node->children[index] ) )
        {
            delete node->children[index]->info;
            node->children[index]->info = NULL;
            break;
        }

        delete node->children[index];
        node->children[index] = NULL;
    }

    return true;
}

int Trie::changeStock( std::string string, int stock, char type )
{
    Movie* moviePtr = NULL;
    if ( type == 'F' )
    {
        search( string, moviePtr );
    }
    else if ( type == 'D' )
    {
        search( string, moviePtr );
    }
    else return -1;

    if ( moviePtr != NULL ) 
    {
        if ( moviePtr->getStock() + stock < 0 ) return -1; // if stock drops < 0
        moviePtr->setStock( moviePtr->getStock() + stock );

        return moviePtr->getStock();
    }

    return -1;
}

int Trie::search( std::string string, Movie*& movie ) const
{
    Trie::TrieNode* currentNode = root;
    int status = 0; // 0 for not found, 1 for found,
                    // -1 for found but conflicting options

    for ( auto currentChar : string )
    {
        int index = tolower(currentChar) - 'a';

        if ( currentNode->children[index] == NULL )
        {
            return 0; // prefix isn't in tree
        }

        currentNode = currentNode->children[index];
    }


    bool foundOneMore = false;
    for ( int i = 0; i < ALPHABET_SIZE; i++ )
    {
        if ( currentNode->children[i] != NULL )
        {
            if ( !foundOneMore ) foundOneMore = true;
            else return -1; // prefix has conflicting postfix
        }
    }

    for ( int i = 0; i < ALPHABET_SIZE; i++ )
    {
        if ( currentNode->children[i] != NULL )
            currentNode = currentNode->children[i];
    }

    movie = currentNode->info; // gets info for movie with prefix

    return 1; // prefix is in the tree
}
Trie::TrieNode* Trie::getRoot() const
{
    return root;
}

void Trie::printAll( TrieNode* node, std::string prefix ) const
{
    if ( node->isWordEnd )
    {
        node->info->print();
    }
    for ( int i = 0; i < ALPHABET_SIZE; i++ )
    {
        if ( node->children[i] != NULL )
        {
            printAll( node->children[i],
                    prefix + static_cast<char>( i + 'a' ) );
        }
    }
}

bool Trie::hasChildren( TrieNode* node )
{
    for ( int i = 0; i < ALPHABET_SIZE; i++ )
    {
        if ( node->children[i] != NULL ) return true;
    }

    return false;
}

void Trie::deleteTrie( TrieNode* node )
{
    if ( node != NULL )
    {
        for ( int i = 0; i < ALPHABET_SIZE; i++ )
        {
            deleteTrie( node->children[i] );
        }

        delete node;
    }
}