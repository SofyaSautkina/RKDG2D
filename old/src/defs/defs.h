#ifndef DEFS_H_
#define DEFS_H_

#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
#include <functional>

#include "numvector.h"
#include "Point.h"


//- Number of basis functions
const int nShapes = 3;

const int dim = 5 * nShapes;

//- rotate coordinate system clockwise
numvector<double, 5> rotate(const numvector<double, 5>& sol, const Point& n);

//- rotate coordinate system counter-clockwise
numvector<double, 5> inverseRotate(const numvector<double, 5>& sol, const Point& n);

//std::vector<numvector<double, dim>> operator = (const std::vector<numvector<double, dim>>& a);

//- vector<numvector> * alpha
std::vector<numvector<double, dim>> operator * (const std::vector<numvector<double, dim>>& a, const double b);

//- Sum of two vector<numvector>s
std::vector<numvector<double, dim>> operator + (const std::vector<numvector<double, dim>>& b, const std::vector<numvector<double, dim>>& a);

// return LU-factorization of matrix (+ transform of rhs)

std::vector<std::vector<double> > forwardGauss(const std::vector<std::vector<double>>& data, bool partChoice = true);

std::vector<double > reverseGauss(const std::vector<std::vector<double>>& data);

int maxAbsPosition(const std::vector<std::vector<double>>& data, int i);

void ChangeRows(std::vector<std::vector<double>>& data, int p, int q);

namespace std
{
// ---------------------------------------------

//����������� � ������ �������� ������� ������� �������� �������
vector<vector<vector<double>>>& operator += (vector<vector<vector<double>>>& a, const vector<vector<vector<double>>>& b);

//����������� � ������ ���������� ������� ������� ���������� �������
vector<vector<double>>& operator += (vector<vector<double>>& a, const vector<vector<double>>& b);

//��������� �� ������ ���������� ������� ������� ���������� �������
vector<vector<double>>& operator -= (vector<vector<double>>& a, const vector<vector<double>>& b);

//���������� ����������� ������� �� �����
vector<vector<vector<double>>>& operator *= (vector<vector<vector<double>>>& a, const double b);
vector<vector<vector<double>>> operator * (const vector<vector<vector<double>>>& a, const double b);

//���������� ���������� ������� �� �����
vector<vector<double>>& operator *= (vector<vector<double>>& a, const double b);
vector<vector<double>> operator * (const vector<vector<double>>& a, const double b);

//���������� ������� �� �����
vector<double>& operator *= (vector<double>& a, const double b);
vector<double> operator * (const vector<double>& a, const double b);
vector<double> operator / (const vector<double>& a, const double b);

//����������� � ������ ������� �������
vector<double>& operator += (vector<double>& a, const vector<double>& b);

//��������� �� ������ ������� �������
vector<double>& operator -= (vector<double>& a, const vector<double>& b);


//��������� ������� �� ������
void prodMatrVec(const vector<vector<double>>& A, \
    const vector<double>& b, \
    vector<double>& c);

//��������� ������ �� ����������� �������� � ������. ����� (��� ���)
void prodWrAbsLWl(const vector<vector<double>>& Wr, \
    const vector<vector<double>>& Wl, \
    const vector<double>& L, \
    vector<vector<double>>& Prod);

}

#endif