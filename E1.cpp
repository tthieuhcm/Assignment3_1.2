#include"Header.h"

void E1(){
	int n; int* arr;
	cout << "Nhap n: ";
	cin >> n;
	arr = new int[n];
	for (int i = 0; i < n; i++){
		cout << "arr[" << i << "] = ";
		cin >> arr[i];
	}
	AVLTree tree = AVLTree::ArrayToAVL(arr,n);
	tree.PrintAVL();
};