#pragma once

#include<iostream>
#include"ComplexNum.h"
#include <cassert>

class ComplexMatrix
{
private:
	ComplexNum** matrix;
	int columns;
	int rows;
public:
	ComplexMatrix(unsigned int rows, unsigned int columns) {
		matrix = new ComplexNum * [rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new ComplexNum[columns];
		}
		this->columns = columns;
		this->rows = rows;
	}

	ComplexMatrix(const ComplexMatrix& copy) {
		this->rows = copy.rows;
		this->columns = copy.columns;
		matrix = new ComplexNum * [rows];
		for (int i = 0; i < this->rows; i++)
			this->matrix[i] = new ComplexNum[copy.columns];

		for (int i = 0; i < copy.rows; i++)
			for (int j = 0; j < copy.columns; j++)
				this->matrix[i][j] = copy.matrix[i][j];
	}

	~ComplexMatrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		this->rows = NULL;
		this->columns = NULL;
	}

	void auto_gen(int min_real, int max_real, int min_imag, int max_imag) {
		int span_real = abs(max_real - min_real) + 1;
		int span_imag = abs(max_imag - min_imag) + 1;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				matrix[i][j] = ComplexNum(rand() % span_real + min_real, rand() % span_imag + min_imag);
			}
		}
	}

	int get_columns() {
		return columns;
	}

	int get_rows() {
		return rows;
	}

	void set(unsigned int i, unsigned int j, double real, double imag) {
		assert(i < rows);
		assert(j < columns);
		matrix[i][j] = ComplexNum(real, imag);
	}

	void set(unsigned int i, unsigned int j, ComplexNum num) {
		assert(i < rows);
		assert(j < columns);
		matrix[i][j] = num;
	}

	void set_column(int j, ComplexNum* num)
	{
		for (int i = 0; i < this->rows; i++)
			this->set(i, j, num[i]);
	}

	void set_row(int i, ComplexNum* num)
	{
		for (int j = 0; j < this->columns; j++)
			this->set(i, j, num[j]);
	}

	ComplexNum get(unsigned int i, unsigned int j) {
		assert(i < rows);
		assert(j < columns);
		return matrix[i][j];
	}

	void print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				std::cout << "|" << matrix[i][j] << "|" << "\t";
				
			}
			std::cout << '\n';
		}
		std::cout << "\n\n";
	}

	//function for exchanging two rows of a matrix
	void swapRows(int row1, int row2)
	{
		assert(row1 >= 0 and row1 < rows);
		assert(row2 >= 0 and row2 < columns);

		int col = this->get_columns();
		for (int i = 0; i < col; i++)
		{
			ComplexNum temp = matrix[row1][i];
			matrix[row1][i] = matrix[row2][i];
			matrix[row2][i] = temp;
		}
	}

	int getRank()
	{
		ComplexMatrix complexMatrix = *this;

		int R = complexMatrix.get_rows();
		int rank = complexMatrix.get_columns();

		for (int row = 0; row < rank; row++)
		{
			if (complexMatrix.get(row, row) != ComplexNum())
			{
				for (int col = 0; col < R; col++)
				{
					if (col != row)
					{
						ComplexNum mult = complexMatrix.get(col, row) / complexMatrix.get(row, row);
						for (int i = 0; i < rank; i++)
							complexMatrix.set(col, i,
								complexMatrix.get(col, i) - mult * complexMatrix.get(row, i));
					}
				}
			}
			else
			{
				bool reduce = true;

				for (int i = row + 1; i < R; i++)
				{
					if (complexMatrix.get(i, row) != ComplexNum())
					{
						complexMatrix.swapRows(row, i);
						reduce = false;
						break;
					}
				}
				if (reduce)
				{
					rank--;
					for (int i = 0; i < R; i++)
						complexMatrix.set(i, row, complexMatrix.get(i, rank));
				}

				row--;
			}
		}

		return rank;
	}

	ComplexMatrix& operator =(const ComplexMatrix& copy) {
		if (this != &copy)
		{
			for (int i = 0; i < this->rows; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;

			matrix = new ComplexNum * [copy.rows];
			this->rows = copy.rows;
			this->columns = copy.columns;
			for (int i = 0; i < copy.rows; i++)
				this->matrix[i] = new ComplexNum[copy.columns];

			for (int i = 0; i < copy.rows; i++)
				for (int j = 0; j < copy.columns; j++)
					this->matrix[i][j] = copy.matrix[i][j];
		}
		return *this;
	}

	ComplexMatrix operator +(const ComplexMatrix& other)const  //add 2 matrix
	{
		ComplexMatrix temp(this->rows, this->columns);
		if (rows != other.rows || columns != other.columns)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					temp.matrix[i][j] = this->matrix[i][j];
			return temp;
		}
		else
		{
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					temp.matrix[i][j] = other.matrix[i][j] + matrix[i][j];

				}
			}
		}
		return temp;
	}

	ComplexMatrix operator *(const ComplexMatrix& other)const  //multiply (o(n^3) way) 2 matrix
	{
		ComplexMatrix res(this->rows, other.columns);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < other.columns; j++)
			{
				for (int k = 0; k < other.rows; k++)
				{
					auto to_check1 = this->matrix[i][k];
					auto to_check2 = other.matrix[k][j];
					res.matrix[i][j] = res.matrix[i][j] + this->matrix[i][k] * other.matrix[k][j];
				}
			}
		}
		return res;
	}

	bool operator ==(const ComplexMatrix& other)const
	{
		if (this->columns != other.columns || this->rows != other.rows)
			return false;

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				auto to_check1 = this->matrix[i][j];
				auto to_check2 = other.matrix[i][j];
				if (this->matrix[i][j] != other.matrix[i][j])
					return false;
			}
		}

		return true;
	}


	ComplexMatrix operator -(const ComplexMatrix& other)const  //subtract 2 matrix
	{
		ComplexMatrix temp(this->rows, this->columns);
		if (rows != other.rows || columns != other.columns)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					temp.matrix[i][j] = this->matrix[i][j];
			return temp;
		}
		else
		{
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					temp.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];

				}
			}
		}
		return temp;
	}
	
};


