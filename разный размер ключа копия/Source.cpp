#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>  
#include <bitset>
using namespace std;
int uf(int x) {
	int kb = 8;
	//cout << bitset<8>(x) << endl;
	//int m1 = x >> 7;// � m1 �� ����� �������� ���� - �������� �������� ���� ��������� �����
	int m1 = x >> (kb - 1);
	//cout << bitset<10>(m1) << endl;
	//int m2 = (x & 1) << 9;//� m2 �� ����� ��������  ���� - �������� �������� ���� ��������� �����
	int m2 = (x & 1) << (kb + 1);
	x = x << 1;
	x = x | m1 | m2;// 0 ���-7 ��� ��������� �����, � 1 �� 8- ���� �����, 9 ���-0 ��� �����
	int m = 1;
	int y = 0;
	//for (int i = 8; i > 0; i = i - 1) {//���������� ������ �������� ���
	for (int i = kb; i > 0; i = i - 1) {
		//��������� ��������� �� ������� 000-0 001-1 010-1 011-1 100-1 101-0 110-0 111-0
		//cout << i << endl;
		//cout << bitset<10>(m1) << endl;
		int x1 = x & 7;//�������� ������  ��� � 0 �� 2
		//cout << bitset<10>(x1) << endl;
		x = x >> 1;//�������� ����� ����� �������� ��������� ������
		if (0 < x1 && x1 < 5) { y = y | m; }//
		//y = y >> 1;
		m = m << 1;
	}
	return y;
}
void cdelatK1(int* K1) {
	//int K1[256] = { 0 };
	int p = 0;
	//for (int i = 0; i < 256; i++) { cout << i << " - " << uf(i) << endl; }
	for (int i = 0; i < 256; i++) { K1[i] = uf(i); }
	//for (int i = 0; i < 256; i++) { cout << i << " - " << K1[i] << endl; }
	for (int i = 0; i < 256; i++) {
		//cout << i << "--";
		for (int j = 0; j < 256; j++) {
			p = 0;
			//if (K1[j] == i) { cout << j << " "; }
		}
		//cout << endl;
	//	cout << "    ";
	}
	int m = 0; int n = 0;
	int V[10] = { 0 }; int I[10] = { 0 };
	for (int i = 0; i < 256; i++) {
		n++;
		V[n] = i;
		for (int j = 0; j < 256; j++) {
			if (K1[j] == i) {
				m++;
				I[m] = j;
			}
		}
		while (m != 0 && n != 0) {
			K1[I[m]] = V[n];
			m--; n--;
		}
	}
	//for (int i = 0; i < 256; i++) {
	//	cout << i << " - " << K1[i] << endl;
	//}
}
void main() {
	setlocale(LC_ALL, "Russian");
	int* K1{ new int[256] };
	cdelatK1(K1);
	string key_tr;
	int nad;
	cout << "������� ����" << endl;
	cin >> key_tr;
	cout << "������� ���������� ������" << endl;
	cin >> nad;
	int S[100] = { 0 };
	//int M[10][10] = {0};
	int K[10][10] = { 0 };
	int k = 0;
	int n = 7;//����������� �������
	int m = 97;//����� �������� � ��������
	int p = key_tr.size();// ���������� �������� � ������
	for (int i = 0; i < p; i++) { S[i] = key_tr[i]; }//�� ������� 30
	//for (int i = 0; i < p; i++) { cout << S[i] << " "; }cout << endl << endl;
	for (int t = 0; t < nad; t++) { //���������� nad ������
		//S[k] = K1[S[k]];
		//n = S[k] % 4 + 2;// �� ������ ��� �� ������ ���� = 6
		//k++;
		//if (k == p) { k = 0; }
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				S[k] = K1[S[k]];
				//M[i][j] = S[k];
				K[i][j] = S[k] % m; //29;
				k++;
				if (k == p) { k = 0; };
			}
		}
		for (int x = 0; x < n; x++) {
			for (int z = 0; z < n; z++) {
				cout << K[x][z] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}