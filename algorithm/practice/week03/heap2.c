#include <stdio.h>

int H[100];
int n;

void downHeap(int i) {
	if (i * 2 > n)
		return;
	int left = i * 2;
	int right = i * 2 + 1;
	int max;
	if (H[left] > H[right])
		max = H[left];
	else
		max = H[right];
	if (max > H[i]) {
		if (max == H[left]) {
			H[left] = H[i];
			H[i] = max;
			downHeap(left);
		}
		else {
			H[right] = H[i];
			H[i] = max;
			downHeap(right);
		}
	}
}

void rBuildHeap(int i) {
	if (i > n)
		return;

	rBuildHeap(i * 2);
	rBuildHeap(i * 2 + 1);
	downHeap(i);
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) downHeap(i);
}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
}

int main() {
	int total_key;
	int key;

	scanf("%d", &total_key);
	n = total_key;
	for (int i = 1; i <= total_key; i++) {
		scanf("%d", &key);
		H[i] = key;
	}

	rBuildHeap(1);
	printHeap();
	return 0;
}