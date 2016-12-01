#include"AVLTree.h"
#include"Graph.h"
#include"Heap.h"
#include"Node.h"
#include"InputReader.h"
#include <iomanip>
#include <list>
#define INFINITY 2147483647
struct List{
	Node* data;
	List* pNext;
};

#pragma region Classes and Fuctions Used in E18 and E19

class VertexW;
class EdgeW :public Edge
{
public:
	int weight;
	EdgeW* nextEdgeW;
	VertexW* destinationW;

	EdgeW(VertexW*,Vertex*, int);
};

class VertexW :public Vertex
{
public:
	EdgeW* firstEdgeW;
	VertexW* nextVertexW;
	int dist;			//Distance used while finding shortest path
	VertexW* path;		//Vertex that goes before it in a path.

	VertexW();
	VertexW(int data);
};

class GraphW : public Graph
{

public:
	VertexW* gHeadW;

	GraphW();

	GraphW(VertexW* gHeadW);

	bool InsertVertexW(int data);

	VertexW* GetVertexW(int);

	bool InsertEdgeFromVertices(VertexW* from, VertexW* to, int weight);

	bool InsertEdgeW(int fromData, int toData, int weight);

	void Print();
};

bool UnProcessedExist(GraphW, list<int>);

bool CheckDataExist(int , list<int>);

void printPath(int ,int  , GraphW , list<int> );

void AdjacencyMattoGraph(int**, int, GraphW&);

VertexW* GetSmallestUnknownDistanceVertexW(GraphW graph, list<int> passList);

void GraphToAdjacencyMatrix(int, int**,Graph);
#pragma endregion

void E1();
void E2();
void E3();
void E4();
void E5();
void E6();
void E7();
void E8();
void E9();
void E10();
void E11();
void E12();
void E13();
void E14();
void E15();
void E16();
void E17();
void E18();
void E19();
void E20();