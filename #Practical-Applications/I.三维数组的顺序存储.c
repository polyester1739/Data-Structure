#include <stdio.h>
#include <stdlib.h>

typedef int zhengshu;

typedef struct {
	zhengshu* base;		//基地址
	int dim;			//维数
	int* bounds;		//维界
	int* constant;		//常数
}array;

void initialize(array* a, int dim);
void destroyArray(array* arr);
void assignArray(array* arr, zhengshu a);
void get_data(array* arr);


int main(int argc, const char* argv[])
{
	int dim = 3;
	array* arr = (array*)malloc(sizeof(array));
	initialize(arr, dim);
	assignArray(arr, 114514);
	assignArray(arr, 10086);
	get_data(arr);
	get_data(arr);
	destroyArray(arr);
}

void initialize(array* arr, int dim)
{
	arr->dim = dim;
	int* bounds = (int*)malloc(sizeof(int) * dim);
	if (!bounds) exit(EXIT_FAILURE);
	for (int i = 2 * dim, j = 0; i > dim; i--, j++) bounds[j] = i;
	arr->bounds = bounds;
	int elemtotal = 1;
	for (int i = 0; i < dim; i++) elemtotal *= bounds[i];
	zhengshu* base = (zhengshu*)malloc(sizeof(zhengshu) * elemtotal);
	if (!base) exit(EXIT_FAILURE);
	for (int i = 0; i < elemtotal; i++) base[i] = 0;
	arr->base = base;
	int* constant = (int*)malloc(sizeof(int) * dim);
	if (!constant) exit(EXIT_FAILURE);
	int constant_value = 1;
	for (int i = dim - 1; i >= 0; i--)
	{
		constant[i] = constant_value;
		constant_value *= bounds[i];
	}
	arr->constant = constant;
	printf("Initialization complete!\n");
}

void destroyArray(array* arr)
{
	free(arr->base);
	free(arr->bounds);
	free(arr->constant);
	free(arr);
	printf("Array Deleted!\n");
}

void assignArray(array* arr, zhengshu a)
{
	int* pos = (int*)malloc(sizeof(int) * arr->dim);
	if (!pos) exit(EXIT_FAILURE);
	for (int i = 0; i < arr->dim; i++)
	{
		int coordinate;
		printf("Please input coordinate %d.\n", i + 1);		//这里还要有一个范围限制
		scanf_s("%d", &coordinate);
		pos[i] = coordinate;
	}
	int alterpos = 0;
	for (int i = 0; i < arr->dim; i++) alterpos = arr->constant[i] * pos[i];
	arr->base[alterpos] = a;
	free(pos);
}

void get_data(array* arr)
{
	zhengshu data;
	int coordinate;
	int* pos = (int*)malloc(sizeof(int) * arr->dim);
	if (!pos) exit(EXIT_FAILURE);
	for (int i = 0; i < arr->dim; i++)
	{
		printf("To get data, Please input coordinate %d.\n", i + 1);		//这里还要有一个范围限制
		scanf_s("%d", &coordinate);
		pos[i] = coordinate;
	}
	int alterpos = 0;
	for (int i = 0; i < arr->dim; i++) alterpos = arr->constant[i] * pos[i];
	data = arr->base[alterpos];
	printf("The data stored there is %d.\n", data);
	free(pos);
}