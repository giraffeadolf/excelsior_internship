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
	}
	return matrix;
}

// class of matrixes
class Matrix {
	int** matrix;
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

	int** read_matrix() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				input >> this->matrix[i][j];
			}
		}
		return this->matrix;
	}

	int** print_matrix() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				output << this->matrix[i][j] << " ";
			}
			output << "\n";
		}
		return this->matrix;
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

Matrix* search_pattern(Matrix* pattern, Matrix* matrix) {

	int n1 = pattern->getN();
	int n2 = matrix->getN();
	int m1 = pattern->getM();
	int m2 = matrix->getM();

	for (int i = 0; i < n2 - n1; i++) {
		for (int j = 0; j < m2 - m1; j++) {

		}
	}
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

	return 0;
}