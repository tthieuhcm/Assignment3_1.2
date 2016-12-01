#include "Header.h"


void E15(){
	int** vertexDataArr = nullptr;
	int vertexCount = 0;
	// Input
	ReadLKGraph("input/E15.txt", vertexDataArr, vertexCount);
	cout << "MA TRAN" << endl;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++)
			cout << vertexDataArr[i][j]<<"  ";
		cout << endl;
	}
	//xu li
	int **edgeDataArr;
	int edgeCount=0;
	//Dem so cach xuat phat tu 1 dinh
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			if (vertexDataArr[i][j] == 1) {
				edgeCount++;
			}
		}
	}
	// EdgeDataArr
	edgeDataArr = new int*[edgeCount];
	for (int i = 0; i < edgeCount; i++)
		edgeDataArr[i] = new int[2];
	int dem=0;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			if (vertexDataArr[i][j] == 1) {
				edgeDataArr[dem][0] = i+1;
				edgeDataArr[dem][1] = j + 1;
				dem++;
			}
		}		
	}

	int* modiVertexDataArr = new int[vertexCount];
	for (int i = 0; i < vertexCount; i++)
		modiVertexDataArr[i] = i+1;
	// In ma tran
	cout << endl;
	myGraph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(modiVertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	graph.Print();

}