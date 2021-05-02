#ifndef __EXP_TREE_CPP
#define __EXP_TREE_CPP

#include "exp_tree.hpp"

// class constructor that calls buildTree()
ExpTree::ExpTree(string postfix_exp, bool optimal) {
    buildTree(postfix_exp, optimal);
}

// returns the constructed expression tree from the given postfix expression
// when the optimal argument is set, the subtrees not containing any variables are computed and their result is stored in the tree as only one node
void ExpTree::buildTree(string postfix_exp, bool optimal)
{
    stack<ExpTree> myStack;
    int index = 0;
    root = NULL;
    while(postfix_exp[index] != '\0')
    {
        if(postfix_exp[index] != '+' && postfix_exp[index] != '-' && postfix_exp[index] != '*' && postfix_exp[index] != '/')
        {
            ExpTree tree("", optimal);
            tree.root = make_shared<node>(postfix_exp[index]);
            myStack.push(tree);
        }
        else
        {
            ExpTree tree("", optimal);
            tree.root = make_shared<node>(postfix_exp[index]);
            tree.root->right = (myStack.top()).root;
            myStack.pop();
            tree.root->left = (myStack.top()).root;
            myStack.pop();
            myStack.push(tree); 
            if(optimal)
            {
                if(tree.root->left->op >= 48 && tree.root->left->op <= 57)
                {
                    if(tree.root->right->op >= 48 && tree.root->right->op <= 57)
                    {
                        int numOne = tree.root->left->op - 48;
                        int numTwo = tree.root->right->op - 48;
                        int result;
                        if(tree.root->op == '+')
                        {
                            result = numOne + numTwo;
                        }
                        else if(tree.root->op == '-')
                        {
                            result = numOne - numTwo;
                        }
                        else if(tree.root->op == '*')
                        {
                            result = numOne * numTwo;
                        }
                        else
                        {
                            result = numOne / numTwo;
                        }
                        result += 48;
                        tree.root = make_shared<node>((char)result);
                        myStack.pop();
                        myStack.push(tree);
                    }
                }
            }
        }
        index++;
    }
    if(index != 0)
    {
        root = myStack.top().root;
    }
}

// returns the root node of the tree;
shared_ptr<node> ExpTree::getRoot()
{
    return root;
}

// returns the value of the expression given the value of the variables in the vector
double ExpTree::calculate(vector<Variable> variables)
{
	return calculateRecurse(root, variables);
}

// recursive function called by calculate():
double ExpTree::calculateRecurse(shared_ptr<node> currNode, vector<Variable> variables)
{
	if(currNode == NULL)
    {
        return -99;
    }
    double numOne = calculateRecurse(currNode->left, variables);
    double numTwo = calculateRecurse(currNode->right, variables);
    if(currNode->op >= 97 && currNode->op <= 122)
    {
        for(int i = 0; i < variables.size(); ++i)
        {
            if(variables.at(i).name == currNode->op)
            {
                return variables.at(i).value;
            }
        }
    }
    else if(currNode->op >= 48 && currNode->op <= 57)
    {
        return double(currNode->op - 48);
    }
    else
    {
        double result;
        if(currNode->op == '+')
        {
            result = numOne + numTwo;
        }
        else if(currNode->op == '-')
        {
            result = numOne - numTwo;
        }
        else if(currNode->op == '*')
        {
            result = numOne * numTwo;
        }
        else
        {
            result = numOne / numTwo;
        }
        return result;
    }
}

// returns the infix expression with brackets added
string ExpTree::getInfix()
{
	return getInfixRecurse(root);
}

// recursive function called by getInfix():
string ExpTree::getInfixRecurse(shared_ptr<node> currNode)
{
	if(currNode == NULL)
    {
        return "";
    }
    string stringOne = getInfixRecurse(currNode->left);
    string stringTwo = getInfixRecurse(currNode->right);
    if(currNode->op >= 97 && currNode->op <= 122)
    {
        string result = "";
        result += currNode->op;
        return result;
    }
    else if(currNode->op >= 48 && currNode->op <= 57)
    {
        string result = "";
        result += currNode->op;
        return result;
    }
    else if(currNode != root)
    {
        string result = "";
        result += currNode->op;
        return "(" + stringOne + result + stringTwo + ")";
    }
    else
    {
        string result = "";
        result += currNode->op;
        return stringOne + result + stringTwo;
    }
}

#endif