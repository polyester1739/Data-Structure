#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* NULL_SIGN = "#";
const char* SEP_SIGN = ",";
const int BUFFER_SIZE = 12;
const int TOKEN_COUNT = 100;
const int STRING_BUILDER_SIZE = 1000;
const int ARRAY_PAIR_SIZE = 2;

typedef struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* createTreeNode(int val);
char* preOrderSerialize(TreeNode* root);
TreeNode* preOrderDeserialize(char* data);
char* postOrderSerialize(TreeNode* root);
TreeNode* postOrderDeserialize(char* data);
int** preOrderInOrderSerialize(TreeNode* root, int* returnSize, int** returnColumnSizes);
TreeNode* preOrderInOrderDeserialize(int** data, int* dataSize, int** dataColSizes);
int** inOrderPostOrderSerialize(TreeNode* root, int* returnSize, int** returnColumnSizes);
TreeNode* inOrderPostOrderDeserialize(int** data, int* dataSize, int** dataColSizes);
void inOrderPrint(const TreeNode* root);
void stringPrint(const char* str);
void matrixPrint(int** matrix, int matrixSize, int* matrixColSizes);
void deleteTree(TreeNode* root);
void deleteString(char* str);
void deleteMatrix(int** matrix, int matrixSize);

int main(int argc, const char* argv[]) {
	char* serialized_1 = "1,2,#,#,3,4,#,#,5,#,#,";
	char* serialized_2 = "#,#,6,#,#,7,#,#,8,9,10,";

	TreeNode* root_1 = preOrderDeserialize(serialized_1);
	printf("Deserialized tree_1 (in-order): ");
	inOrderPrint(root_1);
	TreeNode* root_2 = postOrderDeserialize(serialized_2);
	printf("Deserialized tree_2 (in-order): ");
	inOrderPrint(root_2);

	char* string_1 = preOrderSerialize(root_1);
	printf("Serialized tree_1: ");
	stringPrint(string_1);
	char* string_2 = postOrderSerialize(root_2);
	printf("Serialized tree_2: ");
	stringPrint(string_2);

	deleteString(string_1);
	deleteString(string_2);
	deleteTree(root_1);
	deleteTree(root_2);

	char* serialized_3 = "21,22,24,#,#,25,26,#,#,27,#,#,23,#,28,29,#,#,#,";
	TreeNode* root_3 = preOrderDeserialize(serialized_3);

	int dataSize_3_1;
	int* dataColSizes_3_1;
	int** data_3_1 = preOrderInOrderSerialize(root_3, &dataSize_3_1, &dataColSizes_3_1);
	printf("Pre-order and In-order traversal results:\n");
	matrixPrint(data_3_1, dataSize_3_1, dataColSizes_3_1);
	int dataSize_3_2;
	int* dataColSizes_3_2;
	int** data_3_2 = inOrderPostOrderSerialize(root_3, &dataSize_3_2, &dataColSizes_3_2);
	printf("In-order and Post-order traversal results:\n");
	matrixPrint(data_3_2, dataSize_3_2, dataColSizes_3_2);

	TreeNode* root_3_1 = preOrderInOrderDeserialize(data_3_1, &dataSize_3_1, &dataColSizes_3_1);
	printf("Deserialized tree_3_1 (in-order): ");
	inOrderPrint(root_3_1);
	TreeNode* root_3_2 = inOrderPostOrderDeserialize(data_3_2, &dataSize_3_2, &dataColSizes_3_2);
	printf("Deserialized tree_3_2 (in-order): ");
	inOrderPrint(root_3_2);

	deleteMatrix(data_3_1, dataSize_3_1);
	free(dataColSizes_3_1);
	deleteTree(root_3_1);
	deleteMatrix(data_3_2, dataSize_3_2);
	free(dataColSizes_3_2);
	deleteTree(root_3_2);
	deleteTree(root_3);
	return 0;
}

/* 构造节点 */

