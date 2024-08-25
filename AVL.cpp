/*
Project:            343-lab4
File:               AVL.cpp
Author:             Jaxen Fullerton
Description:        Contains the implementation of the AVL
                    binary search tree
*/
#include "AVL.h"

int AVL::nodeHeight( AVLNode* node )
{
    if ( node == NULL ) return 0;
    return node->height;
}
int AVL::nodeBalance( AVLNode* node )
{
    if ( node == NULL ) return 0;
    return nodeHeight( node->left )
           - nodeHeight( node->right );
}

AVLNode* AVL::rotateR( AVLNode* node )
{
    AVLNode* left = node->left;
    AVLNode* leftRight = left->right;

    left->right = node;
    node->left = leftRight;

    node->height = std::max( nodeHeight( node->left ),
            nodeHeight( node->right ) ) + 1;
    left->height = std::max( nodeHeight( left->left ),
            nodeHeight( left->right ) ) + 1;

    return left; // new root
}
AVLNode* AVL::rotateL( AVLNode* node )
{
    AVLNode* right = node->right;
    AVLNode* rightLeft = right->left;

    right->left = node;
    node->right = rightLeft;

    node->height = std::max( nodeHeight( node->left ),
            nodeHeight( node->right ) ) + 1;
    right->height = std::max( nodeHeight( right->left ),
            nodeHeight( right->right ) ) + 1;

    return right; // new root
}

AVLNode* AVL::lowestValNode( AVLNode* node )
{
    AVLNode* currentNode = node;
    while ( currentNode->left != NULL )
        currentNode = currentNode->left;
    return currentNode;
}


AVLNode* AVL::insert( AVLNode* node, Classic data )
{
    if ( root == NULL )
    {
        root = new AVLNode( data );
        return root;
    }
    if ( node == NULL ) return new AVLNode( data );

    if ( data < *node->data )
        node->left = insert( node->left, data );
    else if ( data > *node->data )
        node->right = insert( node->right, data );
    else return node;

    node->height = std::max( nodeHeight( node->left ),
            nodeHeight( node->right ) ) + 1;

    int balance = nodeBalance( node );

    if ( balance > 1 && data != *node->left->data )
    {
        if ( data > *node->left->data )
            node->left = rotateL( node->left );
        return rotateR( node );
    }

    if ( balance < -1 && data != *node->right->data )
    {
        if ( data < *node->right->data )
            node->right = rotateR( node->right );
        return rotateL( node ); // changed to L ???
    }

    return node;
}

AVLNode* AVL::remove( AVLNode* node, Classic data )
{
    if ( node == NULL ) return node;

    if ( data < *node->data )
        node->left = remove( node->left, data );
    else if ( data > *node->data )
        node->right = remove( node->right, data );
    else
    {
        if ( node->left == NULL || node->right == NULL )
        {
            AVLNode* temp = node->left ? node->left : node->right;

            if ( temp == NULL )
            {
                temp = node;
                node = NULL;
            }
            else *node = *temp;
            delete temp;
        }
        else
        {
            AVLNode* temp = lowestValNode( node->right );
            node->data = temp->data;
            node->right = remove( node->right, *temp->data );
        }
    }

    if ( node == NULL ) return node;

    node->height = std::max( nodeHeight( node->left ),
            nodeHeight( node->right ) ) + 1;
    
    int balance = nodeBalance( node );

    if ( balance > 1 )
    {
        if ( nodeBalance( node->left ) < 0 )
            node->left = rotateL( node->left );
        return rotateR( node );
    }
    if ( balance < -1 )
    {
        if ( nodeBalance( node->right ) > 0 )
            node->right = rotateR( node->right );
        return rotateL( node );
    }

    return node;
}

int AVL::changeStock( Classic classic, int stock )
{
    Classic* classicPtr = NULL;
    search( root, classic.getYear(), classicPtr );

    if ( classicPtr != NULL )
    {
        if ( classicPtr->getStock() + stock < 0 ) return -1;
        classicPtr->setStock( classicPtr->getStock() + stock );

        return classicPtr->getStock();
    }

    return -1;
}

bool AVL::search( AVLNode* node, int key, Classic*& classicPtr )
{
    if ( node == NULL ) return false;
    if ( node->data->getYear() == key ) 
    {
        classicPtr = node->data;
        return true;
    }
    if ( key < node->data->getYear() ) return search( node->left, key, classicPtr );
    return search( node->right, key, classicPtr );
}

AVLNode* AVL::getRoot() const
{
    return root;
}

void AVL::printAll( AVLNode* node ) const
{
    if ( node == NULL )
    {
        return;
    }
    // inorder
    printAll( node->left );
    node->data->print();
    printAll( node->right );
}

void AVL::deleteTree( AVLNode* node )
{
    if ( node != NULL )
    {
        deleteTree( node->left );
        deleteTree( node->right );
        delete node;
    }
}