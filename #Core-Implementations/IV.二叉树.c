#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* createBinaryTree(int* valuesList, int listLength);
void preOrderTraversal(TreeNode* root);
void inOrderTraversal(TreeNode* root);
void postOrderTraversal(TreeNode* root);
void levelOrderTraversal(TreeNode* root, int sizeOfTree);
int numberOfNode(TreeNode* root);
int numberOfLeaf(TreeNode* root);
int minDepth(TreeNode* root, int sizeOfTree);
int maxDepth(TreeNode* root);
int findDiameter(TreeNode* root);
void deleteTree(TreeNode* root);

int main(int argc, const char* argv[]) {
	//测试用例
	int values[12] = { 1,2,3,4,5,INT_MIN,8,INT_MIN,INT_MIN,6,7,9 };
	int* valueList = (int*)malloc(sizeof(int) * 12);
	if (!valueList) exit(EXIT_FAILURE);
	memcpy(valueList, values, sizeof(int) * 12);
	TreeNode* root = createBinaryTree(valueList, 12);
	preOrderTraversal(root);
	printf("\n");
	inOrderTraversal(root);
	printf("\n");
	postOrderTraversal(root);
	printf("\n");
	levelOrderTraversal(root, numberOfNode(root));
	printf("\n");
	printf("Number of nodes: %d\n", numberOfNode(root));
	printf("Number of leaves: %d\n", numberOfLeaf(root));
	printf("Min depth: %d\n", minDepth(root, numberOfNode(root)));
	printf("Max depth: %d\n", maxDepth(root));
	printf("Diameter: %d\n", findDiameter(root));
	deleteTree(root);
}

TreeNode* createTreeNode(int val) {
	TreeNode* tree = (TreeNode*)malloc(sizeof(TreeNode));
	if (!tree) exit(EXIT_FAILURE);
	tree->val = val;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

TreeNode* createBinaryTree(int* valuesList, int listLength) {
	if (!valuesList || listLength < 1 || valuesList[0] == INT_MIN) return NULL;

	TreeNode** queue = (TreeNode**)calloc(listLength, sizeof(TreeNode*));
	if (!queue) exit(EXIT_FAILURE);

	int rear = 0, front = 0;
	queue[rear++] = createTreeNode(valuesList[0]);
	int p = 1;

	while (p < listLength && front < rear) {
		TreeNode* cur = queue[front++];

		if (p < listLength) {
			if (valuesList[p] != INT_MIN) {
				cur->left = createTreeNode(valuesList[p]);
				queue[rear++] = cur->left;
			}
			p++;
		}

		if (p < listLength) {
			if (valuesList[p] != INT_MIN) {
				cur->right = createTreeNode(valuesList[p]);
				queue[rear++] = cur->right;
			}
			p++;
		}
	}

	TreeNode* root = queue[0];
	free(queue);
	return root;
}

void preOrderTraversal(TreeNode* root) {
	if (root == NULL) return;
	else {
		printf("%d\t", root->val);
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

void inOrderTraversal(TreeNode* root) {
	if (root == NULL) return;
	else {
		inOrderTraversal(root->left);
		printf("%d\t", root->val);
		inOrderTraversal(root->right);
	}
}

void postOrderTraversal(TreeNode* root) {
	if (root == NULL) return;
	else {
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		printf("%d\t", root->val);
	}
}

void levelOrderTraversal(TreeNode* root, int sizeOfTree) {
	int rear = 0, front = 0;
	TreeNode** queue = (TreeNode**)malloc(sizeof(TreeNode*) * sizeOfTree);
	if (!queue) exit(EXIT_FAILURE);
	queue[rear++] = root;
	while (front < rear) {
		int size = rear - front;
		for (int i = 0; i < size; i++) {
			TreeNode* cur = queue[front++];
			if (cur->left != NULL) queue[rear++] = cur->left;
			if (cur->right != NULL) queue[rear++] = cur->right;
		}
	}
	for (int i = 0; i < sizeOfTree; i++) printf("%d\t", queue[i]->val);
	free(queue);
}

int numberOfNode(TreeNode* root) {
	if (root == NULL) return 0;
	else {
		int left = numberOfNode(root->left);
		int right = numberOfNode(root->right);
		return 1 + left + right;
	}
}

int numberOfLeaf(TreeNode* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	else {
		int leftLeaf = numberOfLeaf(root->left);
		int rightLeaf = numberOfLeaf(root->right);
		return leftLeaf + rightLeaf;
	}
}

int minDepth(TreeNode* root, int sizeOfTree) {
	if (root == NULL) return 0;
	int rear = 0, front = 0, depth = 0;
	TreeNode** queue = (TreeNode**)malloc(sizeof(TreeNode*) * sizeOfTree);
	if (!queue) exit(EXIT_FAILURE);
	queue[rear++] = root;

	while (front < rear) {
		int size = rear - front;
		depth++;
		for (int i = 0; i < size; i++) {
			TreeNode* cur = queue[front++];
			if (cur->left == NULL && cur->right == NULL) {
				free(queue);
				return depth;
			}
			if (cur->left != NULL) queue[rear++] = cur->left;
			if (cur->right != NULL) queue[rear++] = cur->right;
		}
	}
	free(queue);
	return depth;
}

int maxDepth(TreeNode* root) {
	if (root == NULL) return 0;
	else {
		int leftMax = maxDepth(root->left);
		int rightMax = maxDepth(root->right);
		return 1 + (leftMax > rightMax ? leftMax : rightMax);
	}
}

int findPath(TreeNode* root, int* maxLength) {
	if (root == NULL) return 0;
	else {
		int leftPath = findPath(root->left, maxLength);
		int rightPath = findPath(root->right, maxLength);
		if (leftPath + rightPath > *maxLength) *maxLength = leftPath + rightPath;
		return 1 + (leftPath > rightPath ? leftPath : rightPath);
	}
}

int findDiameter(TreeNode* root) {
	int maxLength = 0;
	findPath(root, &maxLength);
	return maxLength;
}

void deleteTree(TreeNode* root) {
	if (root == NULL) return;
	else {
		deleteTree(root->left);
		deleteTree(root->right);
		free(root);
	}
}