TreeNode* createTreeNode(int val) {
	TreeNode* treeNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!treeNode) exit(EXIT_FAILURE);
	treeNode->val = val;
	treeNode->left = NULL;
	treeNode->right = NULL;
	return treeNode;
}

/* 遍历函数 */

void preOrderTraversal(TreeNode* root, int* ret, int* returnSize) {
	if (root == NULL) return;
	else {
		ret[(*returnSize)++] = root->val;
		preOrderTraversal(root->left, ret, returnSize);
		preOrderTraversal(root->right, ret, returnSize);
	}
}

void inOrderTraversal(TreeNode* root, int* ret, int* returnSize) {
	if (root == NULL) return;
	else {
		inOrderTraversal(root->left, ret, returnSize);
		ret[(*returnSize)++] = root->val;
		inOrderTraversal(root->right, ret, returnSize);
	}
}

void postOrderTraversal(TreeNode* root, int* ret, int* returnSize) {
	if (root == NULL) return;
	else {
		postOrderTraversal(root->left, ret, returnSize);
		postOrderTraversal(root->right, ret, returnSize);
		ret[(*returnSize)++] = root->val;
	}
}

/* 前序遍历序列化 */

void _preOrderSerialize(TreeNode* root, char* stringBuilder) {
	if (root == NULL) {
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, NULL_SIGN);
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, SEP_SIGN);
	}
	else {
		char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer) exit(EXIT_FAILURE);
		buffer[0] = '\0';
		sprintf_s(buffer, BUFFER_SIZE, "%d", root->val);
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, buffer);
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, SEP_SIGN);
		free(buffer);

		_preOrderSerialize(root->left, stringBuilder);
		_preOrderSerialize(root->right, stringBuilder);
	}
}

char* preOrderSerialize(TreeNode* root) {
	char* stringBuilder = (char*)malloc(sizeof(char) * STRING_BUILDER_SIZE);
	if (!stringBuilder) exit(EXIT_FAILURE);
	stringBuilder[0] = '\0';
	_preOrderSerialize(root, stringBuilder);
	return stringBuilder;
}

TreeNode* _preOrderDeserialize(char** nodes, int* p, int nodeCount) {
	if (*p >= nodeCount) return NULL;
	else {
		char* cur = nodes[(*p)++];
		if (strcmp(cur, NULL_SIGN) == 0) return NULL;
		else {
			int value = atoi(cur);
			TreeNode* newnode = createTreeNode(value);
			newnode->left = _preOrderDeserialize(nodes, p, nodeCount);
			newnode->right = _preOrderDeserialize(nodes, p, nodeCount);
			return newnode;
		}
	}

}

TreeNode* preOrderDeserialize(char* data) {
	char* copy = _strdup(data);
	if (!copy) exit(EXIT_FAILURE);
	char** nodes = (char**)malloc(sizeof(char*) * TOKEN_COUNT);
	if (!nodes) exit(EXIT_FAILURE);
	int nodeCount = 0;

	char* context = NULL;
	char* token = strtok_s(copy, SEP_SIGN, &context);
	while (token != NULL) {
		nodes[nodeCount++] = token;
		token = strtok_s(NULL, SEP_SIGN, &context);
	}

	int p = 0;
	TreeNode* root = _preOrderDeserialize(nodes, &p, nodeCount);

	free(nodes);
	free(copy);
	return root;
}

/* 后序遍历序列化 */

void _postOrderSerialize(TreeNode* root, char* stringBuilder) {
	if (root == NULL) {
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, NULL_SIGN);
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, SEP_SIGN);
	}
	else {
		_postOrderSerialize(root->left, stringBuilder);
		_postOrderSerialize(root->right, stringBuilder);

		char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer) exit(EXIT_FAILURE);
		buffer[0] = '\0';
		sprintf_s(buffer, BUFFER_SIZE, "%d", root->val);
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, buffer);
		strcat_s(stringBuilder, STRING_BUILDER_SIZE, SEP_SIGN);
		free(buffer);
	}
}