ComplexMatrix* regular_mult(ComplexMatrix* a, ComplexMatrix* b) {
	ComplexMatrix* res = new ComplexMatrix(a->get_rows(), b->get_columns());
	for (int i = 0; i < a->get_rows(); i++)
	{
		for (int j = 0; j < b->get_columns(); j++)
		{
			for (int k = 0; k < b->get_rows(); k++)
			{
				res->set(i, j, res->get(i, j) + a->get(i, k) * b->get(k, j));
			}
		}
	}
	return res;
}

ComplexMatrix* Strassen_rec(ComplexMatrix* a, ComplexMatrix* b) {
	// matrices sizes are M x N and N x Q
	int N = a->get_columns();
	int M = a->get_rows();
	int Q = b->get_columns();
	if (N <= 8 || M <= 8 || Q <= 8) {
		return regular_mult(a, b);
	}
	int new_N = N / 2 + N % 2;
	int new_M = M / 2 + M % 2;
	int new_Q = Q / 2 + Q % 2;
	ComplexMatrix a11(new_M, new_N);
	ComplexMatrix a12(new_M, new_N);
	ComplexMatrix a21(new_M, new_N);
	ComplexMatrix a22(new_M, new_N);

	for (int i = 0; i < new_M; i++) {
		for (int j = 0; j < new_N; j++) {
			a11.set(i, j, a->get(i, j));
			a12.set(i, j, ((j + new_N) < N) ? a->get(i, j + new_N) : ComplexNum(0, 0));
			a21.set(i, j, ((i + new_M) < M) ? a->get(i + new_M, j) : ComplexNum(0, 0));
			a22.set(i, j, ((i + new_M) < M && (j + new_N) < N) ? a->get(i + new_M, j + new_N) : ComplexNum(0, 0));
		}
	}


	ComplexMatrix b11(new_N, new_Q);
	ComplexMatrix b12(new_N, new_Q);
	ComplexMatrix b21(new_N, new_Q);
	ComplexMatrix b22(new_N, new_Q);

	for (int i = 0; i < new_N; i++) {
		for (int j = 0; j < new_Q; j++) {
			b11.set(i, j, b->get(i, j));
			b12.set(i, j, ((j + new_Q) < Q) ? b->get(i, j + new_Q) : ComplexNum(0, 0));
			b21.set(i, j, ((i + new_N) < N) ? b->get(i + new_N, j) : ComplexNum(0, 0));
			b22.set(i, j, ((i + new_N) < N && (j + new_Q) < Q) ? b->get(i + new_N, j + new_Q) : ComplexNum(0, 0));
		}
	}
	ComplexMatrix D1 = a11 + a22;
	ComplexMatrix D2 = b11 + b22;
	ComplexMatrix D3 = a21 + a22;
	ComplexMatrix D4 = b12 - b22;
	ComplexMatrix D5 = b21 - b11;
	ComplexMatrix D6 = a11 + a12;
	ComplexMatrix D7 = a21 - a11;
	ComplexMatrix D8 = b11 + b12;
	ComplexMatrix D9 = a12 - a22;
	ComplexMatrix D10 = b21 + b22;
	ComplexMatrix* M1;
	M1 = Strassen_rec(&D1/*(a11 + a22)*/, &D2/*(b11 + b22)*/);
	ComplexMatrix* M2;
	M2 = Strassen_rec(&D3/*(a21 + a22)*/, &b11);
	ComplexMatrix* M3;
	M3 = Strassen_rec(&a11, &D4/*(b12 - b22)*/);
	ComplexMatrix* M4;
	M4 = Strassen_rec(&a22, &D5/*(b21 - b11)*/);
	ComplexMatrix* M5;
	M5 = Strassen_rec(&D6/*(a11 + a12)*/, &(b22));
	ComplexMatrix* M6;
	M6 = Strassen_rec(&D7/*(a21 - a11)*/, &D8/*(b11 + b12)*/);
	ComplexMatrix* M7;
	M7 = Strassen_rec(&D9/*(a12 - a22)*/, &D10/*(b21 + b22)*/);

	ComplexMatrix R1 = *M1 + *M4 - *M5 + *M7;
	ComplexMatrix R2 = *M3 + *M5;
	ComplexMatrix R3 = *M2 + *M4;
	ComplexMatrix R4 = *M1 - *M2 + *M3 + *M6;
	ComplexMatrix* Res = new ComplexMatrix(M, Q);
	for (int i = 0; i < new_M; i++) {
		for (int j = 0; j < new_Q; j++) {
			Res->set(i, j, R1.get(i, j));
			if ((j + new_Q) < Q) {
				Res->set(i, j + new_Q, R2.get(i, j));
			}
			if ((i + new_M) < M) {
				Res->set(i + new_M, j, R3.get(i, j));
			}
			if ((i + new_M) < M && (j + new_Q) < Q) {
				Res->set(i + new_M, j + new_Q, R4.get(i, j));
			}
		}
	}
	delete M1; delete M2; delete M3; delete M4; delete M5; delete M6; delete M7;
	return Res;
}

ComplexMatrix* Strassen(ComplexMatrix* a, ComplexMatrix* b) {
	assert(a->get_columns() == b->get_rows());

	if (a->get_columns() <= 8 || a->get_rows() <= 8 || b->get_columns() <= 8) {
		return regular_mult(a, b);
	}

	return Strassen_rec(a, b);

}