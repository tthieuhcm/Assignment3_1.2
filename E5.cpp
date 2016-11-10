#include "Graph.h"
#include "InputReader.h"
using namespace std;
void Graph::Print(){
	Vertex *showVertex = gHead;
	while (showVertex)
	{
		cout << showVertex->data << "->";
		Edge *showEdge = showVertex->firstEdge;
		while (showEdge)
		{
			cout << showEdge->destination->data << "->";
			showEdge = showEdge->nextEdge;
		}
		cout << "NULL" << endl << "|\n";
		showVertex = showVertex->nextVertex;
	}
	cout << "NULL\n";
}
void E5(){

	// get input
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	ReadArrayInputOfGraph("E5.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//create graph
	Graph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(vertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0],edgeDataArr[i][1]);

	// print graph
	graph.Print();
}