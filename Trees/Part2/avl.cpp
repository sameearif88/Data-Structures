#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include <memory>
#include "avl.hpp"

using namespace std;

// Constructor
template <class T, class S>
AVL<T,S>::AVL(bool isAVL){
	this->root = NULL;
    this->isAVL = isAVL;
}
//This function will calculate the balance factor
template <class T, class S>
int AVL<T,S> :: balanceFactor(shared_ptr<node<T,S>> cuurNode)
{
    int leftHeight, rightHeight;
    if(cuurNode->left != NULL)
    {
        leftHeight = cuurNode->left->height;
    }
    else
    {
        leftHeight = 0;
    }
    if(cuurNode->right != NULL)
    {
        rightHeight = cuurNode->right->height;
    }
    else
    {
        rightHeight = 0;
    }
    return leftHeight - rightHeight;
}

//This function will update height of all the ancestors of the node
template <class T, class S>
void AVL<T,S> :: updateHeights(shared_ptr<node<T,S>> cuurNode)
{
    if(cuurNode == NULL)
    {
        return;
    }
    updateHeights(cuurNode->left);
    updateHeights(cuurNode->right);
    cuurNode->height = height(cuurNode);
}

//This function will perform LL rotation
template <class T, class S>
void AVL<T,S> :: rotationLL(shared_ptr<node<T,S>> cuurNode)
{
    shared_ptr<node<T,S>> parent = searchParent(root, cuurNode);
    if(parent == NULL)
    {
        shared_ptr<node<T,S>> temp = cuurNode->left->right;
        shared_ptr<node<T,S>> tempRoot = root;
        root = cuurNode->left;
        tempRoot->left = temp;
        root->right = tempRoot;
    }
    else if(parent->right == cuurNode)
    {
        shared_ptr<node<T,S>> temp = cuurNode->left->right;
        parent->right = cuurNode->left;
        cuurNode->left->right = cuurNode;
        cuurNode->left = temp;
    }
    else
    {
        shared_ptr<node<T,S>> temp = cuurNode->left->right;
        parent->left = cuurNode->left;
        cuurNode->left->right = cuurNode;
        cuurNode->left = temp;
    }
}

//This function will perform RR rotation
template <class T, class S>
void AVL<T,S> :: rotationRR(shared_ptr<node<T,S>> cuurNode)
{
    shared_ptr<node<T,S>> parent = searchParent(root, cuurNode);
    if(parent == NULL)
    {
        shared_ptr<node<T,S>> temp = cuurNode->right->left;
        shared_ptr<node<T,S>> tempRoot = root;
        root = cuurNode->right;
        tempRoot->right = temp;
        root->left = tempRoot;
    }
    else if(parent->right == cuurNode)
    {
        shared_ptr<node<T,S>> temp = cuurNode->right->left;
        parent->right = cuurNode->right;
        cuurNode->right->left = cuurNode;
        cuurNode->right = temp;
    }
    else
    {
        shared_ptr<node<T,S>> temp = cuurNode->right->left;
        parent->left = cuurNode->right;
        cuurNode->right->left = cuurNode;
        cuurNode->right = temp;
    }
}

//This function will perform LR rotation
template <class T, class S>
void AVL<T,S> :: rotationLR(shared_ptr<node<T,S>> cuurNode)
{
    shared_ptr<node<T,S>> temp = cuurNode->left->right->left;
    shared_ptr<node<T,S>> tempNode = cuurNode->left;
    cuurNode->left = cuurNode->left->right;
    cuurNode->left->left = tempNode;
    tempNode->right = temp;
    rotationLL(cuurNode);
}

//This function will perform RL rotation
template <class T, class S>
void AVL<T,S> :: rotationRL(shared_ptr<node<T,S>> cuurNode)
{
    shared_ptr<node<T,S>> temp = cuurNode->right->left->left;
    shared_ptr<node<T,S>> tempNode = cuurNode->right;
    cuurNode->right = cuurNode->right->left;
    cuurNode->right->right = tempNode;
    tempNode->left = temp;
    rotationRR(cuurNode);
}

//This function will perform post order traversal and rotate if unbalanced node
template <class T, class S>
void AVL<T,S> :: postOrderBalance(shared_ptr<node<T,S>> cuurNode)
{
    if(cuurNode == NULL)
    {
        return;
    }
    postOrderBalance(cuurNode->left);
    postOrderBalance(cuurNode->right);
    if(balanceFactor(cuurNode) == 2 && balanceFactor(cuurNode->left) == 1)
    {
        rotationLL(cuurNode);
    }
    else if(balanceFactor(cuurNode) == -2 && balanceFactor(cuurNode->right) == -1)
    {
        rotationRR(cuurNode);
    }
    else if(balanceFactor(cuurNode) == -2 && balanceFactor(cuurNode->right) == 1)
    {
        rotationRL(cuurNode);
    }
    else if(balanceFactor(cuurNode) == 2 && balanceFactor(cuurNode->left) == -1)
    {
        rotationLR(cuurNode);
    }
    updateHeights(root);
}

