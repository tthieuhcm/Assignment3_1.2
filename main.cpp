#include"Header.h"

void main(){
	int n;

	cout << "Nhap so: ";
	cin >> n;
	switch (n){
		case 1 : E1(); break;
		case 2 : E2(); break;
		case 3 : E3(); break;
		case 4 : E4(); break;
		case 7 : E7(); break;
		case 8 : E8(); break;
		default: cout << "Lenh khong ton tai.";
	}
	
	system("pause");
}