char* postOrderSerialize(TreeNode* root) {
	char* stringBuilder = (char*)malloc(sizeof(char) * STRING_BUILDER_SIZE);
	if (!stringBuilder) exit(EXIT_FAILURE);
	stringBuilder[0] = '\0';
	_postOrderSerialize(root, stringBuilder);
	return stringBuilder;
}

TreeNode* _postOrderDeserialize(char** nodes, int* p) {
	if (*p < 0) return NULL;
	else {
		char* cur = nodes[(*p)--];
		if (strcmp(cur, NULL_SIGN) == 0) return NULL;
		else {
			int value = atoi(cur);
			TreeNode* newnode = createTreeNode(value);
			newnode->right = _postOrderDeserialize(nodes, p);
			newnode->left = _postOrderDeserialize(nodes, p);
			return newnode;
		}
	}
}

TreeNode* postOrderDeserialize(char* data) {
	char* copy = _strdup(data);
	if (!copy) exit(EXIT_FAILURE);
	char** nodes = (char**)malloc(sizeof(char*) * TOKEN_COUNT);
	if (!nodes) exit(EXIT_FAILURE);
	int nodeCount = 0;

	char* context = NULL;
	char* token = strtok_s(copy, SEP_SIGN, &context);
	while (token != NULL) {
		nodes[nodeCount++] = token;
		token = strtok_s(NULL, SEP_SIGN, &context);
	}

	int p = nodeCount - 1;
	TreeNode* root = _postOrderDeserialize(nodes, &p);

	free(nodes);
	free(copy);
	return root;
}

/* 前序和中序遍历序列化 */
/* 仅可在元素不重复且只包含非负整数的情况下使用,元素大小应当严格小于1000 */

int** preOrderInOrderSerialize(TreeNode* root, int* returnSize, int** returnColumnSizes) {
	int** ret = (int**)malloc(sizeof(int*) * ARRAY_PAIR_SIZE);
	if (!ret) exit(EXIT_FAILURE);
	*returnSize = ARRAY_PAIR_SIZE;
	*returnColumnSizes = (int*)malloc(sizeof(int) * ARRAY_PAIR_SIZE);
	if (!(*returnColumnSizes)) exit(EXIT_FAILURE);

	int p = 0;
	int* preOrder = (int*)malloc(sizeof(int) * STRING_BUILDER_SIZE);
	if (!preOrder) exit(EXIT_FAILURE);
	preOrderTraversal(root, preOrder, &p);
	ret[0] = preOrder;
	(*returnColumnSizes)[0] = p;
	
	p = 0;
	int* inOrder = (int*)malloc(sizeof(int) * STRING_BUILDER_SIZE);
	if (!inOrder) exit(EXIT_FAILURE);
	inOrderTraversal(root, inOrder, &p);
	ret[1] = inOrder;
	(*returnColumnSizes)[1] = p;

	return ret;
}

TreeNode* _preOrderInOrderDeserialize(int* preOrder, int preStart, int* inOrder, int inStart, int inEnd, int* valToIndex) {
	if (inStart > inEnd) return NULL;
	else {
		int index = valToIndex[preOrder[preStart]];
		TreeNode* newnode = createTreeNode(preOrder[preStart]);
		newnode->left = _preOrderInOrderDeserialize(preOrder, preStart + 1, inOrder, inStart, index - 1, valToIndex);
		newnode->right = _preOrderInOrderDeserialize(preOrder, preStart + (index - inStart) + 1, inOrder, index + 1, inEnd, valToIndex);
		return newnode;
	}
}

