#include"Header.h"
// chuyển dữ liệu trong file thành mảng, chuyển mảng thành cây AVL, cho phép xóa node trên cây
// dừng lại khi giá trị nhập là -1
void E2(){
	int* arr;
	int count;
	int del = -1; // biến chứa giá trị node cần xóa
	ReadArrayInput("E2.txt",arr,count);
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
