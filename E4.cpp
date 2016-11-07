#include"Header.h"

void E4(){
	int n;
	cout << "Nhap n: ";
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++){
		cout << "arr[" << i << "] = ";
		cin >> arr[i];
	}
	Heap tree = Heap::ArrayToHeap(arr,n);
	tree.PrintHeapTree();
};