#include"Header.h"
void HeaptoGraph(Heap tree, Graph &graph, int count){
	if (tree.IsEmpty()) return;
	graph.InsertVertex(tree.operator[](0));
	int walk = 1;
	while (walk < count){
		graph.InsertEdge(tree.operator[]((walk-1)/2), tree.operator[](walk));
		walk++;
	}
}
void E10(){
	int* arr;
	int count;
	ReadArrayInput("input/E10.txt",arr,count);
	Heap tree = Heap::ArrayToHeap(arr,count);
	tree.PrintHeapTree();

	Graph graph;
	HeaptoGraph(tree,graph,count);
	graph.Print();
}