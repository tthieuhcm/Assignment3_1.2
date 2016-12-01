#include "myGraph.h"

//***************************//
//myVertex class implementation//
//***************************//

myVertex::myVertex() {
	height = 0;
	data = 0;
	nextVertex = NULL;
	inDegree = 0;
	outDegree = 0;
	processed = 0;
	firstEdge = NULL;
}

myVertex::myVertex(int _data) {
	height = 0;
	data = _data;
	nextVertex = NULL;
	inDegree = 0;
	outDegree = 0;
	processed = 0;
	firstEdge = NULL;
}

//*************************//
//myEdge class implementation//
//*************************//

myEdge::myEdge(myVertex* _destination) {
	destination = _destination;
	nextEdge = NULL;
	processed = 0;
}

//**************************//
//myGraph class implementation//
//**************************//

myGraph::myGraph() {
	gHead = NULL;
	size = 0;
}

myGraph::myGraph(myVertex* _gHead) {
	gHead = _gHead;
	size = 1;
}

bool myGraph::InsertVertex(myVertex* v) {
	if (gHead == NULL) {
		gHead = v;
		size++;
		return true;
	}

	myVertex* pTemp = gHead;
	myVertex* pTail = NULL;
	while (pTemp != NULL) {
		//To avoid confusion, we do not allow Nodes with same data in our myGraph
		if (pTemp->data == v->data) {
			cout << "\nDifferent Vertices in a myGraph should have different data\n";
			cout << "myVertex insertion with data = " << pTemp->data << " failed\n";
			return false;
		}
		pTail = pTemp;
		pTemp = pTemp->nextVertex;
	}

	size++;
	pTail->nextVertex = v;
	return true;
}

bool myGraph::InsertVertex(int vData) {
	myVertex* newVertex = new myVertex(vData);
	if (gHead == NULL) {
		gHead = newVertex;
		size++;
		return true;
	}

	myVertex* pTemp = gHead;
	myVertex* pTail = NULL;
	while (pTemp != NULL) {
		//To avoid confusion, we do not allow Nodes with same data in our myGraph
		if (pTemp->data == vData) {
			cout << "\nDifferent Vertices in a myGraph should have different data\n";
			cout << "myVertex insertion with data = " << pTemp->data << " failed\n";
			return false;
		}
		pTail = pTemp;
		pTemp = pTemp->nextVertex;
	}

	size++;
	pTail->nextVertex = newVertex;
	return true;
}


bool myGraph::VertexExist(myVertex* v) {
	myVertex* tmp = gHead;
	while (tmp != NULL) {
		if (tmp->data == v->data) {
			return true;
		}
		tmp = tmp->nextVertex;
	}
	return false;
}

bool myGraph::VertexExist(int vData) {
	myVertex* tmp = gHead;
	while (tmp != NULL) {
		if (tmp->data == vData) {
			return true;
		}
		tmp = tmp->nextVertex;
	}
	return false;
}

myVertex* myGraph::GetVertex(int vData) {
	myVertex* tmp = gHead;
	while (tmp != NULL) {
		if (tmp->data == vData) {
			return tmp;
		}
		tmp = tmp->nextVertex;
	}
	return NULL;
}

bool myGraph::InsertEdgeFromVertices(myVertex* from, myVertex* to) {
	if (from->firstEdge == NULL) {
		if (from->data == to->data) {
			return false;
		}
		from->outDegree++;
		to->inDegree++;
		from->firstEdge = new myEdge(to);
		return true;
	}
	else {
		//Check if an myEdge already exists
		myEdge* eTmp = from->firstEdge;
		myEdge* myEdgeTail = eTmp;

		if (from->data == to->data) {
			//We do not allow a myVertex to point to itself
			//(It would be difficult for students to manage)
			cout << "\nA myVertex should not point to itself\n";
			cout << "myEdge insertion failed\n";
			return false;
		}

		while (eTmp != NULL) {
			if (eTmp->destination->data == to->data) {
				//This myEdge already exists, nothing to do here
				cout << "\nmyEdge already exists\n";
				cout << "myEdge insertion failed\n";
				return false;
			}
			myEdgeTail = eTmp;
			eTmp = eTmp->nextEdge;
		}
		myEdge* newmyEdge = new myEdge(to);
		from->outDegree++;
		to->inDegree++;
		myEdgeTail->nextEdge = newmyEdge;
	}
	return true;
}

bool myGraph::InsertEdge(myVertex* from, myVertex* to) {
	//Perform checking if [from] and [to] exist in the myGraph yet
	if (!VertexExist(from)) {
		InsertVertex(from);
	}

	if (!VertexExist(to)) {
		InsertVertex(to);
	}

	return InsertEdgeFromVertices(from, to);
}

