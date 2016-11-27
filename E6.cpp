#include "Header.h"

bool Graph::RemoveVertex(Vertex* v)
{
	if (!gHead) return false;
	if (!VertexExist(v)) return false;

	// Tìm Vertex bị xóa trong Graph
	Vertex *DeleteVertex = gHead;
	while (DeleteVertex->data != v->data)
		DeleteVertex = DeleteVertex->nextVertex;

	// Xóa cạnh nối từ Vertex bị xóa
	while (DeleteVertex->firstEdge)
		Graph::RemoveEdge(DeleteVertex, DeleteVertex->firstEdge->destination);

	//Xóa cạnh nối tới Vertex bị xóa
	Vertex *findVertex = gHead;
	while (findVertex)
	{
		Graph::RemoveEdge(findVertex, DeleteVertex);
		findVertex = findVertex->nextVertex;
	}

	// Xóa Vertex
	if (DeleteVertex == gHead)
	{
		gHead = gHead->nextVertex;
	}
	else
	{
		Vertex *Previous = gHead;
		while (Previous->nextVertex->data != DeleteVertex->data)
			Previous = Previous->nextVertex;
		Previous->nextVertex = DeleteVertex->nextVertex;
	}
	delete DeleteVertex;
	size--;
	if (!size) gHead = NULL;
	return true;
}
bool Graph::RemoveVertex(int reData)
{
	if (!gHead) return false;
	Vertex* v = gHead;
	while (v && v->data != reData)
		v = v->nextVertex;
	if (!v) return false;
	if (Graph::RemoveVertex(v)) return true;
	return false;
}

bool Graph::RemoveEdge(Vertex* from, Vertex* to)
{
	if (!gHead) return false;
	if (!VertexExist(from) || !VertexExist(to)) return false;
	/**************************************/
	Vertex *findVertex = gHead;
	while (findVertex->data != from->data)
		findVertex = findVertex->nextVertex;
	/**************************************/
	if (!findVertex->firstEdge) return false;
	Edge *findEdge = findVertex->firstEdge;
	while (findEdge && findEdge->destination->data != to->data)
		findEdge = findEdge->nextEdge;
	if (!findEdge) return false;
	else if (findEdge == findVertex->firstEdge)
	{
		findVertex->firstEdge = findEdge->nextEdge;
		delete findEdge;
	}
	else
	{
		Edge *Previous = findVertex->firstEdge;
		while (Previous->nextEdge != findEdge)
			Previous = Previous->nextEdge;
		Previous->nextEdge = findEdge->nextEdge;
		delete findEdge; 
	}
	return true;
}
bool Graph::RemoveEdge(int fromData, int toData)
{
	if (!gHead) return false;
	Vertex *from = gHead;
	while (from->data != fromData)
		from = from->nextVertex;
	Vertex *to = gHead;
	while (to->data != toData)
		to = to->nextVertex;
	if (!from || !to) return false;
	if (Graph::RemoveEdge(from, to)) return true;
	return false;
}
bool Graph::RemoveEdge(Vertex* from, Edge* from_to)
{
	if (Graph::RemoveEdge(from, from_to->destination)) return true;
	return false;
}

void E6(){

	// get input
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	ReadArrayInputOfGraph("E6.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//create graph
	Graph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(vertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);

	// print graph
	graph.Print();
	int Vertexdata;
	do{
		cout << "Nhap data Vertex can xoa: ";
		cin >> Vertexdata;
		if (Vertexdata != -1)
		{
			if (!graph.RemoveVertex(Vertexdata)) cout << "Khong the remove" << endl;
			else
			{
				cout  << "Cay nhi phan hien hanh:\n";
				graph.Print();
			}
		}
	} while (Vertexdata != -1);
}
