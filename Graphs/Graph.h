#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
#include <list>
#include <sstream>
#include <memory>
// You may include more libraries.

using namespace std;

class Edge
{
	// You may add more variables and functions in this class
public:
	char origin;
	char dest;
	int weight;
};

class Graph
{
	//
	// You are required to implement the data structures for the graph. Two representations
	// you will be familiar with are adjacency list and adjacency matrix.
	// You can choose to go with any representation you wish.
	//
public:
	//
	// To get you started, we have written the definitions for both adjacency list
	// and matrix. You can uncomment whichever one you like. You are also free to change
	// the data structure to your liking. HOWEVER:
	// MAKE SURE YOU DO NOT CHANGE NAME FROM 'graph' OTHERWISE THE TESTS WILL FAIL.
	//
	// Matrix:
	vector<vector<shared_ptr<Edge>>> graph;
	//
	// List:
	// vector<list<shared_ptr<Edge>>> graph;
	//
	int size = 0;
	Graph(string filename, bool flag);
	int findIndex(char start);
	void addEdge(char start, char end, int weight, bool flag);
	string display(); // displays the graph
	void concatEdge(shared_ptr<Edge> data, string &graphData);
	bool Reachable(char start, char dest);
	int arrayIndex(vector<char> nodes, char searchNode);
	int minCost(vector<int> cost, vector<bool> processed);
	int Dijkstra(char start, char dest);
	string topoSort();
	int findInDegree(char findNode, vector<char> processed);
	//
	// Add any helper function definitions here...
	//
	// We encourage you to make a helper function that can easily translate
	// a city name to its index.
	// ...
	//
};

#endif
