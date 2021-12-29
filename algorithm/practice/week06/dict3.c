#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int		a, b;
	int		n, m;
	char	*answer;

	scanf("%d %d %d", &a, &b, &n);
	if (!(answer = (char *)malloc(sizeof(char) + (n + 1))))
		return (0);
	scanf("%s", answer);

	for (int i = 0; i < n; i++)
	{
		m = (a + b) / 2;
		if (answer[i] == 'Y')
			a = m + 1;
		else
			b = m;
		if (a == b)
			printf("%d", a);
	}
	free(answer);
	return (0);
}