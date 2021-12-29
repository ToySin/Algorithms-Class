#include <stdio.h>
#include <stdlib.h>

void    merge(int *arr, int start, int mid, int end)
{
    int *sorted = (int *)malloc(sizeof(int) * (end - start + 1));
    int i, j, k;
    
    k = 0;
    i = start;
    j = mid + 1;
    while (i <= mid && j <= end)
    {
        if (arr[i] > arr[j])
            sorted[k++] = arr[i++];
        else
            sorted[k++] = arr[j++];
    }
    while (i <= mid)
        sorted[k++] = arr[i++];
    while (j <= end)
        sorted[k++] = arr[j++];
    for (i = 0; i < k; i++)
        arr[start + i] = sorted[i];
    
    free(sorted);
}

void    mergesort(int *arr, int start, int end)
{
    int mid = (start + end) / 2;
    
    if (start >= end)
        return;
    
    mergesort(arr, start, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

int main(){
    int n;
    int *arr;
    
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
        
    mergesort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++)
        printf(" %d", arr[i]);
	
	free(arr);
	return 0;
}