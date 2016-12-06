#include "Header.h"
using namespace std;
void E20()
{
	int q, N1, N2;
#pragma region Read input
#pragma region Read input from files and create Graphs
	// Read graph A input
	int *vertexADataArr;
	int vertexACount;
	int **edgeADataArr;
	int edgeACount;
	ReadArrayInputOfGraph("input/E20a.txt", vertexADataArr, vertexACount, edgeADataArr, edgeACount);

	//create graphA
	Graph _graphA;
	for (int i = 0; i < vertexACount; i++)
		_graphA.InsertVertex(vertexADataArr[i]);
	for (int i = 0; i < edgeACount; i++)
		_graphA.InsertEdge(edgeADataArr[i][0], edgeADataArr[i][1]);

	// Read graph B input

	int *vertexBDataArr;
	int vertexBCount;
	int **edgeBDataArr;
	int edgeBCount;
	ReadArrayInputOfGraph("input/E20b.txt", vertexBDataArr, vertexBCount, edgeBDataArr, edgeBCount);

	//create graphB
	Graph _graphB;
	for (int i = 0; i < vertexBCount; i++)
		_graphB.InsertVertex(vertexBDataArr[i]);
	for (int i = 0; i < edgeACount; i++)
		_graphB.InsertEdge(edgeBDataArr[i][0], edgeBDataArr[i][1]);

#pragma  endregion

#pragma region Calculate number of vertices of graphA and graphB
	int vertexCountA = 0, vertexCountB = 0;
	Vertex* tempA = _graphA.gHead;
	while (tempA != NULL)
	{
		vertexCountA++;
		tempA = tempA->nextVertex;
	}
	Vertex* tempB = _graphB.gHead;
	while (tempB != NULL)
	{
		vertexCountB++;
		tempB = tempB->nextVertex;
	}
#pragma  endregion

#pragma region Create Adjacency Matrix of two Graphs
	vector< vector<int> > adMatA;	//Adjacency Matrix of Graph A
	graphToAdMat(_graphA, vertexCountA, adMatA);
	vector< vector<int> > adMatB;	//Adjacency Matrix of Graph B
	graphToAdMat(_graphB, vertexCountB, adMatB);
#pragma endregion
#pragma endregion

#pragma region Process GraphA
#pragma region Find neighbors and distances from one vertex to the others of the graph
	vector<vector<int> > distanceA;
	vector<vector<int> > neighborA;
	initialStep(adMatA, distanceA, neighborA);
#pragma endregion

#pragma region Find and sort vertices according to distance between their neighbors ascendingly 
	vector<int> mainindexA;
	sortIndex(vertexCountA, neighborA, distanceA, mainindexA);
	//Sort the adjacency matrix with the order of mainindexA
	vector< vector<int> > sortedAdMatA = reindex(adMatA, mainindexA);
#pragma endregion

#pragma region Compute outdegree of all vertices and sort ascendingly
	vector<int> degListA;
	//Compute outdegree 
	getOutDegree(sortedAdMatA, vertexCountA, degListA);
	//sort outdegree ascending
	vector<int> sorted_degA = degListA;
	sort(sorted_degA.begin(), sorted_degA.end());
#pragma endregion

	//Pair graphs 
	map<vector<int>, set<int> > PA;
	map<vector<int>, int> dA;
	map<vector<int>, int> nVA;
	map<vector<int>, int> nEA;
	createPairGraph(sortedAdMatA, vertexCountA, PA, dA, nVA, nEA);

	//Create frequency table (sign frequency vectors)
	map<vector<int>, vector<int> > frequencyA;
	createFrequencyTable(vertexCountA, dA, nVA, nEA, frequencyA);

	//Calculate frequency
	addFrequency(frequencyA, vertexCountA, dA, nVA, nEA);

	//Transpose and sort (canonical form of sign matrix)
	vector<vector<int> > tvssA;
	sortFrequency(frequencyA, tvssA);

	//Divide vertices in to classes, each class contains vertices have the same sign form
	vector<int> graphClassA;
	classDivision(tvssA, vertexCountA, graphClassA);

	//Sort vertices according to the frequency table's order
	vector<int> vertexListA;
	for (int i = 0; i < vertexCountA; i++)
		vertexListA.push_back(tvssA[i][tvssA[i].size() - 1]);

	//Create the final sign matrix
	map<vector<int>, vector<int> > signmatrixA;
	signMatrix(vertexCountA, vertexListA, dA, nVA, nEA, signmatrixA);
#pragma endregion

#pragma region Process GraphB
#pragma region Find neighbors and distances from one vertex to the others of the graph
	vector<vector<int> > distanceB;
	vector<vector<int> > neighborB;
	initialStep(adMatB, distanceB, neighborB);
#pragma endregion

#pragma region Find and sort vertices according to distance between their neighbors ascendingly 
	vector<int> mainindexB;
	sortIndex(vertexCountB, neighborB, distanceB, mainindexB);
	//Sort the adjacency matrix with the order of mainindexB
	vector< vector<int> > sortedAdMatB = reindex(adMatB, mainindexB);
#pragma endregion

#pragma region Compute outdegree of all vertices and sort ascendingly
	vector<int> degListB;
	//Compute outdegree 
	getOutDegree(sortedAdMatB, vertexCountB, degListB);
	//sort outdegree ascending
	vector<int> sorted_degB = degListB;
	sort(sorted_degB.begin(), sorted_degB.end());
#pragma endregion


	//Pair graphs 
	map<vector<int>, set<int> > PB;
	map<vector<int>, int> dB;
	map<vector<int>, int> nVB;
	map<vector<int>, int> nEB;
	createPairGraph(sortedAdMatB, vertexCountB, PB, dB, nVB, nEB);

#pragma region Make frequency table (sign frequency vectors)
	map<vector<int>, vector<int> > frequencyB;
	//Construct frequency table
	createFrequencyTable(vertexCountB, dB, nVB, nEB, frequencyB);
	addFrequency(frequencyB, vertexCountB, dB, nVB, nEB);
#pragma endregion
	//Transpose and sort (canonical form of sign matrix)

	vector<vector<int> > tvssB;
	sortFrequency(frequencyB, tvssB);


	//Divide vertices in to classes, each class contains vertices have the same sign form
	vector<int> graphClassB;
	classDivision(tvssB, vertexCountB, graphClassB);

	//Sort vertices according to the frequency table's order
	vector<int> vertexListB;
	for (int i = 0; i < vertexCountB; i++)
		vertexListB.push_back(tvssB[i][tvssB[i].size() - 1]);

	//Create the final sign matrix
	map<vector<int>, vector<int> > signmatrixB;
	signMatrix(vertexCountB, vertexListB, dB, nVB, nEB, signmatrixB);

#pragma endregion

#pragma region Isomorphism Checking
	//Isomorphism Index 
	vector<int> fixisoB, isoB;
	for (int i = 0; i < vertexCountB; i++)
		fixisoB.push_back(i);
	isoB = fixisoB;
	bool isomorphic = false;
	bool possibly_isomorphic = false;
	if (sorted_degA == sorted_degB){
		vector<vector<int> > checksignA;
		map<vector<int>, vector<int> >::iterator itA = frequencyA.begin();
		while (itA != frequencyA.end())
		{
			vector<int> checksignrowA;
			vector<int> wsA = itA->first;
			for (int i = 0; i < wsA.size(); i++)
				checksignrowA.push_back(wsA[i]);
			vector<int> vsA = itA->second;
			for (int i = 0; i < vsA.size(); i++)
				checksignrowA.push_back(vsA[vertexListA[i]]);
			checksignA.push_back(checksignrowA);
			itA++;
		}
		vector<vector<int> > checksignB;
		map<vector<int>, vector<int> >::iterator itB = frequencyB.begin();
		while (itB != frequencyB.end())
		{
			vector<int> checksignrowB;
			vector<int> wsB = itB->first;
			for (int i = 0; i < wsB.size(); i++)
				checksignrowB.push_back(wsB[i]);
			vector<int> vsB = itB->second;
			for (int i = 0; i < vsB.size(); i++)
				checksignrowB.push_back(vsB[vertexListB[i]]);
			checksignB.push_back(checksignrowB);
			itB++;
		}
		if (checksignA == checksignB)
			possibly_isomorphic = true;
	}
#pragma region Possibly isomorphic
	if (possibly_isomorphic)
	{
		//Find isomorphism 
		for (int j = 0; j < vertexCountB; j++)
		{
			if (isomorphic) break;
			isoB = fixisoB; isoB[0] = fixisoB[j]; isoB[j] = fixisoB[0];
			for (int i = 0; i < vertexCountB*vertexCountB; i++)
			{
				vector<int> oldisoB = isoB;
				isoB = transform(signmatrixA, signmatrixB, vertexListA, vertexListB, isoB);
				bool quit = false, mismatch = false;
				for (int ii = 0; ii < vertexCountB; ii++)
				{
					if (quit)
						break;
					for (int jj = 0; jj < vertexCountB; jj++)
					{
						if (ii == jj)
							continue;
						vector<int> tindA, ta;
						tindA.push_back(vertexListA[ii]);
						tindA.push_back(vertexListA[jj]);
						vector<int> tindB, tb;
						tindB.push_back(vertexListB[isoB[ii]]);
						tindB.push_back(vertexListB[isoB[jj]]);
						map<vector<int>, vector<int> >::iterator itA = signmatrixA.find(tindA);
						ta = itA->second;
						map<vector<int>, vector<int> >::iterator itB = signmatrixB.find(tindB);
						tb = itB->second;
						if (ta != tb) {
							mismatch = true;
							quit = true;
							break;
						}
					}
				}
				if (isoB == oldisoB)
				{
					if (!mismatch)
						isomorphic = true;
					break;
				}
			}
		}

	}
#pragma endregion
#pragma endregion

#pragma region Print Result
	system("cls");
	_graphA.Print();
	cout << "________________" << endl;
	_graphB.Print();
	if (!possibly_isomorphic)
	{
		cout << "Graph A and Graph B cannot be isomorphic because "
			<< "they have different sign frequency vectors in lexicographic order."
			<< endl;
	}
	if (possibly_isomorphic && !isomorphic)
	{
		cout << "Graph A and Graph B have the same sign frequency vectors "
			<< "in lexicographic order but cannot be isomorphic." << endl;
	}
	if (possibly_isomorphic && isomorphic)
	{
		cout << "Graph A and Graph B are isomorphic." << endl;
		for (int i = 0; i < vertexCountA; i++)
		{
			cout << "f(" << getDataAt(inv(mainindexA)[vertexListA[i]] + 1, _graphA) << ")\t=\t";
			cout << getDataAt(inv(mainindexB)[vertexListB[isoB[i]]] + 1, _graphB) << endl;
		}
	}
#pragma endregion
}