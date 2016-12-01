#include "Header.h"



void E16() {
	bool isStrongConnect=true;
	// get input
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	ReadArrayInputOfGraph("input/E16.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//create graph
	myGraph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(vertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	graph.Print();

	// xu li(Duyet DFS tu dinh dau tien,  luu tat ca cac dinh da duyet qua, neu so dinh bang so dinh trong do thi-1 thi se co duong di tu v den tat ca cac dinh)
	//****
	_List tempList;
	graph.DFS(graph.gHead, tempList, insert);
	if (tempList.size == graph.size)
		isStrongConnect = true;
	else{
		isStrongConnect = false;
		cout << "NOT STRONG CONNECTED";
		return;
	}
		
	////
	// neu truong hop tren dung, dao chieu tat ca cac canh bang cach nhap nguoc
	int *_rvertexDataArr;
	int _rvertexCount;
	int **_redgeDataArr;
	int _redgeCount;
	ReadArrayInputOfReverseGraph("input/E16.txt", _rvertexDataArr, _rvertexCount, _redgeDataArr, _redgeCount);

	//create graph
	myGraph reverseGraph;
	for (int i = 0; i < _rvertexCount; i++)
		reverseGraph.InsertVertex(_rvertexDataArr[i]);
	for (int i = 0; i < _redgeCount; i++)
		reverseGraph.InsertEdge(_redgeDataArr[i][0], _redgeDataArr[i][1]);
	reverseGraph.Print();

	_List tempreList;
	reverseGraph.DFS(reverseGraph.gHead, tempreList, insert);
	
	if (tempreList.size == graph.size)
		isStrongConnect = true;
	else {
		isStrongConnect = false;
		cout << "NOT STRONG CONNECTED";
		return;
	}
	cout << "STRONG CONNECTED";
	// xu li tuong tu nhu tren(DFS)
}