#ifndef __TREE_CPP
#define __TREE_CPP

#include <vector>
#include <stack>
#include <algorithm>
#include "tree.hpp"

using namespace std;

// Constructor
template <class T, class S>
Tree<T,S>::Tree(shared_ptr<node<T,S>> root) {
	this->root = root;
}

// This function finds a key in the tree and returns the respective node
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::findKey(T key) {
	return findKeyHelper(root, key);
}

// Helper function to find a key in the tree
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::findKeyHelper(shared_ptr<node<T,S>> currNode, T key) {
	if(currNode == NULL)
	{
		return NULL;
	}
	if(currNode->key == key)
	{
		return currNode;
	}
	shared_ptr<node<T,S>> result = findKeyHelper(currNode->child, key);
	if(result != NULL)
	{
		return result;
	}
	else
	{
		result = findKeyHelper(currNode->sibling, key);
	}
	return result;
}

// This function inserts a the given node as a child of the given key
template <class T, class S>
bool Tree<T,S>::insertChild(shared_ptr<node<T,S>> c, T key) {
	shared_ptr<node<T,S>> insertAt = findKey(key);
	if(insertAt != NULL)
	{
		if(findKey(c->key) == NULL)
		{
			if(insertAt->child == NULL)
			{
				insertAt->child = c;
			}
			else
			{
				insertAt = insertAt->child;
				while(insertAt->sibling != NULL)
				{
					insertAt = insertAt->sibling;
				}
				insertAt->sibling = c;
			}
			return true;
		}
	}
	return false;
}

// This function returns all the children of a node with the given key
template <class T, class S>
vector<shared_ptr<node<T,S>> > Tree<T,S>::getAllChildren(T key) {
	vector<shared_ptr<node<T,S>>> childVector;
	shared_ptr<node<T,S>> node = findKey(key);
	if(node != NULL)
	{
		node = node->child;
	}
	while(node != NULL)
	{
		childVector.push_back(node);
		node = node->sibling;
	}
	return childVector;
}

// This function returns the height of the tree
template <class T, class S>
int Tree<T,S>::findHeight() {
	return findHeightHelper(root);
}

// Helper function to find height of the tree
template <class T, class S>
int Tree<T,S>::findHeightHelper(shared_ptr<node<T,S>> currNode) {
	int height;
	if(root == NULL)
	{
		return 0;
	}
	if(currNode->child == NULL)
	{
		return 1;
	}
	while(currNode->child != NULL)
	{
		height = findHeightHelper(currNode->child) + 1;
		currNode = currNode->child;
	}
	while(currNode->sibling != NULL)
	{
		int temp = findHeightHelper(currNode->sibling);
		if(temp > height)
		{
			height = temp;
		}
		currNode = currNode->sibling;
	}
	return height;
}

// This function deletes the node of a given key (iff it is a leaf node)
template <class T, class S>
bool Tree<T,S>::deleteLeaf(T key) { 
	shared_ptr<node<T,S>> deleteNodeCheck = findKey(key);
	if(deleteNodeCheck == root)
	{
		return false;
	}
	shared_ptr<node<T,S>> deleteNode = deleteLeafHelper(root, key);
	if(deleteNode == NULL)
	{
		return false;
	}
	if(deleteNode->child->child != NULL)
	{
		return false;
	}
	if(deleteNode->child->sibling == NULL)
	{
		deleteNode->child = NULL;
	}
	else
	{
		deleteNode->child = deleteNode->child->sibling;
	}
	return true;
}

// Helper function to delete lead node
template <class T, class S>
shared_ptr<node<T,S>> Tree<T,S>::deleteLeafHelper(shared_ptr<node<T,S>> currNode, T key) {
	if(currNode == NULL)
	{
		return NULL;
	}
	if(currNode->child->key == key)
	{
		return currNode;
	}
	while(currNode->child != NULL)
	{
		shared_ptr<node<T,S>> found = deleteLeafHelper(currNode->child, key);
		if(found != NULL)
		{
			return found;
		}
		else
		{
			break;
		}
	}
	while(currNode->sibling != NULL)
	{
		shared_ptr<node<T,S>> found = deleteLeafHelper(currNode->sibling, key);	
		if(found != NULL)
		{
			return found;
		}
		else
		{
			break;
		}
	}
	return NULL;
}

// This function deletes the tree
template <class T, class S>
void Tree<T,S>::deleteTree(shared_ptr<node<T,S>> currNode) {
	currNode = NULL;
	return;
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>>  Tree<T,S>::getRoot() {
	return root;
}

#endif