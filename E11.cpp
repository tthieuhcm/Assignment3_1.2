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

	// In ma trận liền kề
	cout << "Ma tran lien ke cua graph:\n";
	cout << setw(5)   << right <<"|";
	Vertex* show = graph.gHead;
	while (show)
	{
		cout << setw(4) << left << show->data << right << "|";
		show = show->nextVertex;
	}
	cout << endl;
	show = graph.gHead;
	while (show)
	{
		cout << setw(4) << left << show->data << right << "|";
		Vertex *check = graph.gHead;
		while (check)
		{
			Edge *edge = show->firstEdge;
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
			if (Has) cout << setw(4) << left << 1 << right << "|";
			else cout << setw(4) << left << 0 << right << "|";
			check = check->nextVertex;
		}
		cout << endl;
		show = show->nextVertex;
	}

	// delete
	/*while (graph.gHead)
		graph.RemoveVertex(graph.gHead);*/
}