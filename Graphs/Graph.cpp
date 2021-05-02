#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"

//
// Add your constructor code here. It takes the filename and loads
// the graph from the file, storing into your representation of the
// graph. MAKE SURE you use the addEdge function here, and pass the
// flag to it too.
//
Graph::Graph(string filename, bool flag)
{
	// TODO
	ifstream graphData(filename);
	string data;
	getline(graphData, data);
	size = data[2] - 48;
	graph.reserve(size);
	getline(graphData, data);
	while(getline(graphData, data))
	{
		int weight = data[4] - 48;
		addEdge(data[0], data[2], weight, flag);
	}
}

//
// Adds an edge to the graph. Useful when loading the graph from file.
// The flag determines whether the edges will be added according to a
// directed or undirected graph.
//
void Graph::addEdge(char start, char end, int weight, bool flag)
{
	// TODO
	if(flag)
	{
		shared_ptr<Edge> graphEdge = make_shared<Edge>();
		graphEdge->origin = start;
		graphEdge->dest = end;
		graphEdge->weight = weight;
		int index = findIndex(start);
		graph[index].push_back(graphEdge);
	}
	else
	{
		shared_ptr<Edge> graphEdge = make_shared<Edge>();
		graphEdge->origin = start;
		graphEdge->dest = end;
		graphEdge->weight = weight;
		int index = findIndex(start);
		graph[index].push_back(graphEdge);

		graphEdge = make_shared<Edge>();
		graphEdge->origin = end;
		graphEdge->dest = start;
		graphEdge->weight = weight;
		index = findIndex(end);
		graph[index].push_back(graphEdge);
	}
}

int Graph::findIndex(char start)
{
	int index = 0;
	while(!graph[index].empty())
	{
		if(graph[index][0]->origin == start)
		{
			break;
		}
		index++;
	}
	return index;
}

//
// Returns the display of the graph as a string. Make sure
// you follow the same output as given in the manual.
//
string Graph::display()
{
	string graphData = "";
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < graph[i].size(); ++j)
		{
			concatEdge(graph[i][j], graphData);
		}
		graphData += "\n";
	}
	return graphData;
}

void Graph::concatEdge(shared_ptr<Edge> data, string &graphData)
{
	graphData += "(";
	graphData += data->origin;
	graphData += ',';
	graphData += data->dest;
	graphData += ',';
	graphData += char(data->weight + 48);
	graphData += ')';
	graphData += ' ';
}

// Returns whether the destination city is reachable from the
// origin city or not.
//
bool Graph::Reachable(char start, char end)
{
	vector<char> visited;
	vector<char> frontier;
	frontier.push_back(start);
	while(!frontier.empty())
	{
		char currentNode = frontier.back();
		frontier.pop_back();
		if(currentNode == end)
		{
			return true;
		}
		if(!(find(visited.begin(), visited.end(), currentNode) != visited.end()))
		{
			visited.push_back(currentNode);
			int index = findIndex(currentNode);
			for(int i = 0; i < graph[index].size(); ++ i)
			{
				frontier.push_back(graph[index][i]->dest);
			}
		}
	}
	return false;
}

//
// Returns the weight of shortest path between origin and destination cities.
// Return -1 if no path exists.
//
int Graph::Dijkstra(char start, char dest)
{
	if(!Reachable(start, dest))
	{
		return -1;
	}

	const int INT_MAX = 2147483647;

	vector<char> nodes;
	nodes.resize(size);
	int k = 0;
	for(int i = 0; i < size; ++i)
	{
		if(!graph[i].empty())
		{
			if(find(nodes.begin(), nodes.end(), graph[i][0]->origin) == nodes.end())
			{
				nodes[k] = graph[i][0]->origin;
				k++;
			}
			if(find(nodes.begin(), nodes.end(), graph[i][0]->dest) == nodes.end())
			{
				nodes[k] = graph[i][0]->dest;
				k++;
			}
		}
	}

	vector<bool> processed;
	processed.resize(size, false);

	vector<int> cost;
	cost.resize(size, INT_MAX);

	int index = arrayIndex(nodes, start);
	cost[index] = 0;
	processed[index] = true;

	for(int i = 0; i < graph[findIndex(start)].size(); ++i)
	{
		int indexNew = arrayIndex(nodes, graph[findIndex(start)][i]->dest);
		cost[indexNew] = graph[findIndex(start)][i]->weight;
	}

	for(int i = 0; i < size - 1; ++i)
	{
		int index = minCost(cost, processed);
		processed[index] = true;
		for(int j = 0; j < graph[findIndex(nodes[index])].size(); ++j)
		{
			if(cost[arrayIndex(nodes, graph[findIndex(nodes[index])][j]->dest)] > graph[findIndex(nodes[index])][j]->weight + cost[index])
			{
				cost[arrayIndex(nodes, graph[findIndex(nodes[index])][j]->dest)] = graph[findIndex(nodes[index])][j]->weight + cost[index];
			}
		}
	}
	return cost[arrayIndex(nodes, dest)];
}

int Graph::arrayIndex(vector<char> nodes, char searchNode)
{
	int index = 0;
	for(int i = 0; i < nodes.size(); ++i)
	{
		if(nodes[i] == searchNode)
		{
			index = i;
			break;
		}
	}
	return index;
}

int Graph::minCost(vector<int> cost, vector<bool> processed)
{
	const int INT_MAX = 2147483647;
	int index = 0;
	int value = INT_MAX;
	for(int i = 0; i < cost.size(); ++i)
	{
		if(processed[i])
		{
			continue;
		}
		else
		{
			if(value > cost[i])
			{
				value = cost[i];
				index = i;
			}
		}
	}
	return index;
}

//
// Implement topological sort on the graph and return the string of the sorted cities
//
string Graph::topoSort()
{
	string sorted = "";
	int nodeSize = size;
	const int INT_MAX = 2147483647;

	vector<char> processed;

	vector<char> nodes;
	nodes.resize(nodeSize, ' ');
	int k = 0;
	for(int i = 0; i < nodeSize; ++i)
	{
		if(!graph[i].empty())
		{
			if(find(nodes.begin(), nodes.end(), graph[i][0]->origin) == nodes.end())
			{
				nodes[k] = graph[i][0]->origin;
				k++;
			}
			if(find(nodes.begin(), nodes.end(), graph[i][0]->dest) == nodes.end())
			{
				nodes[k] = graph[i][0]->dest;
				k++;
			}
		}
	}

	while(nodeSize != 0)
	{
		vector<int> inDegree;
		inDegree.resize(nodeSize, INT_MAX);
		int k = 0;
		for(int i = 0; i < nodes.size(); ++i)
		{
			inDegree[i] = findInDegree(nodes[i], processed);
		}

		for(int i = 0; i < inDegree.size(); ++i)
		{
			if(inDegree[i] == 0)
			{
				sorted += nodes[i];
				processed.push_back(nodes[i]);
				nodes.erase(nodes.begin() + i);
				inDegree.erase(inDegree.begin() + i);
				nodeSize--;
			}
		}
	}
	return sorted;
}

int Graph::findInDegree(char findNode, vector<char> processed)
{
	int inDegree = 0;
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < graph[i].size(); ++j)
		{
			if(graph[i][j]->dest == findNode && find(processed.begin(), processed.end(), graph[i][j]->origin) == processed.end())
			{
				inDegree++;
			}
		}
	}
	return inDegree;
}
#endif
