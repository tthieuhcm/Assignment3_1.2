#include "Header.h"

#pragma  region Functions on EdgeW
EdgeW::EdgeW(VertexW* _destinationW, Vertex* _destination, int _weight) :Edge(_destination)
{
	this->weight = _weight;
	this->nextEdgeW = NULL;
	this->destinationW = _destinationW;
}
#pragma  endregion

#pragma region Functions on VertexW
VertexW::VertexW() :Vertex()
{
	firstEdgeW = NULL;
	nextVertexW = NULL;
	dist = INFINITY;
	path = NULL;
}

VertexW::VertexW(int data) :Vertex(data)
{
	firstEdgeW = NULL;
	nextVertexW = NULL;
	dist = INFINITY;
	path = NULL;
}
#pragma  endregion

#pragma region Functions on GraphW
GraphW::GraphW() :Graph()
{
	gHeadW = NULL;
}

GraphW::GraphW(VertexW* gHeadW) :Graph()
{
	this->gHeadW = gHeadW;
	size = 1;
}

bool GraphW::InsertVertexW(int vData) {
	VertexW* newVertexW = new VertexW(vData);
	if (gHeadW == NULL) {
		gHeadW = newVertexW;
		size++;
		return true;
	}

	VertexW* pTemp = gHeadW;
	VertexW* pTail = NULL;
	while (pTemp != NULL) {
		//To avoid confusion, we do not allow Nodes with same data in our graph
		if (pTemp->data == vData) {
			return false;
		}
		pTail = pTemp;
		pTemp = pTemp->nextVertexW;
	}

	size++;
	pTail->nextVertexW = newVertexW;
	return true;
}

VertexW* GraphW::GetVertexW(int vData) {
	VertexW* tmp = gHeadW;
	while (tmp != NULL) {
		if (tmp->data == vData) {
			return tmp;
		}
		tmp = tmp->nextVertexW;
	}
	return NULL;
}

bool GraphW::InsertEdgeFromVertices(VertexW* from, VertexW* to, int weight) {
	Vertex* verTo = new Vertex(to->data);
	if (from->firstEdgeW == NULL) {
		if (from->data == to->data) {
			return false;
		}
		from->outDegree++;
		to->inDegree++;
		from->firstEdgeW = new EdgeW(to,verTo,weight);
		return true;
	}
	else {
		//Check if an Edge already exists
		EdgeW* eTmp = from->firstEdgeW;
		EdgeW* edgeTail = eTmp;

		if (from->data == to->data) {
			//We do not allow a Vertex to point to itself
			//(It would be difficult for students to manage)
			return false;
		}

		while (eTmp != NULL) {
			if (eTmp->destinationW->data == to->data) {
				//This edge already exists, nothing to do here
				return false;
			}
			edgeTail = eTmp;
			eTmp = eTmp->nextEdgeW;
		}
		EdgeW* newEdgeW = new EdgeW(to,verTo,weight);
		from->outDegree++;
		to->inDegree++;
		edgeTail->nextEdgeW = newEdgeW;
	}
	return true;
}

bool GraphW::InsertEdgeW(int fromData, int toData, int weight) {
	//Perform checking if [from] and [to] exist in the graph yet
	if (!VertexExist(fromData)) {
		InsertVertexW(fromData);
	}

	if (!VertexExist(toData)) {
		InsertVertexW(toData);
	}

	VertexW* from = GetVertexW(fromData);
	VertexW* to = GetVertexW(toData);

	return InsertEdgeFromVertices(from, to,weight);
}

//Print Graph with Edges' weight
void GraphW::Print()
{
	VertexW *showVertexW = gHeadW;
	while (showVertexW)
	{
		cout << showVertexW->data << "--";
		EdgeW *showEdgeW = showVertexW->firstEdgeW;
		cout << showEdgeW->weight << "-->";
		while (showEdgeW)
		{
			cout << showEdgeW->destination->data << "--";
			if (showEdgeW->nextEdgeW != NULL)
				cout << showEdgeW->nextEdgeW->weight << "-->";
			else
				cout << ">";
			showEdgeW = showEdgeW->nextEdgeW;
		}
		cout << "NULL" << endl << "|\n";
		showVertexW = showVertexW->nextVertexW;
	}
	cout << "NULL\n";
}

#pragma endregion


//Convert Adjacency Matrix to Graph
void AdjacencyMattoGraph(int **mat, int count, GraphW &graph)
{
	for (int i = 0; i < count; i++)
	{
		graph.InsertVertexW(i+1);		//Insert vertex has data i+1 into graph
		for (int j = 0; j < count; j++)
		{
			if (mat[i][j] != 0)
			{
				graph.InsertEdgeW(i + 1, j+1,mat[i][j]);	//Insert edge from vertex i+1 to j+1 with weight mat[i][j] into graph
			}
		}
	}
}

