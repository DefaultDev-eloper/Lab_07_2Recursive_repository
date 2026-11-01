#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_2Recursive.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab722Tests
{
	static int** MakeMatrix(const int* data, int k, int n) {
		int** m = new int* [k];
		for (int i = 0; i < k; i++) {
			m[i] = new int[n];
			for (int j = 0; j < n; j++)
				m[i][j] = data[i * n + j];
		}
		return m;
	}

	static void FreeMatrix(int** m, int k) {
		for (int i = 0; i < k; i++)
			delete[] m[i];
		delete[] m;
	}

	TEST_CLASS(RecursiveTests)
	{
	public:
		TEST_METHOD(CreateRows_ValuesInRange)
		{
			const int k = 5, n = 6;
			int zeros[k * n] = {};
			int** a = MakeMatrix(zeros, k, n);
			CreateRows(a, k, n, -20, 50, 0);
			for (int i = 0; i < k; i++)
				for (int j = 0; j < n; j++) {
					Assert::IsTrue(a[i][j] >= -20);
					Assert::IsTrue(a[i][j] <= 50);
				}
			FreeMatrix(a, k);
		}

		TEST_METHOD(RowMax_FindsMaximum)
		{
			int data[] = { 3, 9, -1, 4 };
			int** a = MakeMatrix(data, 1, 4);
			Assert::AreEqual(9, RowMax(a, 0, 4, 0));
			FreeMatrix(a, 1);
		}

		TEST_METHOD(RowMax_AllNegative)
		{
			int data[] = { -5, -2, -9 };
			int** a = MakeMatrix(data, 1, 3);
			Assert::AreEqual(-2, RowMax(a, 0, 3, 0));
			FreeMatrix(a, 1);
		}

		TEST_METHOD(RowMax_SingleElement)
		{
			int data[] = { 7 };
			int** a = MakeMatrix(data, 1, 1);
			Assert::AreEqual(7, RowMax(a, 0, 1, 0));
			FreeMatrix(a, 1);
		}

		TEST_METHOD(MinOfRowMax_StartFromSecondRow)
		{
			int data[] = { 0, 0, 0,
						   4, 2, 7,
						   1, 1, 1,
						   5, 6, 1,
						   9, 9, 9 };
			int** a = MakeMatrix(data, 5, 3);
			Assert::AreEqual(6, MinOfRowMax(a, 5, 3, 1));
			FreeMatrix(a, 5);
		}

		TEST_METHOD(Search_IgnoresOddRows)
		{
			int data[] = { 0, 0, 0,
						   4, 2, 7,
						   1, 1, 1,
						   5, 6, 1,
						   9, 9, 9 };
			int** a = MakeMatrix(data, 5, 3);
			int result = 0;
			Assert::IsTrue(SearchMinOfRowMax(a, 5, 3, result));
			Assert::AreEqual(6, result);
			FreeMatrix(a, 5);
		}

		TEST_METHOD(Search_OnlyOneEvenRow)
		{
			int data[] = { 1, 2,
						   3, 4 };
			int** a = MakeMatrix(data, 2, 2);
			int result = 0;
			Assert::IsTrue(SearchMinOfRowMax(a, 2, 2, result));
			Assert::AreEqual(4, result);
			FreeMatrix(a, 2);
		}

		TEST_METHOD(Search_NegativeValues)
		{
			int data[] = { -5, -1,
						   -7, -3,
							0,  0,
						   -9, -8 };
			int** a = MakeMatrix(data, 4, 2);
			int result = 0;
			Assert::IsTrue(SearchMinOfRowMax(a, 4, 2, result));
			Assert::AreEqual(-8, result);
			FreeMatrix(a, 4);
		}

		TEST_METHOD(Search_NoEvenRows)
		{
			int data[] = { 1, 2, 3 };
			int** a = MakeMatrix(data, 1, 3);
			int result = 0;
			Assert::IsFalse(SearchMinOfRowMax(a, 1, 3, result));
			FreeMatrix(a, 1);
		}
	};
}