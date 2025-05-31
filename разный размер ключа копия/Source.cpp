#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>  
#include <bitset>
using namespace std;
int uf(int x) {
	int kb = 8;
	int m1 = x >> (kb - 1);
	int m2 = (x & 1) << (kb + 1);
	x = x << 1;
	x = x | m1 | m2;// 0 бит-7 бит заданного числа, с 1 по 8- саио число, 9 бит-0 бит числа
	int m = 1;
	int y = 0;
	for (int i = kb; i > 0; i = i - 1) {
		int x1 = x & 7;//выделяем тройку  бит с 0 по 2
		x = x >> 1;//сдвигаем число чтобы получить следующую тройку
		if (0 < x1 && x1 < 5) { y = y | m; }//
		m = m << 1;
	}
	return y;
}
void cdelatK1(int* K1) {
	int p = 0;
	for (int i = 0; i < 256; i++) { K1[i] = uf(i); }
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			p = 0;
		}
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
}
void main() {
	setlocale(LC_ALL, "Russian");
	int* K1{ new int[256] };
	cdelatK1(K1);
	string key_tr;
	int nad;
	int n;//размерность матрицы
	cout << "Алфавит" << endl;
	for (int i = 32; i < 127; i++) { cout << char(i) << " "; }
	cout << endl;
	cout << "Введите ключ(без пробелов)" << endl;
	cin >> key_tr;
	cout << "Введите количество матриц" << endl;
	cin >> nad;
	cout << "Введите размерность матриц" << endl;
	cin >> n;
	int S[100] = { 0 };
	int** K = new int* [n];
	for (int i = 0; i < n; ++i) {
		K[i] = new int[n];
	}
	int k = 0;
	int m = 97;//число символов в алфавите
	int p = key_tr.size();// количество символов в строке
	for (int i = 0; i < p; i++) { S[i] = key_tr[i]; }//по правилу 30

	for (int t = 0; t < nad; t++) { //генерируем nad матриц
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				S[k] = K1[S[k]];
				K[i][j] = S[k] ; 
				k++;
				if (k == p) { k = 0; };
			}
		}
		
		int x = K[n - 1][n - 1];
		int y = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				y = K[i][j];
				if (x == 0) { x = 1; }//чтобы не было деления на ноль
				if (y == 0) { y = 1; }
				
				K[i][j] = (max(x, y) % min(x, y)) % m;
				x = y;
				
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