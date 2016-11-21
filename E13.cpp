#include "Header.h"

void E13()
{
	int *arr = NULL;
	int count;
	ReadArrayInput("E8.txt", arr, count);
	Heap heap;
	heap = Heap::ArrayToHeap(arr, count);
	cout << "Cay Heap hien hanh: " << endl;
	heap.PrintHeapTree();

	// In ma trận liền kề
	cout << "Ma tran lien ke cua Heap:\n";
	cout << setw(5) << right << "|";
	for (int i = 0; i < count; i++)
		cout << setw(4) << left << heap.operator[](i) << right << "|";
	cout << endl;

	for (int i = 0; i < count; i++)
	{
		cout << setw(4) << left << heap.operator[](i) << right << "|";

		for (int j = 0; j < count; j++)
		{
			bool Has = false;
			if (j!= 0 && (j-1)/2 == i)
				Has = true;
			if (Has) cout << setw(4) << left << 1 << right << "|";
			else cout << setw(4) << left << 0 << right << "|";
		}
		cout << endl;
	}
}
