#include "Header.h"

void E19()
{
	system("cls");
	int **mat;
	list<int> passList;
	int count;
	int _from, _to;
	string filename = "input/E18.txt";
	GraphW graph;
	ReadAdjacencyMat(filename, mat, count);		//read input
	AdjacencyMattoGraph(mat, count, graph);		//Covert Adjacency Matrix to Graph
	graph.Print();								//print graph
	cout << "Input begining vertex and destination vertex in (0," << count + 1 << ")" << endl;;
	cout << "From: ";
	cin >> _from;
	cout << "To: ";
	cin >> _to;
	cout << "Input list of vertices that you don't want your path to pass(enter -1 to stop): ";
	//Get passed vertices
	while (true)
	{
		int buffer;
		cin >> buffer;
		if (buffer == -1)
			break;
		passList.push_back(buffer);
	}
	if (_from <= 0 || _to <= 0 || _from > count || _to > count)
		cout << "Invalid inputs!" << endl;
	else
		printPath(_from, _to, graph, passList);
}