#include"Header.h"
bool soNguyenTo(int number){
	if (number < 2) return false;
	for (int i = 2; i < sqrt(number); i++){
		if (number%i == 0) return false;
	}
	return true;
};
void preOrder(Node* root, int& chan, int& le, int& nguyento){
	if (root == NULL) return;
	if (root->data%2 == 0) chan++;
	else le++;
	if (soNguyenTo(root->data)) nguyento++;
	preOrder(root->left, chan, le, nguyento);
	preOrder(root->right, chan, le, nguyento);
};
void E3(){
	int* arr;
	int count;
	int chan = 0;
	int le = 0;
	int nguyento = 0;
	ReadArrayInput("input/E3.txt",arr,count);
	AVLTree tree = AVLTree::ArrayToAVL(arr,count);
	tree.PrintAVL();
	preOrder(tree.root,chan,le,nguyento);
	cout << "So node chan la: "<< chan << "\n";
	cout << "So node le la: "<< le << "\n";
	cout << "So node nguyen to la: "<< nguyento << "\n";
};