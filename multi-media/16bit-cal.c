#include <stdio.h>

void	binary(int n)
{
	if (n > 1)
		binary(n / 2);
	printf("%d", n % 2);
}

int main()
{
	int n;

	scanf("%d", &n);

	binary(n);
	printf("\n");

	return 0;
}