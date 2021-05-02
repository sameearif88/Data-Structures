// Test file for BST Implementation
#include "avl.hpp"
#include <vector>


using namespace std;

void test_insert(shared_ptr<AVL<int,string>> tree);
int trav(shared_ptr<node<int,string>> P,int i);
vector<int> find_delete(int k,vector<int> v);
void test_delete(shared_ptr<AVL<int,string>> tree);
void test_search(shared_ptr<AVL<int,string>> tree);
void test_replace(shared_ptr<AVL<int,string>> tree);
void test_height(shared_ptr<AVL<int,string>> tree);
vector<int> test_vec;
vector<int> ref_vec;
int marks = 0;

int main()
{
	shared_ptr<AVL<int,string>> tree(new AVL<int,string>(false));

	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(34,"a")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(7,"b")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(53,"c")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(12,"d")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(68,"e")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(90,"f")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(24,"g")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(71,"h")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(13,"i")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(3,"j")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(1,"k")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(61,"l")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(18,"m")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(30,"n")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(50,"o")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(4,"p")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(11,"q")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(52,"r")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(54,"r")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(56,"r")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(55,"r")));
	tree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(80,"r")));
	
//---------------------------------------------------------

	ref_vec.push_back(1);
	ref_vec.push_back(3);
	ref_vec.push_back(4);
	ref_vec.push_back(7);
	ref_vec.push_back(11);
	ref_vec.push_back(12);
	ref_vec.push_back(13);
	ref_vec.push_back(18);
	ref_vec.push_back(24);
	ref_vec.push_back(30);
	ref_vec.push_back(34);
	ref_vec.push_back(50);
	ref_vec.push_back(52);
	ref_vec.push_back(53);
	ref_vec.push_back(54);
	ref_vec.push_back(55);
	ref_vec.push_back(56);
	ref_vec.push_back(61);
	ref_vec.push_back(68);
	ref_vec.push_back(71);
	ref_vec.push_back(80);
	ref_vec.push_back(90);
//-----------------------------------------------------------

	cout << "Test 2 - BST Without Balancing"<<endl<<endl;
	test_insert(tree);
	test_search(tree);
	test_delete(tree);
	test_height(tree);

	cout << endl << "Total Marks: " << marks << "/20" <<endl;
	if (marks == 20)
	{
		cout << "Wowow Amaze. Good Job! :)" << endl;
	}
	return 0;
}



// Test 2.1 - BST Insertion
void test_insert(shared_ptr<AVL<int,string>> tree)
{
	cout<<"Test 2.1 - BST Insertion"<<endl;
	test_vec.clear();
	int counter=0;

	// Case 2.1.1
	cout << 1;
	shared_ptr<AVL<int,string>>checktree (new AVL<int,string>(false));
	checktree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(20,"OneNodeTree")));

	int num = 0;
	if (checktree->getRoot() != NULL)
	{
		num = checktree -> getRoot()->key;
	}
	if (num == 20)
	{
		cout << "Test 2.1.1: Passed" << endl;
		counter++;
	}
	else
	{
		cout << "Test 2.1.1: Failed" << endl;
	}

	// Case 2.1.2
	checktree->insertNode(shared_ptr<node<int,string>>(make_shared<node<int,string>>(12,"Tree")));
	checktree->insertNode(shared_ptr<node<int,string>>(make_shared<node<int,string>>(24,"Tree")));

	int a=trav(checktree->getRoot(),0);

	int arr[3] = {12,20,24};
	int score = 0;
	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==arr[i])
		{
			score++;
		}		
	}

	if (score==3)
	{
		cout << "Test 2.1.2: Passed" << endl;
		counter = counter + 2;
	}
	else
	{
		cout << "Test 2.1.2: Failed" << endl;
	}

	test_vec.clear();

	// Case 2.1.3
	score = 0;
	a=trav(tree->getRoot(),0);
	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==ref_vec[i])
		{
			score++;
		}
	}

	if ((score/ref_vec.size())*2 == 2)
	{
		cout << "Test 2.1.3: Passed" << endl;
	}
	else
	{
		cout << "Test 2.1.3: Failed" << endl;
		score = 0;
	}
	counter = counter + (score/ref_vec.size())*2;

	cout<<"Total Points: "<< counter <<  "/5" << endl << endl;

	marks = marks + counter;
	return;

}

