#include "Header.h"

bool ReadLKGraph(string filename, int**& vertexDataArr, int& vertexCount) {
	ifstream myfile(filename.c_str());
	string line;
	vertexCount = 0;
	vertexDataArr = NULL;
	cout << "Reading Graph data: \n";
	if (myfile.is_open()) {
		//Read vertex count on the first line
		myfile >> vertexCount;

		//Create an array to store the data
		vertexDataArr = new int*[vertexCount];

		//Read them one by one
		for (int i = 0; i < vertexCount; i++) {
			vertexDataArr[i] = new int[vertexCount];
			for (int j = 0; j < vertexCount; j++) {
				myfile >> vertexDataArr[i][j];
			}
		}
	}
	else {
		cout << "Can't open file " << filename << ".";
		return false;
	}
	return true;
}
void E15(){
	int** vertexDataArr = nullptr;
	int vertexCount = 0;
	// Input
	ReadLKGraph("E15.txt", vertexDataArr, vertexCount);
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