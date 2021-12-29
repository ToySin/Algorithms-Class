#include <stdio.h>

int H[100];
int n;

void upHeap(int i) {
	if (i == 1)
		return;
	int temp;
	if (H[i] > H[i / 2]) {
		temp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = temp;
		upHeap(i / 2);
	}
}

void downHeap(int i) {
	if (i == 1)
		H[1] = H[n];
	if (i * 2 + 1 > n)
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

int insertItem(int key) {
	H[n + 1] = key;
	upHeap(n + 1);
	n++;
	return 0;
}

int removeMax() {
	int k = H[1];
	H[1] = H[n];
	downHeap(1);
	n--;
	return k;
}

void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
}

int main() {
	char oper;
	int key;

	while (1) {
		scanf("%c", &oper);
		switch (oper) {
		case 'i':
			scanf("%d", &key);
			printf("%d\n", insertItem(key));
			break;
		case 'd':
			printf("%d\n", removeMax());
			break;
		case 'p':
			printHeap();
			printf("\n");
			break;
		case 'q':
			return 0;
		}
	}
}