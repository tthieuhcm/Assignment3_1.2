#include "Header.h"

void E13()
{
	int *arr = NULL;
	int count;
	ReadArrayInput("input/E13.txt", arr, count);
	Heap heap;
	heap = Heap::ArrayToHeap(arr, count);
	cout << "Cay Heap hien hanh: " << endl;

	// In heap
	heap.PrintHeapTree();


	// Chuyển heap về ma trận liền kề
	int **matran = new int*[count + 1];
	for (int i = 0; i < count + 1; i++)
		*(matran + i) = new int[count + 1];

	matran[0][0] = -1;
	for (int i = 0; i < count; i++)
	{
		matran[0][i + 1] = heap.operator[](i);
		matran[i + 1][0] = heap.operator[](i);
		for (int j = 0; j < count; j++)
		{
			bool Has = false;
			if ((j != 0 || i != 0) && ((j - 1) / 2 == i || (i - 1) / 2 == j))
				Has = true;
			if (Has) matran[i + 1][j + 1] = 1;
			else matran[i + 1][j + 1] = 0;
		}
	}

	// In ma trận liền kề
	cout << "Ma tran lien ke cua Heap:\n";
	cout << setw(5) << right << "|";
	for (int i = 0; i < count + 1; i++)
	{
		for (int j = 0; j < count + 1; j++)
		if (i != 0 || j != 0) cout << setw(4) << left << matran[i][j] << right << "|";
		cout << endl;
	}
}