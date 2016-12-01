#include"Header.h"
void AVLtoGraph(AVLTree tree, Graph &graph){
	if (tree.root == NULL) return;
	graph.InsertVertex(tree.root->data);
	if (tree.root->left != NULL){
		AVLtoGraph(tree.root->left, graph);
		graph.InsertEdge(tree.root->data, tree.root->left->data);
	}
	if (tree.root->right != NULL){
		AVLtoGraph(tree.root->right, graph);
		graph.InsertEdge(tree.root->data, tree.root->right->data);
	}
}
void E9(){
	int* arr;
	int count;
	ReadArrayInput("input/E9.txt",arr,count);
	AVLTree tree = AVLTree::ArrayToAVL(arr,count);
	tree.PrintAVL();

	Graph graph;
	AVLtoGraph(tree,graph);
	graph.Print();
}