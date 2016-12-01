#include"Header.h"
void printAVLGraph(myVertex* v, int indent);
bool checkAVL(myVertex* v, bool& isAVL);
int heightOfTree(myVertex* v, bool& isAVL);
bool checkThuTu(myVertex* v);
void LNR(myVertex* v, _List& templist, void(*func)(_List&, int));
bool checkLNR_AVL(myVertex* v, _List& templist);
void E17() {
	bool boo=true;
	int** vertexDataArr = nullptr;
	int vertexCount = 0;
	// Input
	ReadLKGraph("input/E17.txt", vertexDataArr, vertexCount);
	cout << "MA TRAN" << endl;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++)
			cout << vertexDataArr[i][j] << "  ";
		cout << endl;
	}
	//xu li
	int **edgeDataArr;
	int edgeCount = 0;
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
	int dem = 0;
	for (int i = 0; i < vertexCount; i++) {
		for (int j = 0; j < vertexCount; j++) {
			if (vertexDataArr[i][j] == 1) {
				edgeDataArr[dem][0] = i + 1;
				edgeDataArr[dem][1] = j + 1;
				dem++;
			}
		}
	}

	int* modiVertexDataArr = new int[vertexCount];
	for (int i = 0; i < vertexCount; i++)
		modiVertexDataArr[i] = i + 1;
	// In ma tran
	cout << endl;
	myGraph graph;
	for (int i = 0; i < vertexCount; i++)
		graph.InsertVertex(modiVertexDataArr[i]);
	for (int i = 0; i < edgeCount; i++)
		graph.InsertEdge(edgeDataArr[i][0], edgeDataArr[i][1]);
	graph.Print();

	//Kiem tra ma tran co phai AVL
	//B1: kiem tra co ton tai duy nhac 1 goc hay khong// Kiem tra co phai la cay nhi phan hay khong
	myVertex* v = graph.gHead;


	/**** Kiem tra in,out
	/*for (int i = 0; i < graph.size; i++) {
		cout << i+1 << " : in = " << v->inDegree << ", out = " << v->outDegree << endl;
		v = v->nextVertex;
	}
	return;
	*/
	
	
	myVertex* vHead=nullptr;
	int NoInVertex=0;
	// xu li outDegree,inDegree
	for(int i=0;i<graph.size;i++){
		if (vHead == nullptr&&v->inDegree == 0&&boo==true)
			vHead = v;
		else if (vHead != nullptr&& v->inDegree == 0)
			boo = false;
		if (v->outDegree > 2)
			boo = false;
		if (v->inDegree > 1)
			boo = false;
		v = v->nextVertex;
	}
	if (vHead != nullptr&&boo == true) {
	// xu li duong di tu diem goc den tat ca cac dinh => Co duong di tu dinh goc den tat ca dinh
		_List tempList;
		graph.DFS(vHead, tempList, insert);
		int dem=0;// so cac dinh ma vHead co duong di
		node* tempNode = tempList.pHead;
		while(tempNode!=nullptr){
			dem++;
			tempNode = tempNode->pNext;
		}
		if (dem != graph.size)
			boo = false;
	
	}
	// xu li thu tu cac dinh! cac dinh duoc duyet LNR co gia tri tang dan
	if (vHead != nullptr&&boo == true){
		_List list;
		boo = checkLNR_AVL(vHead, list); //
	}
	
	if (vHead != nullptr&&boo == true) {
	//xu li 
	//xu li dieu kien AVL, dieu kien cay gan hoan chinh! do doi 2 nhanh chenh lech nhau khong qua 1 don vi
		checkAVL(vHead, boo);
	}

	//in AVL
	if (boo == false)
		cout << endl << "IS NOT AVL";
	else {
		cout << endl << "IS AVL";
		printAVLGraph(vHead, 0);
	}
	


	
	

}

void printAVLGraph(myVertex* v,int indent) {
	if (v==nullptr) {
		return;
	}
	myVertex* e1 = nullptr;
	myVertex* e2 = nullptr;
	if(v->firstEdge!=nullptr){
		if (v->firstEdge->nextEdge != nullptr) {
			if (v->firstEdge->destination->data < v->firstEdge->nextEdge->destination->data) {
				e1 = v->firstEdge->destination;
				e2 = v->firstEdge->nextEdge->destination;
			}
			else{
				e2 = v->firstEdge->destination;
				e1 = v->firstEdge->nextEdge->destination;
			}
		}
		else {
			if (v->firstEdge->destination->data > v->data)
				e2 = v->firstEdge->destination;
			else
				e1 = v->firstEdge->destination;
		}
	}

	printAVLGraph(e1,indent + 1);
	for (int i = 0; i < indent; i++) {
		cout << "\t";
	}
	cout << v->data << endl;
	printAVLGraph(e2, indent + 1);
}


// check do cao
bool checkAVL(myVertex* v,bool& isAVL){
	heightOfTree(v, isAVL);
	return isAVL;
}
int heightOfTree(myVertex* v,bool& isAVL) {
	if (isAVL != false) {
		int hLeft;
		int hRight;
		if (v == nullptr) {
			hLeft = 0;
			hRight = 0;
		}
		else {
			if (v->firstEdge != nullptr)
				hLeft = heightOfTree(v->firstEdge->destination, isAVL) + 1;
			else hLeft = 1;

			if (v->firstEdge != nullptr) {
				if (v->firstEdge->nextEdge != nullptr)
					hRight = heightOfTree(v->firstEdge->nextEdge->destination, isAVL) + 1;
				else
					hRight = 1;
			}
			else
				hRight = 1;
		}
		if (abs(hLeft - hRight) > 1)
			isAVL = false;
		return (hLeft > hRight) ? hLeft : hRight;
	}
}

bool checkLNR_AVL(myVertex* v, _List& templist){
	LNR(v, templist, insert);
	node* p = templist.pHead;
	if (p == nullptr)
		return true;
	while (p->pNext != nullptr) {
		if (p->data > p->pNext->data)
			return false;
		p = p->pNext;
	}
	return true;
}
//duyet cay theo thu tu giua
void LNR(myVertex* v, _List& templist, void(*func)(_List&, int)){
	if (v == nullptr )
		return;

	else {
		myEdge* e1 = v->firstEdge;
		myEdge* e2;
		if (e1 != nullptr)
			e2 = v->firstEdge->nextEdge;
		else
			e2 = nullptr;


		if (e1 != nullptr&&e2 != nullptr){
			if (e1->destination->data > e2->destination->data) {
				LNR(e2->destination, templist, insert);
				func(templist, v->data);
				LNR(e1->destination, templist, insert);
			}
			else {
				LNR(e1->destination, templist, insert);
				func(templist, v->data);
				LNR(e2->destination, templist, insert);
			}
		}
		if (e1 != nullptr&&e2 == nullptr) {
			LNR(e1->destination, templist, insert);
			func(templist, v->data);
		}
		if (e1 == nullptr&&e2 == nullptr)
			func(templist, v->data);
	}
}
