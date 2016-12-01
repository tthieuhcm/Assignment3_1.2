// class cung cap boi HLCT
/*
-Cung cap class node,list de thuc hien linkList
-Cung cap class myVertex,myEdge,myGraph: sua doi lai bien processed trong myVertex(bool->int) va them bien processed(int)
	+Cung cap ham duyet DFS 
*/


#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class node {
public:
	node() :pNext(nullptr) {
		data = 0;
	}
	int data;
	node* pNext;

};
class _List {
public:
	_List() :pHead(nullptr) { size = 0; };
	node* pHead;
	int size;

};
//For circular usage
/**
* \class Edge
* \brief Class Edge for Graph structure
*
* This is implemented accordingly to the book Data Structures: A Pseudocode Approach with C. \n
* We don't allow duplicate edges in this assignment since there is no weight. \n
* Each Edge instance has two member: \c destination and \c nextEdge. \n
* \c destination is the Vertex that this Edge will point to. \n
* \c nextEdge is another Edge came from the same source of this Edge. \n
*/
class myEdge;

/**
* \class Vertex
* \brief Class Vertex for Graph structure
*
* This is implemented accordingly to the book Data Structures: A Pseudocode Approach with C. \n
* This ADT is actually just a linked list. \n
* <b>Note that two vertices connected by nextVertex DOESN'T MEAN that they are connected in the graph G.</b> \n
* <b>Vertex A actually connects to Vertex B only if and only if there is an Edge in \c firstEdge linked list that point to B.</b> \n
*/

class myVertex {
public:
	// phuc vu cho kiem tra cay AVL
	int height;
	/**
	* \var data
	* \brief Vertex data
	*/
	int data;

	/**
	* \var inDegree
	* \brief Number of edges that point to this Vertex
	*/
	int inDegree;


	/**
	* \var outDegree
	* \brief Number of edges that point out from this Vertex
	*/
	int outDegree;

	/**
	* \var nextVertex
	* \brief Linked list, point to the next Vertex added into the Graph (or NULL). \n
	* This does not mean that they are connected by an edge in the Graph. \n
	*/
	myVertex* nextVertex;

	/**
	* \var firstEdge
	* \brief Linked list, point to the first Edge of this Vertex (or NULL). \n
	* In this linked list, if there is an Edge that point to another Vertex then this Vertex and that Vertex are connected in Graph G. \n
	*/
	myEdge* firstEdge;

	/**
	* \var processed
	* \brief For traversal purpose, tell us if a node has been visited or not. \n
	*/
	int processed;

	/**
	* \brief Default constructor. \n Create a Vertex with data=0
	*/
	myVertex();

	/**
	* \brief Create a Vertex with \c data.
	*/
	myVertex(int data);
};

//Linked list that contains Edges from a Vertex to other Vertices
//This class helps we to connect Vertices in a graph
class myEdge {
public:
	/**
	* \var destination
	* \brief The Vertex that this Edge will point to.
	*/
	myVertex* destination;

	/**
	* \var nextEdge
	* \brief Another Edge came from the same source Vertex with this Edge.
	*/
	myEdge* nextEdge;

	/**
	* \brief Default constructor. \n
	* This is illegal because an Edge should always come with a destination. \n
	* Use the other constructor instead. \n
	*/
	/**
	*/
	int processed;
	/**
	* \brief Create an Edge that point to \c destination.
	*/
	myEdge(myVertex*);
};

/**
* \class Graph
* \brief Class Graph data structure
*
* This is implemented accordingly to the book Data Structures: A Pseudocode Approach with C. \n
* Note that in this implementation, we do not allow data duplication.\n
* Although data duplication is common in real-life applications, it is avoided here to ease the workload of this assignment.\n
*/
class myGraph {
public:
	/**
	* \var gHead
	* \brief Store the first Vertex inserted into this Graph. \N
	* Brought gHead back to public to allow easier coding for students
	*/
	myVertex* gHead;

	/**
	* \var size
	* \brief Number of Vertices in the Graph
	*/
	int size;

	/**
	* \brief Helper function created to remove duplicate codes
	*/
	bool InsertEdgeFromVertices(myVertex* from, myVertex* to);

	/**
	* \brief Default constructor.
	*/
	myGraph();

	/**
	* \brief Constructor that takes a Vertex as the first Vertex to this Graph
	*/
	myGraph(myVertex* gHead);

	/**
	* \brief Insert new Vertex into the graph
	*/
	bool InsertVertex(myVertex*);

	/**
	* \brief Create a new Vertex with \c data and insert it into the Graph.
	*/
	bool InsertVertex(int data);

	/**
	* \brief Remove Vertex from the Graph.
	*/
	bool RemoveVertex(myVertex*);

	/**
	* \brief Remove Vertex with \c data=reData from the Graph.
	*/
	bool RemoveVertex(int reData);

	/**
	* \brief Check if a Vertex exists in the Graph
	*/
	bool VertexExist(myVertex* v);

	/**
	* \brief Check if a Vertex exists in the graph using the Vertex data
	*/
	bool VertexExist(int vData);

	/**
	* \brief Return Vettex* given \c data
	*/
	myVertex* GetVertex(int);

	/**
	* \brief Insert new Edge into the graph using 2 Vertex
	*/
	bool InsertEdge(myVertex* from, myVertex* to);

	/**
	* \brief Create an Edge betweem two nodes with \c fromData and \c toData
	*/
	bool InsertEdge(int fromData, int toData);

	/**
	* \brief Insert new Edge into the graph using a Vertex and an Edge
	*/
	bool InsertEdge(myVertex* from, myEdge* from_to);

	/**
	* \brief Remove an Edge from the graph using 2 Vertex
	*/
	bool RemoveEdge(myVertex* from, myVertex* to);

	/**
	* \brief Remove the Edge betweem two nodes with \c fromData and \c toData
	*/
	bool RemoveEdge(int fromData, int toData);

	/**
	* \brief Remove an Edge using a Vertex and an Edge
	*/
	bool RemoveEdge(myVertex* from, myEdge* from_to);

	/**
	* \brief Print the graph
	*/
	void Print();

	/**
	* \brief DFS
	*/
	void DFS(myVertex* v,_List&,void(*func)(_List&,int));


	//
	myVertex* at(int i);
};


void insert(_List&, int);
bool ReadArrayInputOfReverseGraph(string filename, int*& vertexDataArr, int& vertexCount, int**& edgeDataArr, int& edgeCount);
bool ReadLKGraph(string filename, int**& vertexDataArr, int& vertexCount);
#endif