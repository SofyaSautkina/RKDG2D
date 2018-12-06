#pragma once

//- Number of conservative variables
const int PhysDim = 5;  // !!!���������� �������� � ����� ����!!!

//- Number of basis functions
const int nShapes = 3;

//- Initialisaton of tools for computations
void Initialize() {}


// ���������� ����������. 
enum Variables
{
	r = 0, U = 0, \
		rvx = 1, rvy = 2, rvz = 3, e = 4//, \
		Hx = 5, Hy = 6, Hz = 7
};
//��� ������ "��� ������"
enum CaseInit
{
	Const, Acoustic, Acoustic1D, SodX, SodY, SodDiag, SodCircle, Blast
};
enum CaseBound
{
	Inf, Free, Diag, Wall, PeriodicSquare
};

