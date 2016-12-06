#include "Header.h"
//Dijkstra's Algorithm to find shortest paths from a given vertex to others, return list of paths.
vector<vector<int> > dijkstra(vector<vector<int> > graph)
{
	vector<vector<int> > table;
	int i, j, k, n = graph.size();
	//Initialize Table 
	const int infinity = n;
	vector<bool> known;
	for (i = 0; i < n; i++) known.push_back(false);
	vector<int> d;		//distance
	d.push_back(0);
	for (i = 1; i < n; i++) d.push_back(infinity);
	vector<int> p;		//path
	for (i = 0; i < n; i++) p.push_back(-1);
	//End initialization 

	//Iteration 
	for (k = 0; k < n; k++)
	{
		//Find min of d for unknown vertices 
		int min = 0;
		while (known[min] == true)min++;
		for (i = 0; i < n; i++)
		if (known[i] == false && d[i] < d[min]) min = i;
		//End find 
		//Update Table 
		known[min] = true;
		for (j = 0; j<n; j++)
		{
			if (graph[min][j] != 0 && d[j]>d[min] + graph[min][j] && known[j] == false)
			{
				d[j] = d[min] + graph[min][j];
				p[j] = min;
			}
		}
		//End update 
	}
	table.push_back(d);
	table.push_back(p);
	vector<vector<int> > path;
	for (i = 0; i < n; i++)
	{
		vector<int> temp_path;
		vector<int> temp;
		k = i;
		while (k != -1)
		{
			temp.push_back(k);
			k = table[1][k];
		}
		temp_path.push_back(temp[temp.size() - 1]);
		for (j = temp.size() - 2; j >= 0; j--)
		{
			temp_path.push_back(temp[j]);
		}
		path.push_back(temp_path);
	}
	return path;
}

//Rearrange the adjacency matrix according to the order given by index
vector<vector<int> > reindex(vector<vector<int> > graph, vector<int> index)
{
	vector<vector<int> > temp_graph = graph;
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
			temp_graph[index[i]][index[j]] = graph[i][j];
	}
	return temp_graph;
}

vector<int> inv(vector<int> index)
{
	vector<int> inverse = index;
	for (int i = 0; i < index.size(); i++)
		inverse[index[i]] = i;
	return inverse;
}

vector<int> transform(map<vector<int>, vector<int> > signmatrixA, map<vector<int>, vector<int> > signmatrixB,
	vector<int> vertexListA, vector<int> vertexListB,
	vector<int> isoB)
{
	vector<int> iso = isoB;
	map<vector<int>, vector<int> >::iterator it;
	int k, n = iso.size();
	bool found = false;
	bool check = true;
	for (int i = 0; i < n; i++)
	{
		if (found)
			break;
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			vector<int> indA, a;
			indA.push_back(vertexListA[i]); indA.push_back(vertexListA[j]);
			vector<int> indB, b;

			indB.push_back(vertexListB[isoB[i]]);
			indB.push_back(vertexListB[isoB[j]]);
			it = signmatrixA.find(indA); a = it->second;
			it = signmatrixB.find(indB); b = it->second;
			if (a != b)
			{
				k = j;
				vector<int> temp_ind = indB;
				while (k < n - 1 && check == true)
				{
					k++;
					temp_ind[1] = vertexListB[isoB[k]];
					it = signmatrixB.find(temp_ind); b = it->second;
					//check 
					if (a == b)
					{
						vector<int> temp_iso = isoB;
						temp_iso[j] = isoB[k];
						temp_iso[k] = isoB[j];
						int ti = -1, tj = -1;
						bool quit = false;
						for (int ii = 0; ii < n; ii++)
						{
							if (quit)
								break;
							for (int jj = 0; jj < n; jj++)
							{
								if (ii == jj)
									continue;
								vector<int> tindA, ta;
								tindA.push_back(vertexListA[ii]);
								tindA.push_back(vertexListA[jj]);
								vector<int> tindB, tb;
								tindB.push_back(vertexListB[temp_iso[ii]]);
								tindB.push_back(vertexListB[temp_iso[jj]]);
								it = signmatrixA.find(tindA); ta = it->second;
								it = signmatrixB.find(tindB); tb = it->second;
								if (ta != tb) {
									ti = ii;
									tj = jj;
									quit = true;
									break;
								}
								if (k == n - 1 && ti == -1) {
									check = false;
									quit = true;
									break;
								}
							}
						}
						if (ti == -1 || ti > i || (ti == i && tj > j))
							check = false;
					}
					//end check  
				}
				if (!check){
					found = true;
					iso[j] = isoB[k];
					iso[k] = isoB[j];
					break;
				}
				if (check) return iso;
			}
		}
	}
	return iso;
}