// Test 2.3 - BST Deletion
void test_delete(shared_ptr<AVL<int,string>> tree)
{
	cout<<"Test 2.3 - BST Deletion"<<endl;

	int counter=0;

	// Case 2.3.1
	AVL<int,string>* checktree=new AVL<int,string>(false);
	checktree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(20,"H")));
	checktree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(30,"H")));
	checktree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(12,"H")));

	checktree->deleteNode(30);
	test_vec.clear();
	int num =trav(checktree->getRoot(),0);
	int treearr[2] = {12,20};
	int score = 0;
	if (test_vec.size() == 2)
	{
		score++;
	}
	for (int i = 0; i < (test_vec.size()); i++)
	{
		if (test_vec[i] == treearr[i])
		{
			score++;
		}
	}

	if (score==3)
	{
		cout << "Test 2.3.1: Passed" << endl;
		counter = 1;
	}
	else
	{
		cout << "Test 2.3.1: Failed" << endl;
	}

	test_vec.clear();

	// Case 2.3.2
	checktree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(10,"R")));
	checktree->deleteNode(10);

	score = 0;
	int e=trav(checktree->getRoot(),0);
	if (test_vec.size() == 2)
	{
		score++;
	}
	for (int i = 0; i < (test_vec.size()); i++)
	{
		if (test_vec[i] == treearr[i])
		{
			score++;
		}
	}

	if (score==3)
	{
		cout << "Test 2.3.2: Passed" << endl;
		counter++;
	}
	else
	{
		cout << "Test 2.3.2: Failed" << endl;
	}

	test_vec.clear();

	// Case 2.1.3
	tree->deleteNode(90);
	tree->deleteNode(18);
	tree->deleteNode(50);
	tree->deleteNode(24);
	tree->deleteNode(68);
	tree->deleteNode(54);
	ref_vec=find_delete(90,ref_vec);
	ref_vec=find_delete(18,ref_vec);
	ref_vec=find_delete(50,ref_vec);
	ref_vec=find_delete(24,ref_vec);
	ref_vec=find_delete(68,ref_vec);
	ref_vec=find_delete(54,ref_vec);
	
	int a=trav(tree->getRoot(),0);

	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==ref_vec[i])
		{
			score++;
		}

	}

	if ((score/ref_vec.size())*2 == 2)
	{
		cout << "Test 2.3.3: Passed" << endl;
	}
	else
	{
		cout << "Test 2.3.3: Failed" << endl;
	}
	counter = counter + (score/ref_vec.size())*3;

	cout<<"Total Points: " << counter << "/5" <<endl;

	marks = marks + counter;
	return;


}

// Test 2.2 : Search
void test_search(shared_ptr<AVL<int,string>> tree)
{
	cout<< "Test 2.2 - BST Search"  << endl;
	vector<int> ref_search;
	int counter=0;
	test_vec.clear();

	int arr[5] = {13,11,52,90,24};

	// Case 2.2.1
	for (int i = 0; i < 5; i++)
	{
		if (tree->searchNode(arr[i]))
		{
			test_vec.push_back(tree->searchNode(arr[i])->key);
		}
	}

	ref_search.push_back(13);
	ref_search.push_back(11);
	ref_search.push_back(52);
	ref_search.push_back(90);
	ref_search.push_back(24);

	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==ref_search[i])
		{
			counter++;
		}

	}

	counter = (counter/ref_search.size())*5;
	if (counter == 5)
	{
		cout << "Test 2.2.1: Passed" << endl;
		counter = 3;
	}
	else
	{
		counter = 0;
		cout << "Test 2.2.1: Failed" << endl;
	}

	// Case 2.2.2
	if (tree->searchNode(14) == NULL && tree->searchNode(90)!=NULL)
	{
		counter = counter + 2;
		cout << "Test 2.2.2: Passed" << endl;
	}
	else
	{
		cout << "Test 2.2.2: Failed" << endl;
	}

	cout<< "Total Points: "<< counter <<"/5"<<endl<<endl;

	marks = marks + counter;
	return;
}

// Test 2.4 : Height
void test_height(shared_ptr<AVL<int,string>> tree)
{
	cout<< endl << "Test 2.4 - BST Height"<<endl;
	test_vec.clear();
	int counter=0;

	// Case 2.4.1 - Single Node Tree Height
	shared_ptr<AVL<int,string>> checktree(new AVL<int,string>(false));
	checktree->insertNode(shared_ptr<node<int,string>> (make_shared<node<int,string>>(1,"singlennodetest")));
	int h = checktree->height(checktree->getRoot());

	if (h==1)
	{
		cout << "Test 2.4.1: Passed" << endl;
		counter = counter + 2;
	}
	else
	{
		cout << "Test 2.4.1: Failed" << endl;
	}

	// Case 2.4.2 - Main Height Test
	h=tree->height(tree->getRoot());
	if (h==6)
	{	
		cout << "Test 2.4.2: Passed" << endl;
		counter= counter + 3;
	}
	else
	{
		cout << "Test 2.4.2: Failed" << endl;
	}

	cout << "Total Points: "<<counter<<"/5"<<endl;

	marks = marks + counter;
}

int trav(shared_ptr<node<int,string>> P,int i)
{
	if (P == NULL)
	{
		return 0;
	}
	if(P->left)
		i=trav(P->left,i);
	test_vec.push_back(P->key);
	i++;
	if(P->right)
		i=trav(P->right,i);
	return i;

}

vector<int> find_delete(int k,vector<int> v)
{
	for (int i=0;i<v.size();i++)
	{
		if (v.at(i)==k)
		{
			v.erase(v.begin()+i);
			return v;
		}
	}
}