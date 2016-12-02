#include"Header.h"

void E8(){
//tao Heap
        int* arr;
	int count;
	ReadArrayInput("input/E8.txt",arr,count);
	Heap tree = Heap::ArrayToHeap(arr,count);
	tree.PrintHeapTree();
//vi Heap la cay gan day du nen vi tri cac phan tu trong 1 hang la xac dinh
//1 phan tu thuoc hang thu Row thi có vi tri < 2^Row
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