//Find Shortest Path from vertex _from to vertex _to, using Dijkstra's Algorithm
int FindShortestPath(GraphW graph,int _from, int _to, list<int>passList)
{
	if(_from == _to)
		return 0;
	if (CheckDataExist(_from, passList) || CheckDataExist(_to, passList))
		return INFINITY;
	VertexW* fromVertexW = graph.GetVertexW(_from);		//Get from Vertex
	VertexW* temp = fromVertexW;
	//Set all Vertices' distance = INFINITY
	while (temp)
	{
		temp->dist = INFINITY;
		temp = temp->nextVertexW;
	}
	fromVertexW->dist = 0;		//Set distance of beginning vertex to 0

	while (UnProcessedExist(graph,passList))		//If graph has a vertex that has not been processed 
													//and does not belong to passList, do the algorithm
	{
		VertexW* v = GetSmallestUnknownDistanceVertexW(graph,passList);	//Get vertex that has smallest distance to beginning vertex
		if (v == NULL)
			break;
		v->processed = true;						//v has been processed
		EdgeW* w = v->firstEdgeW;					//Get adjacency vertices of vertex v
		while (w)
		{
			if (!CheckDataExist(w->destinationW->data, passList))
			{
				if (w->destinationW->processed == false)
				{
					int distvw = w->weight;			//distance from v to w
					if (v->dist + distvw < w->destinationW->dist)
					{
						w->destinationW->dist = v->dist + distvw;	//decrease distance from w to v to distance(v,beginning vertex) + distance(w,v)
						w->destinationW->path = v;					//Set v to be the previous vertex of w in the path from beginning vertex to w
					}
				}
			}
			w = w->nextEdgeW;
		}
	}
	return graph.GetVertexW(_to)->dist;								//return result
}

//Check if vertex exists in passed Vertex List
bool CheckDataExist(int data, list<int> passList)
{
	for each (int var in passList)
	{
		if (var == data)
			return true;
	}
	return false;
}

//Print path from beginning Vertex to Destination vertex
void printPath(int _from, int _to,GraphW graph,list<int>passList)
{
	int shortestPath = FindShortestPath(graph, _from, _to,passList);
	VertexW* temp= graph.gHeadW;
	int count = 0;
	//Calculate the number of vertex in graph
	while (temp)
	{
		count++;
		temp = temp->nextVertexW;
	}
	if (shortestPath == INFINITY)
		cout << "There is no path from vertex " << _from << " to vertex " << _to << endl;
	else
	{
		cout << "The shortest path from vertex " << _from << " to vertex " << _to << " is: " << shortestPath << endl;
		cout << "Path you can go: ";
		VertexW* pTemp = graph.GetVertexW(_to);
		cout << pTemp->data;
		pTemp = pTemp->path;
		while (pTemp)
		{
			if (pTemp)
				cout << " <-- " << pTemp->data;
			pTemp = pTemp->path;
		}
		cout << endl;
	}
}

//Get Unknown Vertex that has smallest distance to the beginning vertex
VertexW* GetSmallestUnknownDistanceVertexW(GraphW graph, list<int> passList)
{
	VertexW* temp = graph.gHeadW;
	VertexW* temp2 = NULL;
	int smallest = INFINITY;
	if (temp->processed == false&&!CheckDataExist(temp->data,passList))		//If vertex has been processed of Exists in passList, pass
	{
		smallest = temp->dist;
		temp2 = temp;
	}
	while (temp)
	{
		if (!CheckDataExist(temp->data, passList))
		{
			if (temp->processed == false)
			{
				if (temp->dist < smallest)
				{
					smallest = temp->dist;
					temp2 = temp;
				}
			}
		}
		temp = temp->nextVertexW;
	}
	return temp2;
}

//Check if all the Vertex in Graph has been processed or not
bool UnProcessedExist(GraphW graph,list<int>passList)
{
	VertexW* gHeadW = graph.gHeadW;
	while (gHeadW)
	{
		if (gHeadW->processed == false &&!CheckDataExist(gHeadW->data,passList))
			return true;
		gHeadW = gHeadW->nextVertexW;
	}
	return false;
}

void E18()
{	
	system("cls");
	int **mat;
	list<int> passList;
	int count;
	int _from, _to;
	string filename = "input/E18.txt";
	GraphW graph;
	ReadAdjacencyMat(filename, mat, count);		//read input
	AdjacencyMattoGraph(mat, count, graph);		//Convert Adjacency Matrix to Graph
	graph.Print();								//Print Graph
	cout << "Input from beginning vertex and destination vertex in (0," << count+1 << ")" << endl;;
	cout << "From: ";
	cin >> _from;
	cout << "To: ";
	cin >> _to;
	if (_from <= 0 || _to <= 0 || _from > count || _to > count)
		cout << "Invalid inputs!" << endl;
	else
		printPath(_from, _to, graph, passList);
}