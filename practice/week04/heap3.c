#include <stdio.h>

int H[100];
int n;

void downHeap(int i, int max_idx) {
	if (i * 2 > max_idx)
		return;
	int left = i * 2;
	int right = i * 2 + 1;
	int max;

	if (left > max_idx)
		return;
	if (right > max_idx) {
		if ((H[left] <= H[i]))
			return;
		else {
			max = H[left];
			H[left] = H[i];
			H[i] = max;
			return;
		}
	}
	
	if (H[left] > H[right])
		max = H[left];
	else
		max = H[right];
	if (max > H[i]) {
		if (max == H[left]) {
			H[left] = H[i];
			H[i] = max;
			downHeap(left, max_idx);
		}
		else {
			H[right] = H[i];
			H[i] = max;
			downHeap(right, max_idx);
		}
	}
}

void rBuildHeap(int i) {
	if (i > n)
		return;

	rBuildHeap(i * 2);
	rBuildHeap(i * 2 + 1);
	downHeap(i, n);
}

void printArray() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
}

void inPlaceHeapSort() {
	rBuildHeap(1);
	int temp;
	for (int i = n; i > 1; i--) {
		temp = H[i];
		H[i] = H[1];
		H[1] = temp;
		downHeap(1, i - 1);
	}
}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	inPlaceHeapSort();

	printArray();

	return 0;
}