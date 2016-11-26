#include"Header.h"

void main(){
	int n;
	bool stop = false;
	char c;
	do{
		cout << "Nhap so: ";
		cin >> n;
		switch (n){
			case 1 : E1();  break;
			case 2 : E2();  break;
			case 3 : E3();  break;
			case 4 : E4();  break;
			case 5 : E5();  break;
			case 6 : E6();  break;
			case 7 : E7();  break;
			case 8 : E8();  break;
			case 9 : E9();  break;
			case 10: E10(); break;
			case 11: E11(); break;
			case 12: E12(); break;
			case 13: E13(); break;
			case 14: E14(); break;
			case 15: E15(); break;
			case 16: E16(); break;
			default: cout << "Lenh khong ton tai.\n";
		}
		cin.ignore();
		cout << "Ban co muon dung chuong trinh ? Nhan Y/y de ket thuc chuong trinh.";
		c = getch();
		system("cls");
	}
	while (c!='y'&&c!='Y');
}