//Convert Graph to Adjacency Matrix
void graphToAdMat(Graph graph, int count, vector<vector<int>> &adMat)
{
	Vertex* show = graph.gHead;
	while (show)
	{
		vector<int> row;
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
			if (Has)
				row.push_back(1);
			else
				row.push_back(0);
			check = check->nextVertex;
		}
		adMat.push_back(row);
		show = show->nextVertex;
	}
}

//Get vertex's data at index k
int getDataAt(int k, Graph graph)
{
	Vertex* temp = graph.gHead;
	while (--k)
	{
		temp = temp->nextVertex;
	}
	return temp->data;
}

//Calculate outDegree of all vertices in Graph
void getOutDegree(vector< vector<int> > adMat, int vertexCount, vector<int> &degList)
{
	int sum;
	for (int i = 0; i < vertexCount; i++)
	{
		sum = 0;
		for (int j = 0; j < vertexCount; j++)
		{
			if (adMat[i][j] == 1) sum++;
		}
		degList.push_back(sum);
	}
}

//Compute shortest path from a given point
void shortestPath(int count, int N, vector<vector<int> > graph, vector<vector<int> > &shortest_path)
{
	vector<int> index;
	for (int q = 0; q < count; q++)
		index.push_back(q);
	index[0] = N; index[N] = 0;
	vector< vector<int> > temp_graph2A = reindex(graph, index);
	vector< vector<int> > path = dijkstra(temp_graph2A);
	for (int i = 0; i < path.size(); i++)
	{
		vector<int> tpath;
		for (int j = 0; j < path[i].size(); j++)
		{
			tpath.push_back(inv(index)[path[i][j]]);
		}
		shortest_path.push_back(tpath);
	}
}

//Create frequency table. (vertexCount = number of vertices in graph, distanceTable = shortest distance from one vertex to another,
//nV = number of vertices in a set containing vertices that form shortest path from i->j,
//nE = number of edges that formed by nV vertices above,
//frequency = contains the frequency of set {d, nV, nE}
void createFrequencyTable(int vertexCount, map<vector<int>, int> d, map<vector<int>, int> nV, map<vector<int>, int> nE, map<vector<int>, vector<int> > &frequency)
{
	map<vector<int>, int>::iterator it;
	vector<int> dummy;
	for (int i = 0; i < vertexCount; i++)
		dummy.push_back(0);
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			vector<int> vec;
			vector<int> ind;	//path from i->j
			ind.push_back(i);
			ind.push_back(j);
			it = d.find(ind);	//Get distance from i->j without traversing directly
			vec.push_back(it->second);
			it = nV.find(ind);	//Get number of vertices in the pair graph Pij
			vec.push_back(it->second);
			it = nE.find(ind);	//Number of edges in the pair graph Pij
			vec.push_back(it->second);
			frequency[vec] = dummy;
		}
	}
}

