#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

char** allocate_matrix(int n, int m) {
	char** matrix = new char* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new char[m];
	}
	return matrix;
}

// class of matrixes
class Matrix {
	char** matrix;
	int n;
	int m;
public:
	//default constructor
	Matrix(int n, int m) : n(n), m(m) {
		this->matrix = allocate_matrix(n, m);
	}

	//copying constructor
	Matrix(const Matrix& orig) {
		this->n = orig.n;
		this->m = orig.m;
		matrix = allocate_matrix(n, m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				this->matrix[i][j] = orig.matrix[i][j];
			}
		}
	}

	char** read_matrix() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				input >> this->matrix[i][j];
			}
		}
		return this->matrix;
	}

	char** print_matrix() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				output << this->matrix[i][j] << " ";
			}
			output << "\n";
		}
		return this->matrix;
	}

	char getValue(int row, int column) {
		return matrix[row][column];
	}

	void setValue(int row, int column, int value) {
		matrix[row][column] = value;
	}

	int getN() {
		return n;
	}

	int getM() {
		return m;
	}

	~Matrix() {
		for (int i = 0; i < n; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
};


int check_pattern(Matrix* pattern, Matrix* matrix, int column, int row) {
	int n1 = pattern->getN();
	int m1 = pattern->getM();
	int is_id = 0;
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m1; j++) {
			if (matrix->getValue(row + i, column + j) == pattern->getValue(i, j)) {
				continue;
			}
			else {
				is_id = 1;
				break;
			}
		}
		if (is_id) { break; }
	}
	return is_id;
}

Matrix* mark_pattern(Matrix* pattern, Matrix* matrix, int column, int row) {
	int n1 = pattern->getN();
	int m1 = pattern->getM();
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m1; j++) {
			if (matrix->getValue(row + i, column + j) == '1') {
				matrix->setValue(row + i, column + j, '2');
			}
			else {
				matrix->setValue(row + i, column + j, '*');
			}
		}
	}
	return matrix;
}

Matrix* search_pattern(Matrix* pattern, Matrix* matrix) {

	int n1 = pattern->getN();
	int n2 = matrix->getN();
	int m1 = pattern->getM();
	int m2 = matrix->getM();

	for (int i = 0; i <= n2 - n1; i++) {
		for (int j = 0; j <= m2 - m1; j++) {
			if (!check_pattern(pattern, matrix, i, j)) {
				mark_pattern(pattern, matrix, i, j);
			}
		}
	}

	return matrix;
}

int main() {

	int n, m;

	//reading the pattern
	input >> n >> m;
	Matrix* pattern = new Matrix(n, m);
	pattern->read_matrix();

	//reading the matrix to search
	input >> n >> m;
	Matrix* searchm = new Matrix(n, m);
	searchm->read_matrix();

	Matrix* result = search_pattern(pattern, searchm);

	result->print_matrix();

	return 0;
}