// This function returns the parent of the node
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: searchParent(shared_ptr<node<T,S>> currNode, shared_ptr<node<T,S>> findParent)
{
    if(findParent == root)
    {
        return NULL;
    }
    if(currNode->left == findParent || currNode->right == findParent)
    {
        return currNode;
    }
    else if(currNode->key > findParent->key)
    {
        return searchParent(currNode->left, findParent);
    }
    else 
    {
        return searchParent(currNode->right, findParent);
    }
}

// This function inserts a given node in the tree
template <class T, class S>
void AVL<T,S> :: insertNode(shared_ptr<node<T,S>> newNode){
    if(root == NULL)
    {
        root = newNode;
        root->height = 1;
    }
    else
    {
        shared_ptr<node<T,S>> insertAt = root;
        bool found = false;
        while(!found)
        {
            if(insertAt->key > newNode->key)
            {
                if(insertAt->left == NULL)
                {
                    found = true;
                    insertAt->left = newNode;
                    insertAt->left->height = height(newNode);
                    updateHeights(root);
                }
                else
                {
                    insertAt = insertAt->left;
                }
            }
            else if(insertAt->key < newNode->key)
            {
                if(insertAt->right == NULL)
                {
                    found = true;
                    insertAt->right = newNode;
                    insertAt->right->height = height(newNode);
                    updateHeights(root);
                }
                else
                {
                    insertAt = insertAt->right;
                }
            }
        }
    }
    if(isAVL)
    {
        postOrderBalance(root);
    }
}

// This function searches a node in a tree by its key
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: searchNode(T k){
    shared_ptr<node<T,S>> traverse = root;
    if(traverse != NULL)
    {
        while(traverse != NULL)
        {
            if(traverse->key == k)
            {
                return traverse;
            }
            else if(traverse->key > k)
            {
                traverse = traverse->left;
            }
            else
            {
                traverse = traverse->right;
            }
        }
    }
    return NULL;
}

// This function deletes a given node from the tree
template <class T, class S>
void AVL<T,S>::deleteNode(T k){
    shared_ptr<node<T,S>> deleteNode = searchNode(k);
    if(deleteNode != NULL)
    {
        shared_ptr<node<T,S>> parent = searchParent(root, deleteNode);
        if(deleteNode->left == NULL && deleteNode->right == NULL)
        {
            if(deleteNode == root)
            {
                root = NULL;
            }
            else if(parent->right != NULL && parent->right->key == k)
            {
                parent->right = NULL;
            }
            else
            {
                parent->left = NULL;
            }
        }
        else if(deleteNode->left == NULL && deleteNode->right != NULL)
        {
            if(deleteNode == root)
            {
                root = root->right;
            }
            else if(parent->right != NULL && parent->right->key == k)
            {
                parent->right = deleteNode->right;
            }
            else
            {
                parent->left = deleteNode->right;
            }
        }
        else if(deleteNode->right == NULL && deleteNode->left != NULL)
        {
            if(deleteNode == root)
            {
                root = root->left;
            }
            else if(parent->right != NULL && parent->right->key == k)
            {
                parent->right = deleteNode->left;
            }
            else
            {
                parent->left = deleteNode->left;
            }
        }
        else
        {
            shared_ptr<node<T,S>> smallest = deleteNode->right;
            while(smallest->left != NULL)
            {
                smallest = smallest->left;
            }
            if(smallest == deleteNode->right)
            {
                deleteNode->key = smallest->key;
                deleteNode->value = smallest->value;
                deleteNode->right = NULL;
            }
            else
            {
                parent = searchParent(root, smallest);
                deleteNode->key = smallest->key;
                deleteNode->value = smallest->value;
                parent->left = smallest->right;
            }
        }
        updateHeights(root);
        if(isAVL)
        {
            postOrderBalance(root);
        }
    }
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::getRoot(){
    return root;
}

// This function calculates and returns the height of the tree
template <class T, class S>
int AVL<T,S> :: height (shared_ptr<node<T,S>> p){
    if(p == NULL)
    {
        return 0;
    }
    int leftHeight = height(p->left) + 1;
    int rightHeight = height(p->right) + 1;
    if(leftHeight > rightHeight)
    {
        return leftHeight;
    }
    else
    {
        return rightHeight;
    }
}

#endif
