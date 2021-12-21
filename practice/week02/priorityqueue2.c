#include <stdio.h>
#include <stdlib.h>

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

int main() {
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) scanf("%d", arr + i);

	inplaceInsertionSort(arr, n);
	for (int i = 0; i < n; i++) printf(" %d", arr[i]);
	free(arr);

	return 0;
}