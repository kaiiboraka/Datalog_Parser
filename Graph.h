#include <iostream>
#include "Helper.h"
#include <list>
#include <set>

using namespace std;

template <typename T>
struct GraphNode
{
	T value;
	bool visited = false;
	list<Index> neighborsList;
	Count neighbors = 0;

	GraphNode() = default;
	explicit GraphNode(const T& value) : value{value}
	{

	}

	void push_back(Index neighbor)
	{
		neighborsList.push_back(neighbor);
		neighbors = neighborsList.size();
	}

	list<Index>::iterator begin()
	{
		return neighborsList.begin();
	}

	list<Index>::iterator end()
	{
		return neighborsList.end();
	}

	GraphNode& operator=(bool visit)
	{
		visited = visit;
		return *this;
	}
	bool operator==(bool visit) const
	{
		return (visited == visit);
	}
	bool operator!=(bool visit) const
	{
		return (visited != visit);
	}
	bool operator!() const
	{
		return (!visited);
	}
};

//graph class for DFS travesal
template <typename T>
class DFSGraph
{
	vector<GraphNode<T>> nodes;
	Indices postOrder{};

	void VisitNodes(Index current)
	{
		// current node v is visited
		nodes[current] = true;

		// recursively process all the adjacent vertices of the node
		for (Index other = 0; other < nodes[current].neighbors; other++)
		{
			if(!nodes[other]) VisitNodes(other);
		}
		postOrder.push_back(current);
	}

	int TestGraph();

public:
	[[nodiscard]] vector<GraphNode<T>> GetNodes() const
	{
		return nodes;
	}

	[[nodiscard]] const Indices& GetPostOrder() const
	{
		return postOrder;
	}
	Indices GetPostOrderReverse() const
	{
		auto temp = postOrder;
		reverse(temp.begin(), temp.end());
		return temp;
	}

	explicit DFSGraph(set<T> givenValues = {})
	{
		for (auto thing : givenValues)
		{
			nodes.push_back(GraphNode<T>{thing});
		}
	}

	explicit DFSGraph(vector<T> givenValues)
	{
		for (auto thing : givenValues)
		{
			nodes.push_back(GraphNode<T>{thing});
		}
	}

	explicit DFSGraph(vector<GraphNode<T>> givenNodes)
	{
		nodes = givenNodes;
	}

	void ResetVisits()
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			nodes[i] = false;
		}
	}

	void AddEdge(Index i, Index neighbor)
	{
		nodes[i].push_back(neighbor); // Add node to i’s list.
	}

	Indices DFS()    // DFS traversal function
	{
		// initially none of the vertices are visited
		ResetVisits();

		// explore the vertices one by one by recursively calling  VisitNodes
		for (Index i = 0; i < nodes.size(); i++)
		{
			if (!nodes[i].visited) VisitNodes(i);
		}

		return postOrder;
	}

	GraphNode<T> at(Index i)
	{
		return nodes.at(i);
	}
};
template <typename T>
int DFSGraph<T>::TestGraph()
{
	// Create a graph
	DFSGraph<int> gdfs;
	gdfs.AddEdge(0, 1);
	gdfs.AddEdge(0, 2);
	gdfs.AddEdge(0, 3);
	gdfs.AddEdge(1, 2);
	gdfs.AddEdge(2, 4);
	gdfs.AddEdge(3, 3);
	gdfs.AddEdge(4, 4);

	cout << "Depth-first search of the given graph:" << endl;
	gdfs.DFS();

	return 0;
}