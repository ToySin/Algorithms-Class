#include<stdio.h>
#include<stdlib.h>

void swap(int* a, int* b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int median(int a, int b, int c) {
    if (a >= b) {
        if (a >= c) return a;
        else return c;
    }
    else if (b >= c) return b;
    else return c;
}

int inPlacePartition(int* List, int left, int right, int key) {
    int pivot, i, j;
    pivot = List[key];
    swap(List + key, List + left);
    key = left;
    for (i = key + 1, j = right; i <= j;) {
        if (List[i] < List[key]) {
            swap(List + i, List + key);
            i++;
            key++;
        }
        else if (List[i] == List[key]) {
            i++;
        }
        else {
            swap(List + i, List + j);
            j--;
        }
    }
    return key;
}

void inPlaceQuickSort(int* List, int left, int right) {
    int k, a, b, i;
    if (left >= right) return;
    k = inPlacePartition(List, left, right, (left + right) / 2);
    a = k - 1;
    for (b = k + 1; List[b] == List[k];)b++;
    inPlaceQuickSort(List, left, a);
    inPlaceQuickSort(List, b, right);
}

int main() {
    int N, * arr, i;

    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int) * N);

    for (i = 0; i < N; i++) scanf("%d", arr + i);

    inPlaceQuickSort(arr, 0, N - 1);

    for (i = 0; i < N; i++) printf(" %d", arr[i]);
    return 0;
}