bool myGraph::InsertEdge(int fromData, int toData) {
	//Perform checking if [from] and [to] exist in the myGraph yet
	if (!VertexExist(fromData)) {
		InsertVertex(fromData);
	}

	if (!VertexExist(toData)) {
		InsertVertex(toData);
	}

	myVertex* from = GetVertex(fromData);
	myVertex* to = GetVertex(toData);

	return InsertEdgeFromVertices(from, to);
}

bool myGraph::InsertEdge(myVertex* from, myEdge* from_to) {
	if (!VertexExist(from)) {
		InsertVertex(from);
	}

	myVertex* to = from_to->destination;

	if (!VertexExist(to)) {
		InsertVertex(to);
	}

	if (from->firstEdge == NULL) {
		if (from->data == to->data) {
			return false;
		}
		from->outDegree++;
		to->inDegree++;
		from->firstEdge = from_to;
		return true;
	}
	else {
		//Check if an myEdge already exists
		myEdge* eTmp = from->firstEdge;
		myEdge* myEdgeTail = eTmp;

		if (from->data == to->data) {
			//We do not allow a myVertex to point to itself
			//(It would be difficult for students to manage)
			cout << "\nA myVertex should not point to itself\n";
			cout << "myEdge insertion failed\n";
			return false;
		}

		while (eTmp != NULL) {
			if (eTmp->destination->data == to->data) {
				//This myEdge already exists, nothing to do here
				cout << "\nmyEdge already exists\n";
				cout << "myEdge insertion failed\n";
				return false;
			}
			myEdgeTail = eTmp;
			eTmp = eTmp->nextEdge;
		}
		from->outDegree++;
		to->inDegree++;
		myEdgeTail->nextEdge = from_to;
	}
	return true;
}

void myGraph::Print() {
	myVertex *showVertex = gHead;
	while (showVertex)
	{
		cout << showVertex->data << "->";
		myEdge *showEdge = showVertex->firstEdge;
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

// Duyet DFS
void myGraph::DFS(myVertex* v,_List& templist, void(*func)(_List&,int))
{
	if (v == nullptr||v->processed==1)
		return;
	
	else {
		v->processed = 1;
		func(templist,v->data);
		myEdge* e=v->firstEdge;
		while (e != nullptr){
			DFS(e->destination,templist, func);
			e = e->nextEdge;
		}

	}
}

myVertex* myGraph::at(int i){
	int d = i;
	myVertex* v = gHead;
	while (d>0)
	{
		v = v->nextVertex;
		d--;
	}
	return v;
}

// ham insert vao link list
void insert(_List& tempList, int data) {
	if (tempList.pHead == nullptr) {
		node* tempNode = new node;
		tempNode->data = data;
		tempList.pHead = tempNode;
		tempList.size++;
	}
	else {
		node* posNode = tempList.pHead;
		if (posNode->data == data)
			return;
		while (posNode->pNext != nullptr) {
			if (posNode->data == data)
				return;
			posNode = posNode->pNext;
		}
		node* pTemp = new node;
		pTemp->data = data;
		posNode->pNext = pTemp;
		tempList.size++;

	}
}

// Read reverse graph
bool ReadArrayInputOfReverseGraph(string filename, int*& vertexDataArr, int& vertexCount, int**& edgeDataArr, int& edgeCount) {
	ifstream myfile(filename.c_str());
	string line;
	vertexCount = 0;
	edgeCount = 0;
	vertexDataArr = NULL;
	edgeDataArr = NULL;
	cout << "Reading Graph data: \n";
	if (myfile.is_open()) {
		//Read vertex count on the first line
		myfile >> vertexCount;

		//Create an array to store the data
		vertexDataArr = new int[vertexCount];

		//Read them one by one
		for (int i = 0; i < vertexCount; i++) {
			myfile >> vertexDataArr[i];
		}

		//Read edge count on the 3rd line
		myfile >> edgeCount;

		//Create an array to store the Edge data
		//Each row of edgeDataArr indicates an edge
		//For example: edgeDataArr[0][0] = 5; edgeDataArr[0][1] = 7 means that there is an Edge goes from 5 to 7.
		edgeDataArr = new int*[edgeCount];
		for (int i = 0; i < edgeCount; i++) {
			edgeDataArr[i] = new int[2];
		}

		for (int i = 0; i < edgeCount; i++) {
			myfile >> edgeDataArr[i][1];
			myfile >> edgeDataArr[i][0];
		}
	}
	else {
		cout << "Can't open file " << filename << ".";
		return false;
	}
	return true;
}


//Read LK Graph
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

