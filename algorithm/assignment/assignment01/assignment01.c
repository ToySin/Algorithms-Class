#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define FT_SORT inplaceSelectionSort
#define SEED 10

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void inplaceSelectionSort(int* arr, int n) {
	int max = 0;
	for (int i = n - 1; i > 0; i--) {
		max = 0;
		for (int j = 0; j <= i; j++) if (arr[max] < arr[j]) max = j;
		swap(arr + i, arr + max);
	}
}

void inplaceInsertionSort(int* arr, int n) {
	int j;
	int temp;

	for (int i = 1; i < n; i++) {
		j = i - 1;
		temp = arr[i];
		while ((j >= 0) && (temp < arr[j])) {
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = temp;
	}
}

double return_sec_count(int* arr, int n, void (*fp)(int*, int)) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	double rst_time;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	fp(arr, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	rst_time = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
	return rst_time;
}

double random_n(int n, void (*fp)(int*, int)) {
	int* arr = (int*)malloc(sizeof(int) * n);
	double t, total = 0;

	srand(SEED);
	for (int r = 0; r < 5; r++) {
		for (int i = 0; i < n; i++)
			arr[i] = rand() & 10000000 + 1;

		t = return_sec_count(arr, n, fp);
		total += t;
		printf("Check %d: %.10f\n", r + 1, t);
	}
	printf("Random Size %d's average time: %.10f", n, total / 5.0);
	free(arr);
	return total / 5.0;
}

double sorted_n(int n, void (*fp)(int*, int)) {
	int* arr = (int*)malloc(sizeof(int) * n);
	double t;

	for (int i = 0; i < n; i++)
		arr[i] = i + 1;

	t = return_sec_count(arr, n, fp);

	printf("Sorted Size %d's time: %.10f", n, t);
	free(arr);
	return t;
}

double reversed_n(int n, void (*fp)(int*, int)) {
	int* arr = (int*)malloc(sizeof(int) * n);
	double t;

	for (int i = 0; i < n; i++)
		arr[i] = n - i;

	t = return_sec_count(arr, n, fp);

	printf("Reversed Size %d's time: %.10f", n, t);
	free(arr);
	return t;
}

int main() {
	printf("\n\n====SelectionSort====\n\n");
	//printf("\n\n====InsertionSort====\n\n");
	/*
	printf("----Random----\n");
	random_n(10000, FT_SORT);
	printf("\n\n");
	random_n(20000, FT_SORT);
	printf("\n\n");
	random_n(30000, FT_SORT);
	printf("\n\n");
	random_n(40000, FT_SORT);
	printf("\n\n");
	random_n(50000, FT_SORT);
	printf("\n\n");
	random_n(60000, FT_SORT);
	printf("\n\n");
	random_n(70000, FT_SORT);
	printf("\n\n");
	random_n(80000, FT_SORT);
	printf("\n\n");
	random_n(90000, FT_SORT);
	printf("\n\n");
	random_n(100000, FT_SORT);
	printf("\n\n");
	*/
	
	printf("----Sorted----\n");
	sorted_n(10000, FT_SORT);
	printf("\n\n");
	sorted_n(20000, FT_SORT);
	printf("\n\n");
	sorted_n(30000, FT_SORT);
	printf("\n\n");
	sorted_n(40000, FT_SORT);
	printf("\n\n");
	sorted_n(50000, FT_SORT);
	printf("\n\n");
	sorted_n(60000, FT_SORT);
	printf("\n\n");
	sorted_n(70000, FT_SORT);
	printf("\n\n");
	sorted_n(80000, FT_SORT);
	printf("\n\n");
	sorted_n(90000, FT_SORT);
	printf("\n\n");
	sorted_n(100000, FT_SORT);
	printf("\n\n");
	/*
	printf("----Reversed----\n");
	reversed_n(10000, FT_SORT);
	printf("\n\n");
	reversed_n(20000, FT_SORT);
	printf("\n\n");
	reversed_n(30000, FT_SORT);
	printf("\n\n");
	reversed_n(40000, FT_SORT);
	printf("\n\n");
	reversed_n(50000, FT_SORT);
	printf("\n\n");
	reversed_n(60000, FT_SORT);
	printf("\n\n");
	reversed_n(70000, FT_SORT);
	printf("\n\n");
	reversed_n(80000, FT_SORT);
	printf("\n\n");
	reversed_n(90000, FT_SORT);
	printf("\n\n");
	reversed_n(100000, FT_SORT);
	printf("\n\n");
	*/
	return 0;
}