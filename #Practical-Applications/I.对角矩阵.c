#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int** data;
	int n;
	int halfDiag;	//°ë´ø¿í
}mat;

mat* initmat(int n, int halfDiag);
void demonstrate(mat* m);
void DestroyMat(mat* m);

int main(int argc, const char* argv[])
{
	mat* m = initmat(5, 1);
	for (int i = 0; i < 4; i++)m->data[0][i] = 10+i;
	for (int i = 0; i < 5; i++)m->data[1][i] = 20+i;
	for (int i = 0; i < 4; i++)m->data[2][i] = 30+i;
	demonstrate(m);
	DestroyMat(m);
}

mat* initmat(int n, int halfDiag)
{
	if (halfDiag > n - 1) exit(EXIT_FAILURE);
	mat* ret = (mat*)malloc(sizeof(mat));
	if (!ret) exit(EXIT_FAILURE);
	ret->n = n;
	ret->halfDiag = halfDiag;
	ret->data = (int**)malloc(sizeof(int*) * (1 + 2 * halfDiag));
	if (!ret->data) exit(EXIT_FAILURE);
	for (int i = 0; i < 1 + 2 * halfDiag; i++)
	{
		ret->data[i] = (int*)malloc(sizeof(int) * n);
		if (!ret->data[i]) exit(EXIT_FAILURE);
	}
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
	for (int i = 0; i < m->n; i++) for (int j = 0; j < m->n; j++) demo[i][j] = 0;
	/*for (int i = m->halfDiag, j = 0; i > -1; i--, j++)
		for (int a = i, b = 0, c = 0; a < m->n && b < m->n; a++, b++, c++)
		demo[a][b] = m->data[j][c];
	for (int i = 1, j = m->halfDiag + 1; i <= m->halfDiag; i++, j++)
		for (int a = 0, b = i, c = 0; a < m->n && b < m->n; a++, b++, c++)
		demo[a][b] = m->data[j][c];*/
	int row, col;
	for (int i = -m->halfDiag; i < m->halfDiag + 1; i++)
	{
		if (i < 0)
		{
			row = abs(i);
			col = 0;
		}
		else
		{
			row = 0;
			col = i;
		}
		for (int num = 0; row < m->n && col < m->n; row++, col++, num++)
			demo[row][col] = m->data[i + m->halfDiag][num];
	}
	for (int i = 0; i < m->n; i++)
	{
		for (int j = 0; j < m->n; j++) printf("%d\t", demo[i][j]);
		printf("\n");
	}
	for (int i = 0; i < m->n; i++) free(demo[i]);
	free(demo);
}

void DestroyMat(mat* m)
{
	for (int i = 0; i < 2 * m->halfDiag + 1; i++) free(m->data[i]);
	free(m->data);
	free(m);
}