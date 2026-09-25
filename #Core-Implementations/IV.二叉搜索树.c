#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct TreeNode {
	int key;
	int value;
	int size;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct TreeMap {
	TreeNode* root;
} TreeMap;

int main(int argc, const char* argv[]) {

}

TreeNode* createNode(int key, int val) {
	TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newnode) exit(EXIT_FAILURE);
	newnode->key = key;
	newnode->value = val;
	newnode->size = 1;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

TreeMap* initTreeMap() {
	TreeMap* map = (TreeMap*)malloc(sizeof(TreeMap));
	if (!map) exit(EXIT_FAILURE);
	map->root = NULL;
	return map;
}

int treeMapGetSize(TreeMap* map) {
	return map->root ? map->root->size : 0;
}

bool treeMapIsEmpty(TreeMap* map) {
	return treeMapGetSize(map) == 0;
}

TreeNode* _treeMapPut(TreeNode* root, int key, int value) {
	if (root == NULL) return createNode(key, value);
	else {
		if (root->key == key) root->value = value;
		else if (root->key > key) root->left = _treeMapPut(root->left, key, value);
		else root->right = _treeMapPut(root->right, key, value);
	
		root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
		return root;
	}
}

void treeMapPut(TreeMap* map, int key, int value) {
	map->root = _treeMapPut(map->root, key, value);
}

void _treeMapGet(TreeNode* root, int key, int* result, bool* found) {
	if (root == NULL) return;
	else {
		if (root->key == key) {
			*result = root->value;
			*found = true;
		}
		else if (root->key > key) _treeMapGet(root->left, key, result, found);
		else _treeMapGet(root->right, key, result, found);
	}
}

bool treeMapGet(TreeMap* map, int key, int* result) {
	bool found = false;
	_treeMapGet(map->root, key, result, &found);
	return found;
}

TreeNode* getMaxNode(TreeNode* p) {
	if (p == NULL) return NULL;
	while (p->right != NULL) p = p->right;
	return p;
}

TreeNode* getMinNode(TreeNode* p) {
	if (p == NULL) return NULL;
	while (p->left != NULL) p = p->left;
	return p;
}

TreeNode* removeMaxNode(TreeNode* root) {
	if (root == NULL) return NULL;
	if (root->right == NULL) {
		TreeNode* left = root->left;
		free(root);
		return left;
	}
	root->right = removeMaxNode(root->right);

	root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
	return root;
}

TreeNode* removeMinNode(TreeNode* root) {
	if (root == NULL) return NULL;
	if (root->left == NULL) {
		TreeNode* right = root->right;
		free(root);
		return right;
	}
	root->left = removeMinNode(root->left);

	root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
	return root;
}

TreeNode* _treeMapRemove(TreeNode* root, int key) {
	if (root == NULL) return NULL;
	else {
		if (root->key == key) {
			if (root->left == NULL) {
				TreeNode* right = root->right;
				free(root);
				return right;
			}
			if (root->right == NULL) {
				TreeNode* left = root->left;
				free(root);
				return left;
			}

			TreeNode* leftMax = getMaxNode(root->left);
			root->key = leftMax->key;
			root->value = leftMax->value;
			root->left = removeMaxNode(root->left);
		}
		else if (root->key > key) root->left = _treeMapRemove(root->left, key);
		else root->right = _treeMapRemove(root->right, key);

		root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
		return root;
	}
}

void treeMapRemove(TreeMap* map, int key) {
	map->root = _treeMapRemove(map->root, key);
}

bool treeMapContainsKey(TreeMap* map, int key) {
	int dummy;
	return treeMapGet(map, key, &dummy);
}

void _treeMapGetKeys(TreeNode* root, int* ret, int* p) {
	if (root == NULL) return;
	else {
		_treeMapGetKeys(root->left, ret, p);
		ret[(*p)++] = root->value;
		_treeMapGetKeys(root->right, ret, p);
	}
}

int* treeMapGetKeys(TreeMap* map, int* size) {
	*size = treeMapGetSize(map);
	int* ret = (int*)malloc(sizeof(int) * (*size));
	int p = 0;
	_treeMapGetKeys(map->root, ret, &p);
}

bool treeMapGetFirstKey(TreeMap* map, int* result) {
	TreeNode* minNode = getMinNode(map->root);
	if (!minNode) return false;
	else {
		*result = minNode->key;
		return true;
	}
}

bool treeMapGetLastKey(TreeMap* map, int* result) {
	TreeNode* maxNode = getMaxNode(map->root);
	if (!maxNode) return false;
	else {
		*result = maxNode->key;
		return true;
	}
}

TreeNode* _treeMapGetFloorKey(TreeNode* root, int key) {
	if (root == NULL) return NULL;
	else {
		if (root->key == key) return root;
		else if (root->key > key) return _treeMapGetFloorKey(root->left, key);
		else {
			TreeNode* temp = _treeMapGetFloorKey(root->right, key);
			if (!temp) return root;
			else return temp;
		}
	}
}

bool treeMapGetFloorKey(TreeMap* map, int key, int* result) {
	TreeNode* temp = _treeMapGetFloorKey(map->root, key);
	if (temp == NULL) return false;
	else {
		*result = temp->key;
		return true;
	}
}

TreeNode* _treeMapGetCeilingKey(TreeNode* root, int key) {
	if (root == NULL) return;
	else {
		if (root->key == key) return root;
		else if (root->key > key) {
			TreeNode* temp = _treeMapGetCeilingKey(root->left, key);
			if (!temp) return root;
			else return temp;
		}
		else return _treeMapGetCeilingKey(root->right, key);
	}
}

bool treeMapGetCeilingKey(TreeMap* map, int key, int* result) {
	TreeNode* temp = _treeMapGetCeilingKey(map->root, key);
	if (temp == NULL) return false;
	else {
		*result = temp->key;
		return true;
	}
}

TreeNode* _treeMapGetKeyAtRank(TreeNode* root, int rank) {

}

bool treeMapGetKeyAtRank(TreeMap* map, int rank, int* result) {

}

bool treeMapGetRankOfKey(TreeMap* map, int key, int* result) {

}

int* treeMapGetRangeKeys(TreeMap* map, int low, int high, int* size) {

}

void traverseArray(int* arr, int size) {

}

void deleteArray(int* arr) {

}

void deleteTreeMap(TreeMap* map) {

}