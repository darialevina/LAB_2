#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include <windows.h>

#include "io/io.h"
#include "gtest/gtest.h" // adding gtest took a lot of time :(

const char* inputPath  = "inputA.txt";
const char* outputPath = "output.txt";
const int MAX_RECORDS = 1024;

void printArray(int* data, int len);

typedef void (__stdcall* dllSort)(int* data, int len);
dllSort sort = NULL;

int main(int argc, char* argv[]) {

	// Load DLL:

	printf("LAB 2\n");
	printf("Loading sorting.dll...\n");

	HINSTANCE h = LoadLibrary("sorting/sorting.dll");
	if (!h)	{
		printf("DLL not found.\n");
		getchar();
		return 0;
	}

	sort = (dllSort)GetProcAddress(h, "sort");
	if (!sort) {
		printf("DLL function load error.\n");
		getchar();
		return 0;
	}

	printf("DLL OK\n");

	// Sort file:

	int* data = new int[MAX_RECORDS];

	printf("Reading file...\n");

	int numRecords = readData(inputPath, data, MAX_RECORDS);

	if (!numRecords) {
		printf("No data.\n");
		getchar();
		return 0;
	}

	printf("Reading file OK\n");

	printf("Sorting data...\n");
	sort(data, numRecords);
	printf("Sorting data OK\n");

	printf("Writing file...\n");

	if (writeData(outputPath, data, numRecords)) {
		printf("Writing failed.\n");
		getchar();
		return 0;
	}
	printf("Writing file OK\n");

	delete [] data;

	// gtest:

	printf("Testing with gtest...\n");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	printf("Testing OK.\n");
	FreeLibrary(h);
	getchar();
	return 0;
}

// gtest tests:

void printArray(int* data, int len) {
	printf("Array: { ");
	for (int i = 0; i < len; i++) {
		printf("%i", data[i]);
		if (i != len - 1) { printf(", "); }
	}
	printf(" }\n");
}

::testing::AssertionResult isAscending(int* data, int len) {
	for (int i = 1; i < len; i++) {
		if (data[i] < data[i - 1]) {
			printArray(data, len);
			return ::testing::AssertionFailure();
		}
	}

	return ::testing::AssertionSuccess();
}

TEST(TestData, Empty     ) {                                                              sort(NULL,                          0); EXPECT_TRUE(isAscending(NULL,                          0)); }
TEST(TestData, OneItem   ) { int data[] = { 0xDEADBEEF,                                }; sort(data, sizeof(data) / sizeof(int)); EXPECT_TRUE(isAscending(data, sizeof(data) / sizeof(int))); }
TEST(TestData, Descending) { int data[] = { -3,  2,   1,  0,   1,       2,  3,         }; sort(data, sizeof(data) / sizeof(int)); EXPECT_TRUE(isAscending(data, sizeof(data) / sizeof(int))); }
TEST(TestData, Ascendng  ) { int data[] = {  1,  2,   3,  4,   5,       6,  7          }; sort(data, sizeof(data) / sizeof(int)); EXPECT_TRUE(isAscending(data, sizeof(data) / sizeof(int))); }
TEST(TestData, RandomA   ) { int data[] = {  7,  6, 334,  4,   3,  231010,  1, -10, -4 }; sort(data, sizeof(data) / sizeof(int)); EXPECT_TRUE(isAscending(data, sizeof(data) / sizeof(int))); }
TEST(TestData, RandomB   ) { int data[] = {  3, 56,  18, -7, 247,       0, -1,         }; sort(data, sizeof(data) / sizeof(int)); EXPECT_TRUE(isAscending(data, sizeof(data) / sizeof(int))); }
TEST(TestData, Same      ) { int data[] = {  7,  7,   7,  7,   7,       7,  7          }; sort(data, sizeof(data) / sizeof(int)); EXPECT_TRUE(isAscending(data, sizeof(data) / sizeof(int))); }