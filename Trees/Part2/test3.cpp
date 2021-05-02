// Test file for AVL Tree Implementation
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include "avl.hpp"
using namespace std;

int marks = 0;
int total_values = 25;
int values[25] = {55,43,26,82,93,04,39,95,50,6,62,17,21,49,77,5,32,60,88,16,44,72,80,8,36};
int TreeAfterAddition[25] = {4,5,6,8,16,17,21,26,32,36,39,43,44,49,50,55,60,62,72,77,80,82,88,93,95};
int TreeAfterDeletion[21] = {5,8,16,17,21,26,32,36,39,44,49,50,55,60,62,72,77,80,88,93,95};

int indx=0;
int score=0;
int step=0;

template<class T, class S>
void TraverseTree(shared_ptr<node<T,S>> P,int test)
{
	if (P==NULL)
	{
		return;
	}
	if(P->left)
		TraverseTree(P->left,test);
	if(test == 1)
	{
		if(P->key == TreeAfterAddition[indx])
			score++;
	}
	else if(test == 2)
	{
		if(P->key == TreeAfterDeletion[indx])
			score++;
	}
	indx++;
	if(P->right)
		TraverseTree(P->right,test);
}

void test_addition()
{
	cout<<"Test 3.1 - AVL Insertion\n";

	int counter = 0;
	score=0;
	indx=0;
	// Case 1 - Correct order of nodes
	AVL<int,string> B(true);
	for (int i=0;i<total_values;i++)
		B.insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(values[i],"CS202")));
		//B.insertNode(make_shared<node<int,string>>(values[i],"abc"));
	

	TraverseTree(B.getRoot(),1);

	if(score == 25){
		cout << "Test 3.1.1: Passed" << endl;
		counter = counter + 4;
	}
	else
	{
		// Order of nodes is incorrect
		cout << "Test 3.1.1: Failed" << endl;
	}

	// Case 2 - Correct structure of tree
	score = 0;

	shared_ptr<node<int,string>> root = B.getRoot();
	
	if (root != NULL)
	{
	if(root->key == 43){
		score++;
	}
	if(root->right->key == 62){
		score++;
	}
	if(root->left->key == 17){
		score++;
	}
	if(root->left->left->left->key == 4){
		score++;
	}
	if(root->left->right->right->key == 36){
		score++;
	}
	if(root->right->left->right->key == 60){
		score++;
	}
	if(root->right->right->right->right->key == 95){
		score++;
	}
	if(root->left->left->right->left->key == 6){
		score++;
	}
	}

	if(score == 8)
	{
		cout << "Test 3.1.2: Passed" << endl;
		counter = counter + 5;
	}
	else
	{
		// Structure of tree is incorrect
		cout << "Test 3.1.2: Failed" << endl;
	}
	
	cout << "Total Points: " << counter << "/9" << endl << endl;
	marks = marks + counter;

}

void test_deletion()
{
	cout<<"Test 3.3 - AVL Deletion" << endl;

	int counter = 0;
	score=0;
	indx=0;

	// Case 1 - Correct order of nodes
	AVL<int,string> B(true);
	for (int i=0;i<total_values;i++)
		B.insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(values[i],"CS202")));

	for (int i=0;i<total_values;i++)
		B.deleteNode(values[i]);
	for (int i=0;i<total_values;i++)
		B.insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(values[i],"CS202")));

	
	B.deleteNode(6);
	B.deleteNode(82);
	B.deleteNode(4);
	B.deleteNode(43);
	TraverseTree(B.getRoot(),2);

	if(score == (total_values-4)){
		cout << "Test 3.3.1: Passed" << endl;
		counter = counter + 4;
	}
	else
	{
		// Order of nodes is incorrect
		cout << "Test 3.3.1: Failed" << endl;
	}
	
	// Case 2 - Correct structure of tree
	score=0;
	shared_ptr<node<int,string>> root = B.getRoot();
	if (root != NULL)
	{
	if(root->key == 44)
		score++;
	if(root->right->key == 62)
		score++;
	if(root->left->key == 17)
		score++;
	if(root->left->left->left->key == 5)
		score++;
	if(root->left->right->right->key == 36)
		score++;
	if(root->right->left->right->key == 60)
		score++;
	if(root->right->right->right->right->key == 95)
		score++;
	if(root->left->left->right->left == NULL)
		score++;
	}

	if(score == 8)
	{
		counter = counter + 5;
		cout << "Test 3.3.2: Passed" << endl;
		
	}
	else
	{
		// Structure of tree not okay
		cout << "Test 3.3.2: Failed" << endl;
	}

	cout << "Total Points: " << counter << "/9" << endl;
	marks = marks + counter;
}


void test_search()
{
	int counter = 0;
	cout<<"Test 3.2 - AVL Search" << endl;
	score=0;
	indx=0;

	// Case 1 - Simple search
	AVL <int,string> B(true);
	for (int i=0;i<total_values;i++)
		B.insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(values[i],"abc")));
		//B.insertNode(make_shared<node<int,string>>(values[i],"abc"));

	for (int i=0;i<total_values;i++){
		if (B.searchNode(values[i]) != NULL)
		{
			if (B.searchNode(values[i])->key == values[i])
			{
				score++;
			}
		}
	}
	if(score == 25)
	{
		cout << "Test 3.2.1: Passed" << endl;
		counter = counter + 1;
	}
	else
	{
		cout << "Test 3.2.1: Failed" << endl;
	}
	step++;
	score=0;

	// Case 2 - Nodes not present
	if (B.getRoot() != NULL)
	{
		score++;
	}
	if(B.searchNode(100) == NULL)
		score++;
	if(B.searchNode(1) == NULL)
		score++;
	if(B.searchNode(99) == NULL)
		score++;
	if(B.searchNode(40) == NULL)
		score++;

	if(score == 5)
	{
		cout << "Test 3.2.2: Passed" << endl;
		counter = counter + 1;
	}
	else
	{
		cout << "Test 3.2.2: Failed" << endl;
	}

	cout << "Total Points: " << counter << "/2" << endl << endl;
	step++;
	marks = marks + counter;

}
void testcases()
{
	test_addition();
	test_search();
	test_deletion();
}

int main()
{
	cout<<"Test 3 - AVL Tree" << endl << endl;
	testcases();

	cout << endl << "Total Marks: " << marks << "/20" <<endl;
	if (marks == 20)
	{
		cout << "Perfect! Onto the last one :')" << endl;
	}
}
