#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo);
void CreateRows(int** a, const int k, const int n, const int Low, const int High, int rowNo);
void PrintRow(int** a, const int rowNo, const int n, int colNo);
void PrintRows(int** a, const int k, const int n, int rowNo);
int RowMax(int** a, const int rowNo, const int n, int colNo);
int MinOfRowMax(int** a, const int k, const int n, int rowNo);
bool SearchMinOfRowMax(int** a, const int k, const int n, int& minOfMax);

int main()
{
	srand((unsigned)time(NULL));

	int Low = -20;
	int High = 50;

	int k, n;
	cout << "k = "; cin >> k;
	cout << "n = "; cin >> n;

	int** a = new int* [k];
	for (int i = 0; i < k; i++)
		a[i] = new int[n];

	CreateRows(a, k, n, Low, High, 0);
	PrintRows(a, k, n, 0);

	int minOfMax;
	if (SearchMinOfRowMax(a, k, n, minOfMax))
		cout << "min of row maximums (even rows) = " << minOfMax << endl;
	else
		cout << "there are no even rows" << endl;

	for (int i = 0; i < k; i++)
		delete[] a[i];
	delete[] a;

	return 0;
}

void CreateRow(int** a, const int rowNo, const int n, const int Low, const int High, int colNo)
{
	a[rowNo][colNo] = Low + rand() % (High - Low + 1);
	if (colNo < n - 1)
		CreateRow(a, rowNo, n, Low, High, colNo + 1);
}

void CreateRows(int** a, const int k, const int n, const int Low, const int High, int rowNo)
{
	CreateRow(a, rowNo, n, Low, High, 0);
	if (rowNo < k - 1)
		CreateRows(a, k, n, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int n, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < n - 1)
		PrintRow(a, rowNo, n, colNo + 1);
	else
		cout << endl;
}

void PrintRows(int** a, const int k, const int n, int rowNo)
{
	PrintRow(a, rowNo, n, 0);
	if (rowNo < k - 1)
		PrintRows(a, k, n, rowNo + 1);
	else
		cout << endl;
}

int RowMax(int** a, const int rowNo, const int n, int colNo)
{
	if (colNo == n - 1)
		return a[rowNo][colNo];
	int restMax = RowMax(a, rowNo, n, colNo + 1);
	return a[rowNo][colNo] > restMax ? a[rowNo][colNo] : restMax;
}

int MinOfRowMax(int** a, const int k, const int n, int rowNo)
{
	int current = RowMax(a, rowNo, n, 0);
	if (rowNo + 2 < k)
	{
		int rest = MinOfRowMax(a, k, n, rowNo + 2);
		return current < rest ? current : rest;
	}
	return current;
}

bool SearchMinOfRowMax(int** a, const int k, const int n, int& minOfMax)
{
	if (k < 2)
		return false;
	minOfMax = MinOfRowMax(a, k, n, 1);
	return true;
}