#include <stdio.h>
#include <stdlib.h>

typedef struct elemDescription
{
	int row;
	int col;
	int data;
	struct elemDescription* right;
	struct elemDescription* down;
}mat;

int main(int argc, const char* argv[])
{
	
}

mat* initmat(int row, int col)
{
	mat* headnode = (mat*)malloc(sizeof(mat));
	if (!headnode) exit(EXIT_FAILURE);
	headnode->row = row;
	headnode->col = col;
	headnode->data = 0;
	headnode->right = NULL;
	headnode->down = NULL;
	for (int i = 0; i < row; i++)
	{
		mat* newrownode = (mat*)malloc(sizeof(mat));
		if (!newrownode) exit(EXIT_FAILURE);
		newrownode->row = row - 1 - i;
		newrownode->right = NULL;
		newrownode->down = headnode->down;
		headnode->down = newrownode;
	}
	for (int i = 0; i < col; i++)
	{
		mat* newcolnode = (mat*)malloc(sizeof(mat));
		if (!newcolnode) exit(EXIT_FAILURE);
		newcolnode->col = col - 1 - i;
		newcolnode->down = NULL;
		newcolnode->right = headnode->right;
		headnode->right = newcolnode;
	}
	return headnode;
}

void appendElem(mat* m, int row, int col, int data)
{

}