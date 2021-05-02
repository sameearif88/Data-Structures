#ifndef __EXP_TREE_HPP
#define __EXP_TREE_HPP

#include <vector>
#include <bits/stdc++.h>

using namespace std;

// a node of the expression tree
struct node {
    char op; //operator or the operand
    shared_ptr<node> left;
    shared_ptr<node> right;
    
    node (char op) 
	{
        this->op = op;
        left = NULL;
        right = NULL;
    }
};

// struct used to provide variable values
struct Variable {
	char name;
	double value;
	Variable(char name, double value)
	{
		this->name = name;
		this->value = value;
	}
};

// our expression tree class
class ExpTree {

	shared_ptr<node> root;

	// recursive function called by calculate():
	double calculateRecurse(shared_ptr<node> currNode, vector<Variable> variables);

	// recursive function called by getInfix():
	string getInfixRecurse(shared_ptr<node> currNode);

public:

	// class constructor that calls buildTree()
	ExpTree(string postfix_exp, bool optimal);

	// returns the constructed expression tree from the given postfix expression
	// when the optimal argument is set, the subtrees not containing any variables are computed and their result is stored in the tree as only one node
	void buildTree(string postfix_exp, bool optimal);

	// returns the root node of the tree;
	shared_ptr<node> getRoot();

	// returns the value of the expression given the value of the variables in the vector
	double calculate(vector<Variable> variables);

	// returns the infix expression with parentheses added
	string getInfix();

};

#endif
