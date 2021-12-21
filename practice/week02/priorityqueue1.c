#include <stdio.h>
#include <stdlib.h>

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

int main() {
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) scanf("%d", arr + i);

	inplaceSelectionSort(arr, n);
	for (int i = 0; i < n; i++) printf(" %d", arr[i]);
	free(arr);

	return 0;
}