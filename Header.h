#include"AVLTree.h"
#include"Graph.h"
#include"Heap.h"
#include"Node.h"
#include"InputReader.h"
#include "myGraph.h"
#include <iomanip>
#include <list>
#include <string> 
#include <vector> 
#include <map> 
#include <set> 
#include <algorithm>
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

#pragma region Functions for E20
vector<vector<int> > dijkstra(vector<vector<int> > graph);

vector<vector<int> > reindex(vector<vector<int> > graph, vector<int> index);

vector<int> inv(vector<int> index);

vector<int> transform(map<vector<int>, vector<int> > signmatrixA,
	map<vector<int>, vector<int> > signmatrixB, vector<int> vertexA,
	vector<int> vertexB, vector<int> isoB);

void graphToAdMat(Graph graph, int count, vector<vector<int>> &adMat);

int getDataAt(int i, Graph graph);

void getOutDegree(vector< vector<int> > graphA, int nA, vector<int> &degA);

void shortestPath(int count, int N, vector<vector<int> > graph, vector<vector<int> > &shortest_path);

void createFrequencyTable(int vertexCount, map<vector<int>, int> distaceTable, map<vector<int>, int> nV, map<vector<int>, int> nE, map<vector<int>, vector<int> > &frequency);

void createPairGraph(vector< vector<int> > &graph, int vertexCount, map<vector<int>, set<int> > &PairGraph, map<vector<int>, int> &d, map<vector<int>, int> &nV, map<vector<int>, int> &nE);

void addFrequency(map<vector<int>, vector<int> > &frequency, int vertexCount, map<vector<int>, int> &d, map<vector<int>, int> &nV, map<vector<int>, int> &nE);

void classDivision(vector<vector<int> > tvss, int vertexCount, vector<int> &GraphClass);

void signMatrix(int vertexCount, vector<int> vertexList, map<vector<int>, int> &d, map<vector<int>, int> &nV, map<vector<int>, int> &nE, map<vector<int>, vector<int> > &signmatrix);

void sortIndex(int vertexCount, vector<vector<int> > neighbor, vector<vector<int> > distance, vector<int> &mainindex);

void initialStep(vector< vector<int> > adMat, vector<vector<int> > &distance, vector<vector<int> > &neighbor);

void sortFrequency(map<vector<int>, vector<int> > frequency, vector<vector<int> > &tvss);
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