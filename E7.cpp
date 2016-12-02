#include"Header.h"

void E7(){
		
//tao cay AVL tu file E7.tzt
        int* arr;
	int count;
	ReadArrayInput("input/E7.txt",arr,count);
	AVLTree tree = AVLTree::ArrayToAVL(arr,count);
	tree.PrintAVL();
//
//Duyet Breadth First Search
//bien front la 1 queue
//numberRow1 la bien chua so phan tu tung hang, hang 1 bat dau là 1 phan tu
//numberRow2 chua so phan tu hang tiep theo
//xet cac phan tu trong queue co cung hang (duoc quy dinh boi numberRow1)
//neu co phan tu ben trai hay ben phai thì add vao queue va tang numberRow2
//sau do cong gia tri vao bien Sum va giam numberRow1
//tiep tuc den khi khong con phan tu trong queue
//
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
