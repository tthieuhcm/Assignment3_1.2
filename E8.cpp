#include"Header.h"

void E8(){
	int* arr;
	int count;
	ReadArrayInput("E8.txt",arr,count);
	Heap tree = Heap::ArrayToHeap(arr,count);
	tree.PrintHeapTree();
	int walk = 0;
	int row = 1;
	int sum = 0;
	while (walk < count){
		while (walk < _Pow_int(2,row)-1 && walk < count){
			sum += tree.operator[](walk);
			walk++;
		}
		cout << sum << "\n";
		row++;
		sum = 0;
	}
};