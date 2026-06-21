#include <stdio.h>
#include <stdlib.h>

typedef struct matrixDescription
{
	int row;
	int col;
	int data;
}mat;

mat** initmat(int row, int col, int numberOfData);
void demonstrate(mat** m);
void DestroyMat(mat** m);

int main(int argc, const char* argv[])
{
	mat** m = initmat(6, 10, 3);
	m[1]->row = 0;
	m[2]->row = 2;
	m[3]->row = 4;
	m[1]->col = 7;
	m[2]->col = 4;
	m[3]->col = 1;
	m[1]->data = 114514;
	m[2]->data = 32767;
	m[3]->data = 10086;
	demonstrate(m);
	DestroyMat(m);
}

mat** initmat(int row, int col, int numberOfData)
{
	mat** ret = (mat**)malloc((numberOfData + 1) * sizeof(mat*));
	if (!ret) exit(EXIT_FAILURE);
	for (int i = 0; i < numberOfData + 1; i++)
	{
		ret[i] = (mat*)malloc(sizeof(mat));
		if (!ret[i]) exit(EXIT_FAILURE);
	}
	ret[0]->row = row;
	ret[0]->col = col;
	ret[0]->data = numberOfData;
	return ret;
}

void demonstrate(mat** m)
{
	int** demo = (int**)malloc(m[0]->row * sizeof(int*));
	if (!demo) exit(EXIT_FAILURE);
	for (int i = 0; i < m[0]->row; i++)
	{
		demo[i] = (int*)malloc(m[0]->col * sizeof(int));
		if (!demo[i]) exit(EXIT_FAILURE);
	}
	for (int i = 0; i < m[0]->row; i++) for (int j = 0; j < m[0]->col; j++) demo[i][j] = 0;
	for (int i = 1; i < m[0]->data + 1; i++) demo[m[i]->row][m[i]->col] = m[i]->data;
	for (int i = 0; i < m[0]->row; i++)
	{
		for (int j = 0; j < m[0]->col; j++) printf("%d\t", demo[i][j]);
		printf("\n");
	}
	for (int i = 0; i < m[0]->row; i++) free(demo[i]);
	free(demo);
}

void DestroyMat(mat** m)
{
	for (int i = 0; i < m[0]->data + 1; i++) free(m[i]);
	free(m);
}