TreeNode* preOrderInOrderDeserialize(int** data, int* dataSize, int** dataColSizes) {
	int* valToIndex = (int*)malloc(sizeof(int) * STRING_BUILDER_SIZE);
	if (!valToIndex) exit(EXIT_FAILURE);
	for (int i = 0; i < (*dataColSizes)[1]; i++) valToIndex[data[1][i]] = i;
	TreeNode* root = _preOrderInOrderDeserialize(data[0], 0, data[1], 0, (*dataColSizes)[1] - 1, valToIndex);
	free(valToIndex);
	return root;
}

/* 中序和后序遍历序列化 */
/* 仅可在元素不重复且只包含非负整数的情况下使用,元素大小应当严格小于1000 */


int** inOrderPostOrderSerialize(TreeNode* root, int* returnSize, int** returnColumnSizes) {
	int** ret = (int**)malloc(sizeof(int*) * ARRAY_PAIR_SIZE);
	if (!ret) exit(EXIT_FAILURE);
	*returnSize = ARRAY_PAIR_SIZE;
	*returnColumnSizes = (int*)malloc(sizeof(int) * ARRAY_PAIR_SIZE);
	if (!(*returnColumnSizes)) exit(EXIT_FAILURE);

	int p = 0;
	int* inOrder = (int*)malloc(sizeof(int) * STRING_BUILDER_SIZE);
	if (!inOrder) exit(EXIT_FAILURE);
	inOrderTraversal(root, inOrder, &p);
	ret[0] = inOrder;
	(*returnColumnSizes)[0] = p;

	p = 0;
	int* postOrder = (int*)malloc(sizeof(int) * STRING_BUILDER_SIZE);
	if (!postOrder) exit(EXIT_FAILURE);
	postOrderTraversal(root, postOrder, &p);
	ret[1] = postOrder;
	(*returnColumnSizes)[1] = p;

	return ret;
}

TreeNode* _inOrderPostDeserialize(int* postOrder, int postEnd, int* inOrder, int inStart, int inEnd, int* valToIndex) {
	if (inStart > inEnd) return NULL;
	else {
		int index = valToIndex[postOrder[postEnd]];
		TreeNode* newnode = createTreeNode(postOrder[postEnd]);
		newnode->left = _inOrderPostDeserialize(postOrder, postEnd - (inEnd - index) - 1, inOrder, inStart, index - 1, valToIndex);
		newnode->right = _inOrderPostDeserialize(postOrder, postEnd - 1, inOrder, index + 1, inEnd, valToIndex);
		return newnode;
	}
}

TreeNode* inOrderPostOrderDeserialize(int** data, int* dataSize, int** dataColSizes) {
	int* valToIndex = (int*)malloc(sizeof(int) * STRING_BUILDER_SIZE);
	if (!valToIndex) exit(EXIT_FAILURE);
	for (int i = 0; i < (*dataColSizes)[0]; i++) valToIndex[data[0][i]] = i;
	TreeNode* root = _inOrderPostDeserialize(data[1], (*dataColSizes)[1] - 1, data[0], 0, (*dataColSizes)[0] - 1, valToIndex);
	free(valToIndex);
	return root;
}

/* 辅助函数 */

void _inOrderPrint(const TreeNode* root) {
	if (root == NULL) return;
	else {
		_inOrderPrint(root->left);
		printf("%d,", root->val);
		_inOrderPrint(root->right);
	}
}

void inOrderPrint(const TreeNode* root) {
	_inOrderPrint(root);
	printf("\n");
}

void stringPrint(const char* str) {
	int p = 0;
	while (str[p] != '\0') {
		printf("%c", str[p]);
		p++;
	}
	printf("\n");
}

void matrixPrint(int** matrix, int matrixSize, int* matrixColSizes) {
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixColSizes[i]; j++) {
			printf("%d,", matrix[i][j]);
		}
		printf("\n");
	}
}

void deleteTree(TreeNode* root) {
	if (root == NULL) return;
	else {
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}
}

void deleteString(char* str) {
	free(str);
}

void deleteMatrix(int** matrix, int matrixSize) {
	for (int i = 0; i < matrixSize; i++) free(matrix[i]);
	free(matrix);
}