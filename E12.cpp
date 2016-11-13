#include "Header.h"
int *AVLtoArray(AVLTree tree, int *arr, int &count)
{
	if (!tree.root) return arr;
	arr[count] = tree.root->data;
	count++;
	if (tree.root->left) AVLtoArray(tree.root->left, arr, count);
	if (tree.root->right) AVLtoArray(tree.root->right, arr, count);
	return arr;
}
void FindNode(Node *root, int data, Node *&find)
{
	if (!root) return;
	if (root->data == data)
	{
		find = root;
		return;
	}
	if (root->left) FindNode(root->left, data, find);
	if (root->right) FindNode(root->right, data, find);
}
void E12()
{
	int *arr;
	int count;
	ReadArrayInput("E12.txt", arr, count);
	AVLTree avlTree;
	avlTree = AVLTree::ArrayToAVL(arr, count);
	cout << endl << "Cay AVL hien hanh: " << endl;
	avlTree.PrintAVL();

	// AVLtree to Array
	int *Arr = new int[count];
	count = 0;
	AVLtoArray(avlTree, Arr, count);

	// In ma trận liền kề
	cout << "Ma tran lien ke cua AVLtree:\n";
	cout << setw(5) << right << "|";
	for (int i = 0; i < count;i++)
		cout << setw(4) << left << Arr[i] << right << "|";
	cout << endl;

	for (int i = 0; i < count; i++)
	{
		cout << setw(4) << left << Arr[i] << right << "|";
		Node *find;
		FindNode(avlTree.root, Arr[i], find);

		for (int j = 0; j < count; j++)
		{
			bool Has = false;
			if ((find->left && find->left->data == Arr[j]) || (find->right && find->right->data == Arr[j]))
				Has = true;
			if (Has) cout << setw(4) << left << 1 << right << "|";
			else cout << setw(4) << left << 0 << right << "|";
		}
		cout << endl;
	}

	// delete
	//while (!avlTree.IsEmpty())
	//	avlTree.AVLDelete(avlTree.root->data);
	//delete[]arr;
	//delete[]Arr;
	//system("pause");
}