//Create Pair Graph
void createPairGraph(vector< vector<int> > &graph, int vertexCount, map<vector<int>, set<int> > &PairGraph, map<vector<int>, int> &d, map<vector<int>, int> &nV, map<vector<int>, int> &nE)
{
	for (int N1 = 0; N1 < graph.size(); N1++)
	{
		for (int N2 = 0; N2 < graph[N1].size(); N2++)
		{
			int sign = -1;
			vector<vector<int> > tgraph = graph;
			//If N1->N2 is an edge of graphA, remove it to create pair graph
			if (graph[N1][N2] != 0)
			{
				tgraph[N1][N2] = 0;
				sign = 1;
			}
#pragma region Compute shortest paths from given vertices u and v
			//Compute shortest paths from vertex u to other vertices with edge N1->N2 removed
			vector<vector<int> > shortest_path1;
			shortestPath(vertexCount, N1, tgraph, shortest_path1);
			//Compute shortest paths from vertex v to other vertices with edge N1->N2 removed
			vector<vector<int> > shortest_path2;
			shortestPath(vertexCount, N2, tgraph, shortest_path2);
#pragma endregion
			//Compute distance between vertex N1 and vertex N2 with edge N1->N2 removed
			int D = 0;
			for (int i = 0; i < shortest_path1.size(); i++)
			{
				if (shortest_path1[i][shortest_path1[i].size() - 1] == N2)
				{
					D = shortest_path1[i].size() - 1;
					break;
				}
			}
			//Compute shortest paths between vertex N1 and vertex N2 with edge N1->N2 removed
			vector<vector<int> > shortest_path12;
			for (int i = 0; i < shortest_path1.size(); i++)
			{
				for (int j = 0; j < shortest_path2.size(); j++)
				{
					if (shortest_path1[i].size()>1)
					{
						if (shortest_path1[i][shortest_path1[i].size() - 1] == shortest_path2[j][0])
						{
							vector<int> temppath = shortest_path1[i];
							for (int k = 1; k <= shortest_path2[j].size() - 1; k++)
								temppath.push_back(shortest_path2[j][k]);
							if (temppath.size() - 1 == D)
								shortest_path12.push_back(temppath);
						}
					}
					else
					{
						if (graph[shortest_path1[i][0]][shortest_path2[j][0]] == 1)
						{
							sign = 0;
						}
						if (shortest_path1[i][0] == shortest_path2[j][0])
						{
							vector<int> temp;
							temp.push_back(shortest_path1[i][0]);
							shortest_path12.push_back(temp);
						}
					}
				}
			}
			//Pair graph for vertex N1 and vertex N2 
			bool check = false;		//Check if edge N1->N2 exists or not, default 
			set<int> S;		//Set vertices belong to union of shortest paths from v->u
			for (int i = 0; i < shortest_path12.size(); i++)
			{
				if (shortest_path12[i][0] == N1 && shortest_path12[i][shortest_path12[i].size() - 1] == N2)
				{
					check = true;
					for (int j = 0; j < shortest_path12[i].size(); j++)
						S.insert(shortest_path12[i][j]);
				}
			}
			vector<int> V;
			V.push_back(N1);
			V.push_back(N2);
			PairGraph[V] = S;
			//Distance between vertex N1 and vertex N2 
			if (check)
				d[V] = sign*D;
			else
				d[V] = sign;
			//Count number of vertices in pair graph 
			nV[V] = S.size();
			//Count number of edges in pair graph 
			int count = 0;
			for (int i = 0; i < vertexCount; i++)
			{
				for (int j = 0; j < vertexCount; j++)
				{
					bool findpair = false;
					set<int>::iterator i1, i2;
					i1 = S.find(i); i2 = S.find(j);
					if (i1 != S.end() && i2 != S.end())
						findpair = true;
					if (findpair && graph[i][j] != 0)
						count++;
				}
			}
			nE[V] = count;
		}
	}
}

//Add frequency to frequecy table
void addFrequency(map<vector<int>, vector<int> > &frequency, int vertexCount, map<vector<int>, int> &d, map<vector<int>, int> &nV, map<vector<int>, int> &nE)
{
	map<vector<int>, vector<int> >::iterator itt = frequency.begin();
	while (itt != frequency.end())
	{
		for (int i = 0; i < vertexCount; i++)
		{
			int fre = 0;
			for (int j = 0; j < vertexCount; j++)
			{
				vector<int> vec;
				vector<int> ind; ind.push_back(i); ind.push_back(j);
				map<vector<int>, int >::iterator it = d.find(ind);
				vec.push_back(it->second);
				it = nV.find(ind);
				vec.push_back(it->second);
				it = nE.find(ind);
				vec.push_back(it->second);
				if (vec == itt->first) fre++;
			}
			itt->second[i] = fre;
		}
		itt++;
	}
}

//Divide vertices in to classes, each class contains vertices that have same sign form
void classDivision(vector<vector<int> > tvss, int vertexCount, vector<int> &GraphClass)
{
	vector<int> cl, dl;
	int c = 0;
	int ic = 0;
	dl = tvss[ic];
	dl.pop_back();
	while (ic < vertexCount)
	{
		cl = tvss[ic];
		cl.pop_back();
		if (cl == dl)
			GraphClass.push_back(c);
		else {
			dl = cl;
			c++;
			GraphClass.push_back(c);
		}
		ic++;
	}
}

