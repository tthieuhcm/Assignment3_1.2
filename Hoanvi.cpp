//chương trình sẽ liệt kê tất cả các hoán vị của tập X={1,2,3,4} bằng phương pháp đệ quy quay lui.
//Kết quả của chương trình sẽ được ghi ra file HOANVI.OUT
#include"HoanVi.h"
using namespace std;

void swap(int&, int&);
void hoanVi(int n, int ** arr)
{
	int i, k, a, b, d;
	d = 0;
	int* x = new int[n];
	for (i = 0; i < n; i++)
		x[i] = i+1;
	i = n - 2;
	while(i>=0){
		for(int i=0;i<n;i++){
			arr[d][i] = x[i];
		}
		d++;
		i = n - 2;
		while (i >= 0 && x[i] > x[i + 1]) i--;
		if (i >= 0) {
			k = n-1;
			while (x[k] < x[i]) k--;
			swap(x[k], x[i]);
			a = i + 1;
			b = n - 1;
			while (a < b) {
				swap(x[a], x[b]);
				a++;
				b--;
			}

		}
	
	}
	

}

void swap(int& a, int& b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}