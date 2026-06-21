#include <stdio.h>
#include <stdlib.h>

typedef struct mat
{
	int* base;
	int n;
}mat;

mat* initmat(int n);
void demonstrate(mat* m);

int main(int argc, const char* argv[])
{
	mat* m = initmat(5);
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j == i) m->base[(i + 1) * i / 2 + j] = 1;
			else if (j == i - 1) m->base[(i + 1) * i / 2 + j] = 2;
			else m->base[(i + 1) * i / 2 + j] = 3;
		}
	}
	demonstrate(m);
	free(m->base);
	free(m);
}

mat* initmat(int n)
{
	mat* ret = (mat*)malloc(sizeof(mat));
	if (!ret) exit(EXIT_FAILURE);
	ret->n = n;
	ret->base = (int*)malloc(sizeof(int) * n * (n + 1) / 2);
	if (!ret->base) exit(EXIT_FAILURE);
	for (int i = 0; i < n * (n + 1) / 2; i++) ret->base[i] = 0;
	return ret;
}

void demonstrate(mat* m)
{
	int** demo = (int**)malloc(sizeof(int*) * m->n);
	if (!demo) exit(EXIT_FAILURE);
	for (int i = 0; i < m->n; i++)
	{
		demo[i] = (int*)malloc(sizeof(int) * m->n);
		if (!demo[i]) exit(EXIT_FAILURE);
	}
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j < m->n; j++)
		{
			if (j <= i) demo[i][j] = m->base[(1 + i) * i / 2 + j];
			else demo[i][j] = m->base[(1 + j) * j / 2 + i];
			printf("%d\t",demo[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < m->n; i++) free(demo[i]);
	free(demo);
}
/*
	1 2 3 3 3
	2 1 2 3 3
	3 2 1 2 3
	3 3 2 1 2
	3 3 3 2 1
*/