//Create final sign matrix
void signMatrix(int vertexCount, vector<int> vertexList, map<vector<int>, int> &d, map<vector<int>, int> &nV, map<vector<int>, int> &nE, map<vector<int>, vector<int> > &signmatrix)
{
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			vector<int> ind;
			ind.push_back(vertexList[i]);
			ind.push_back(vertexList[j]);
			vector<int> si;
			map<vector<int>, int>::iterator it = d.find(ind);
			si.push_back(it->second);
			it = nV.find(ind);
			si.push_back(it->second);
			it = nE.find(ind);
			si.push_back(it->second);
			signmatrix[ind] = si;
		}
	}
}

//Sort index of adjacency matrix via the shortest distance between their neighbors ascendingly
void sortIndex(int vertexCount, vector<vector<int> > neighbor, vector<vector<int> > distance, vector<int> &mainindex)
{
	vector<vector<int> > sequence;
	for (int i = 0; i < vertexCount; i++)
	{
		vector<int> mutualdistance;
		if (neighbor[i].size() != 0)
		{
			for (int j = 0; j < neighbor[i].size(); j++)
			{
				for (int k = 0; k < neighbor[i].size(); k++)
					mutualdistance.push_back(distance[neighbor[i][j]][neighbor[i][k]]);
			}
		}
		sort(mutualdistance.begin(), mutualdistance.end());
		vector<int> tmutual;
		for (int k = 0; k < vertexCount*vertexCount - 1 - mutualdistance.size(); k++)
			tmutual.push_back(0);
		for (int k = 0; k < mutualdistance.size(); k++)
			tmutual.push_back(mutualdistance[k]);
		sequence.push_back(tmutual);
	}

	map<vector<int>, int> sorter;
	for (int i = 0; i < sequence.size(); i++)
		sorter[sequence[i]] = i;
	map<vector<int>, int>::iterator sit = sorter.begin();
	while (sit != sorter.end())
	{
		vector<int>vsit = sit->first;
		for (int i = 0; i < sequence.size(); i++)
		{
			if (sequence[i] == vsit)
				mainindex.push_back(i);
		}
		sit++;
	}
}

//Find neighbors and distances from one vertex to the others of the graph
void initialStep(vector< vector<int> > adMat, vector<vector<int> > &distance, vector<vector<int> > &neighbor)
{
	for (int i = 0; i < adMat.size(); i++)
	{
		vector<int> rowdistance, rowneighbor;
		for (int j = 0; j < adMat[i].size(); j++)
		{
			if (adMat[i][j] == 1)
				rowneighbor.push_back(j);
			vector<int> indexd;
			for (int k = 0; k < adMat.size(); k++)
				indexd.push_back(k);
			indexd[0] = i;
			indexd[i] = 0;
			vector<vector<int> > dgraph = reindex(adMat, indexd);
			vector<vector<int> > dpath = dijkstra(dgraph);
			int dd = -1;
			for (int k = 0; k < dpath.size(); k++)
			if (inv(indexd)[dpath[k][dpath[k].size() - 1]] == j)
			{
				dd = dpath[k].size() - 1;
				break;
			}
			rowdistance.push_back(dd);
		}
		distance.push_back(rowdistance);
		neighbor.push_back(rowneighbor);
	}
}

//Sort the sign form in the lexicographical order with correspondent frequency
void sortFrequency(map<vector<int>, vector<int> > frequency, vector<vector<int> > &tvss)
{
	vector<vector<int> > vss;
	map<vector<int>, vector<int> >::iterator it = frequency.begin();
	while (it != frequency.end())
	{
		vector<int> vs = it->second;
		vss.push_back(vs);
		it++;
	}
	vector<int> row;
	for (int i = 0; i < vss.size(); i++)
		row.push_back(0);
	for (int j = 0; j < vss[0].size(); j++)
		tvss.push_back(row);
	for (int i = 0; i < vss.size(); i++)
	{
		for (int j = 0; j < vss[0].size(); j++)
			tvss[j][i] = vss[i][j];
	}
	for (int i = 0; i < tvss.size(); i++)
		tvss[i].push_back(i);
	sort(tvss.begin(), tvss.end());
}