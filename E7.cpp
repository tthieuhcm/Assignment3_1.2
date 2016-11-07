#include"Header.h"

void E7(){
	int* arr;
	int count;
	ReadArrayInput("E7.txt",arr,count);
	AVLTree tree = AVLTree::ArrayToAVL(arr,count);
	tree.PrintAVL();

	List* front = new List;
	front->data = tree.root;
	front->pNext = NULL;
	List* rear  = front;
	int numberRow1 = 1;
	int numberRow2 = 0;
	int sum = 0;
	while (front != NULL){
		while (numberRow1 > 0){
			if (front->data->left != NULL){
				List* newNode = new List;
				newNode->data = front->data->left;
				newNode->pNext = NULL;
				rear->pNext = newNode;
				rear = newNode;
				numberRow2++;
			}
			if (front->data->right != NULL){
				List* newNode = new List;
				newNode->data = front->data->right;
				newNode->pNext = NULL;
				rear->pNext = newNode;
				rear = newNode;
				numberRow2++;
			}
			sum += front->data->data;
			numberRow1--;
			List* del = front;
			front = front->pNext;
			delete del;
		}
		cout << sum << "\n";
		numberRow1 = numberRow2;
		numberRow2 = 0;
		sum = 0;
	}
};