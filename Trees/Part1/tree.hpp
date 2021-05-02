#include "tree.cpp"

#ifndef __TREE_HPP
#define __TREE_HPP

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Struct for nodes of the tree
template <class T, class S>
struct node {
	T key;
	S value;
	shared_ptr<node<T,S>> child;
	shared_ptr<node<T,S>> sibling;

	node(T key, S value) {

		this->key = key;
		this->value = value;
		child = NULL;
		sibling = NULL;
	}
};


// Tree class
template <class T, class S>
class Tree {
	shared_ptr<node<T,S>> root;

	shared_ptr<node<T,S>> findKeyHelper(shared_ptr<node<T,S>>, T);
	int findHeightHelper(shared_ptr<node<T,S>>);
	shared_ptr<node<T,S>> deleteLeafHelper(shared_ptr<node<T,S>>,T);
	void deleteTree(shared_ptr<node<T,S>>);
public:
	Tree(shared_ptr<node<T,S>>);
	shared_ptr<node<T,S>> findKey(T);
	bool insertChild(shared_ptr<node<T,S>>, T);
	vector<shared_ptr<node<T,S>>> getAllChildren(T);
	int findHeight();
	bool deleteLeaf(T);
	shared_ptr<node<T,S>> getRoot();
	
	// Declare helper functions here
};

#endif