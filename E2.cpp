#include"Header.h"
void E2(){
	int* arr;
	int count;
	int del = -1;
	ReadArrayInput("input/E2.txt",arr,count);
	AVLTree tree = AVLTree::ArrayToAVL(arr,count);	
        tree.PrintAVL();	
        do{
		cout << "Nhap gia tri node can xoa: ";
		cin >> del;
		if (del != -1) {
			if (!tree.AVLDelete(del)) cout << "Node khong ton tai.\n";
			else tree.PrintAVL();
		}
	}
	while (del != -1);
};
