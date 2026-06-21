#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct mat
{
	int* base;
	int n;
	bool upper;
}mat;

mat* initmat(int n, bool upper);
void demonstrate(mat* m);

int main(int argc, const char* argv[])
{
	mat* m = initmat(5, true);
	for (int i = 0; i < (m->n + 1) * m->n / 2; i++)m->base[i] = i+10;
	m->base[(m->n + 1) * m->n / 2] = 1;
	demonstrate(m);
	free(m->base);
	free(m);
}

mat* initmat(int n, bool upper)
{
	mat* ret = (mat*)malloc(sizeof(mat));
	if (!ret) exit(EXIT_FAILURE);
	ret->n = n;
	ret->base = (int*)malloc(sizeof(int) * ((n + 1) * n / 2 + 1));
	if (!ret->base) exit(EXIT_FAILURE);
	for (int i = 0; i < (n + 1) * n / 2 + 1; i++)ret->base[i] = 0;
	ret->upper = upper;
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
	if (!m->upper)
	{
		for (int i = 0; i < m->n; i++)
		{
			for (int j = 0; j < m->n; j++)
			{
				if (j <= i)demo[i][j] = m->base[(1 + i) * i / 2 + j];
				else demo[i][j] = m->base[(m->n + 1) * m->n / 2];
			}
		}
	}
	else
	{
		for (int i = 0; i < m->n; i++)
		{
			for (int j = 0; j < m->n; j++)
			{
				if (j < i)demo[i][j] = m->base[(m->n + 1) * m->n / 2];
				else demo[i][j] = m->base[(i * (2 * m->n - i + 1)) / 2 + j - i];
			}
		}
	}
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j < m->n; j++) printf("%d\t", demo[i][j]);
		printf("\n");
	}
	for (int i = 0; i < m->n; i++) free(demo[i]);
	free(demo);
}