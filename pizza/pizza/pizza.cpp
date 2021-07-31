#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

int** allocate_matrix(int n, int m) {
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
		for (int j = 0; j < m; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;

}

void read_matrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << matrix[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

void delete_matrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void delete_triple(int*** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		delete_matrix(matrix[i], m);
	}
	delete[] matrix;
}

struct Pizza {
	int x, y, c;
	int s = 0, e = 0, n = 0, w = 0;

	Pizza() {};
	Pizza(int x, int y, int c) : x(x), y(y), c(c) {};
};

int min_dist(Pizza* pizzas, int*** dist, int x, int y, int n, int m, int k) {
	int result = INT16_MAX;
	int index;
	int maxc = 0;

	for (int i = 0; i < k; i++) {

		// случай когда заданы изначальные координаты пиццерии
		if (!dist[x][y][i]) {
			return i;
		}

		// провер€ем, чтобы рассто€ние было минимальным и Ємкость пиццерий была оптимальной
		if (dist[x][y][i] <= result && pizzas[i].c >= dist[x][y][i] && pizzas[i].c > maxc) {
			result = dist[x][y][i];
			maxc = pizzas[i].c;
			index = i;
		}
	}

	pizzas[index].c -= result;


	// обозначаем, в какую сторону раширилась пиццери€ и соответственно мен€ем рассто€ние до точек
	if (pizzas[index].x - 1 == x) {
		if (pizzas[index].y - 1 > y) {
			pizzas[index].e += result;
			for (int j = 0; j < m; j++) {
				if (j < pizzas[index].y - 1 - result) {
					dist[pizzas[index].x - 1][j][index] -= result;
					continue;
				}
				if (pizzas[index].y - 1 - result <= j && j < pizzas[index].y - 1) {
					dist[pizzas[index].x - 1][j][index] = 0;
					continue;
				}
			}
		}
		else {
			pizzas[index].w += result;
			for (int j = 0; j < m; j++) {
				if (j > pizzas[index].y - 1 - result) {
					dist[pizzas[index].x - 1][j][index] -= result;
					continue;
				}
				if (pizzas[index].y - 1 - result >= j && j > pizzas[index].y - 1) {
					dist[pizzas[index].x - 1][j][index] = 0;
					continue;
				}
			}
		}
	}
	if (pizzas[index].y - 1 == y) {
		if (pizzas[index].x - 1 > x) {
			pizzas[index].n += result;
			for (int j = 0; j < n; j++) {
				if (j < pizzas[index].x - 1 - result) {
					dist[j][pizzas[index].y - 1][index] -= result;
					continue;
				}
				if (pizzas[index].x - 1 - result <= j && j < pizzas[index].x - 1) {
					dist[j][pizzas[index].y - 1][index] = 0;
					continue;
				}
			}
		}
		else {
			pizzas[index].s += result;
			for (int j = 0; j < n; j++) {
				if (j > pizzas[index].x - 1 - result) {
					dist[j][pizzas[index].y - 1][index] -= result;
					continue;
				}
				if (pizzas[index].x - 1 - result >= j && j > pizzas[index].x - 1) {
					dist[j][pizzas[index].y - 1][index] = 0;
					continue;
				}
			}
		}
	}
	return index;
}


int main() {

	int count = 0;
	int n = 1;
	int m, k, x, y, c;

	input >> n;

	// цикл, считывающий все случаи
	while (n != 0) {

		count++;

		input >> m >> k;

		Pizza* pizzas = new Pizza[k];
		// вводим матрицу рассто€ний
		// 0 в координатах точки, в остальных точках "бесконечность"
		int*** dist = new int** [n];
		for (int i = 0; i < n; i++) {
			dist[i] = new int* [m];
			for (int j = 0; j < m; j++) {
				dist[i][j] = new int[k];
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				for (int l = 0; l < k; l++) {
					dist[i][j][l] = INT16_MAX;
				}
			}
		}

		// дл€ каждой пиццерии обозначаем рассто€ние до каждой доступной точки
		for (int i = 0; i < k; i++) {
			input >> x >> y >> c;
			pizzas[i] = Pizza(x, y, c);

			for (int j = 0; j < n; j++) {
				dist[j][y - 1][i] = abs(x - j - 1);
			}

			for (int j = 0; j < m; j++) {
				dist[x - 1][j][i] = abs(y - j - 1);
			}
		}

		// вы€вл€ем дл€ каждой точки ближайшую пиццерию
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				min_dist(pizzas, dist, i, j, n, m, k);
			}
		}

		output << "Case " << count << ":" << '\n';
		for (int i = 0; i < k; i++) {
			output << pizzas[i].s << ' ' << pizzas[i].e << ' ' << pizzas[i].n << ' ' << pizzas[i].w << '\n';
		}
		output << '\n';

		delete[] pizzas;
		delete_triple(dist, n, m);

		input >> n;
	}

	return 0;
}