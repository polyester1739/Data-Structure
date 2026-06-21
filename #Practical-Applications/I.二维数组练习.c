#include <stdio.h>
#include <stdlib.h>

typedef struct mat
{
	int* base;
	int* bounds;
	int* constant;
}mat;

mat* InitArray(int bound1, int bound2);
void DestroyArray(mat* m);
void Value(mat* m, int* e, int index1, int index2);
void Assign(mat* m, int* e, int index1, int index2);

int main(int argc, const char* argv[])
{
	mat* matrix = InitArray(4,5);
	int num = 15;
	Assign(matrix, &num, 3, 4);
	num = 25;
	Assign(matrix, &num, 2, 4);
	num = 35;
	Assign(matrix, &num, 0, 2);
	Value(matrix, &num, 3, 4);
	Value(matrix, &num, 2, 4);
	Value(matrix, &num, 0, 2);
	Value(matrix, &num, 1, 1);
	DestroyArray(matrix);
}

mat* InitArray(int bound1, int bound2)
{
	mat* ret = (mat*)malloc(sizeof(mat));
	if (!ret) exit(EXIT_FAILURE);
	int elemtotal = bound1 * bound2;
	int* ret_base = (int*)malloc(sizeof(int) * elemtotal);
	if (!ret_base) exit(EXIT_FAILURE);
	for (int i = 0; i < elemtotal; i++) ret_base[i] = 0;
	ret->base = ret_base;
	int* ret_bounds = (int*)malloc(sizeof(int) * 2);
	if (!ret_bounds) exit(EXIT_FAILURE);
	ret_bounds[0] = bound1;
	ret_bounds[1] = bound2;
	ret->bounds = ret_bounds;
	int* ret_const = (int*)malloc(sizeof(int) * 2);
	if (!ret_const) exit(EXIT_FAILURE);
	ret_const[1] = 1;
	ret_const[0] = ret_const[1] * ret_bounds[1];
	ret->constant = ret_const;
	return ret;
}

void DestroyArray(mat* m)
{
	free(m->base);
	free(m->bounds);
	free(m->constant);
	free(m);
}

void Value(mat* m, int* e, int index1, int index2)
{
	if (index1 < 0 || index1 > m->bounds[0]-1) exit(EXIT_FAILURE);
	if (index2 < 0 || index2 > m->bounds[1]-1) exit(EXIT_FAILURE);
	int pos = index1 * m->constant[0] + index2 * m->constant[1];
	*e = m->base[pos];
	//printf("%d\n", *e);
}

void Assign(mat* m, int* e, int index1, int index2)
{
	if (index1 < 0 || index1 > m->bounds[0] - 1) exit(EXIT_FAILURE);
	if (index2 < 0 || index2 > m->bounds[1] - 1) exit(EXIT_FAILURE);
	int pos = index1 * m->constant[0] + index2 * m->constant[1];
	m->base[pos] = *e;
}