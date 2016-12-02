#include "Header.h"

void E11()
{
	int *arr = NULL;
	int *vertexDataArr, vertexCount, **edgeDataArr, edgeCount;
	ReadArrayInputOfGraph("E11.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//create graph
	Graph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(vertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);

	// print graph
	graph.Print();

	// Chuyển graph về ma trận liền kề
	int **matran = new int*[vertexCount + 1];
	for (int i = 0; i < vertexCount + 1; i++)
		*(matran + i) = new int[vertexCount + 1];
	matran[0][0] = -1;
	int i = 1;
	Vertex *add = graph.gHead;
	while (add)
	{
		matran[0][i] = add->data;
		matran[i][0] = add->data;
		Vertex *check = graph.gHead;
		int j = 1;
		while (check)
		{
			Edge *edge = add->firstEdge;
			bool Has = false;
			while (edge)
			{
				if (edge->destination == check)
				{
					Has = true;
					break;
				}
				edge = edge->nextEdge;
			}
			if (Has) matran[i][j] = 1;
			else matran[i][j] = 0;
			check = check->nextVertex;
			j++;
		}
		add = add->nextVertex;
		i++;
	}

	// In ma trận liền kề
	cout << "Ma tran lien ke cua graph:\n";
	cout << setw(5) << right << "|";
	for (int i = 0; i < vertexCount + 1; i++)
	{
		for (int j = 0; j < vertexCount + 1; j++)
			if (i != 0 || j != 0) cout << setw(4) << left << matran[i][j] << right << "|";
		cout << endl;
	}
}
