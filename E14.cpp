#include "Header.h"



void ChuTrinh(myVertex*, myEdge*, int&);
void E14() {

	// get input
	int *vertexDataArr;
	int vertexCount;
	int **edgeDataArr;
	int edgeCount;
	ReadArrayInputOfGraph("input/E14.txt", vertexDataArr, vertexCount, edgeDataArr, edgeCount);

	//create graph
	myGraph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(vertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	graph.Print();
	// xu li tien lap
	if (graph.gHead == nullptr)
		return;
	myVertex* pVer = graph.gHead;
	myEdge* pEdge;

	int dem = 0;

	// duyet qua tat ca cac dinh co process!=1 trong do thi
	//Duyet theo canh

	for(int i=0; i<graph.size;i++){
		if (pVer!=nullptr) {
			pEdge = pVer->firstEdge;
			while (pEdge != nullptr){
				ChuTrinh(pVer, pEdge, dem);
				pEdge = pEdge->nextEdge;  // duyet tat ca cac canh trong first edge cua Dinh
			}
			myVertex* pPast = graph.gHead;
			for (int i = 0; i < graph.size; i++) {
				if (pPast->processed == 3)
					pPast->processed = 1;
				pPast = pPast->nextVertex;

			}
			// Dinh da duyet xong
			pVer = pVer->nextVertex;
			
		}
	}

	cout << "SO CHU TRINH = " << dem;

}

void ChuTrinh(myVertex* pVer, myEdge* pEdge, int& dem){
	if (pEdge == nullptr)
		return;
	myVertex* pNext = pEdge->destination;
	if (pNext->processed == 1) // da duyet qua hoan toan
		return;
	if (pNext->processed == 2) { // con trong de quy, la canh duyet o truoc
		dem++;
		return;
	}
	if(pNext->processed == 3){// con trong 1 vong de quy, tuy nhien canh da duoc duyet het tat ca cac canh ra

		myEdge* pTemp = pNext->firstEdge;
		pNext->processed = 4;// xu li truong hop lap vo han
		while (pTemp != nullptr) {
				ChuTrinh(pVer, pTemp, dem);
			pTemp = pTemp->nextEdge;
		}
		
		return;
	}
	if (pNext->processed == 4)
		return;
	if (pNext == pVer) {
		dem++;
		return;
	}
	if(pNext->processed==0){// chua duyet qua
		
		pNext->processed = 2;// tam thoi duyet qua

		myEdge* pTemp = pNext->firstEdge;
		while (pTemp != nullptr) {
			if (pTemp->processed != 1)
				ChuTrinh(pVer, pTemp, dem);
			pTemp = pTemp->nextEdge;
		}
		pNext->processed = 3;

		return;
	}
}