#include <stdio.h>
#include "AVLTree.h"

int main() {
	FILE* file = fopen("f.dat", "r");
	int heapList[20];
	char* inputString = malloc(sizeof(char)*STR_MAX);
	AVLTreeNode* head = NULL;
	int lineCounter = 0;

	if(file == NULL){
		printf("Error! File does not exist!\n");
		return 0;
	}

	//reading the file
	while(!feof(file)){
		if(fgets(inputString, STR_MAX, file) != NULL){
			int counter = 0;
			if(inputString[strlen(inputString)-1] == '\n'){
				inputString[strlen(inputString)-1] = '\0';
			}

			heapList[lineCounter] = (int)atol(inputString);
		}
		lineCounter++;
	}
	fclose(file);

	head = InitializeNewNode(heapList[0]);
	for(int i = 1; i<lineCounter-1; i++){
		AVLTreeNode * tmp = InitializeNewNode(heapList[i]);
		InsertNode(head, tmp);
	}

	printTreeInorderPretty(head);
}


int BalanceFactor(AVLTreeNode * node){
	int leftHeight = -1;
	int rightHeight = -1;
	if(node == NULL){
		return 0;
	}
	if(node->left != NULL){
		leftHeight = node->left->height;
	}
	if(node->right != NULL){
		rightHeight = node->right->height;
	}
	return leftHeight-rightHeight;
}

void Balance(AVLTreeNode *head) {
	AdjustHeight(head);
	int test = BalanceFactor(head);
	if(abs(BalanceFactor(head)) > 1){
		if(BalanceFactor(head) > 0){
			if(BalanceFactor(head->left) > 0){
				LLRotation(head);
			} else {
				LRRotation(head);
			}
		}else {
			if(BalanceFactor(head->right) < 0){
				RRRotation(head);
			} else {
				RLRotation(head);
			}
		}
	}
}

void InsertNode(AVLTreeNode *parent, AVLTreeNode *newNode) {
	int diff = *(parent->value) - *(newNode -> value);
	if(diff == 0){
		printf("duplicate keys");
	} else if(diff > 0){
		if(parent->left != NULL){
			InsertNode(parent->left, newNode);
		} else {
			parent->left = newNode;
		}
		Balance(parent->left);
	} else {
		if(parent->right != NULL){
			InsertNode(parent->right, newNode);
		} else {
			parent->right = newNode;
		}
		Balance(parent->right);
	}
	Balance(parent);
}

void AdjustHeight(AVLTreeNode *node) {
	int leftHeight = -1;
	int rightHeight = -1;
	int height = -1;
	if(node->left != NULL){
		leftHeight = node->left->height;
	}
	if(node->right != NULL){
		leftHeight = node->right->height;
	}
	height = (leftHeight > rightHeight) ? leftHeight : rightHeight;
	height++;
	node->height = height;
}

void LLRotation(AVLTreeNode *node) {
	AVLTreeNode * tmp = node->right;
	AVLTreeNode * tempNewRight = node->left;

	node->right = tempNewRight;
	node->left = tempNewRight->left;

	tempNewRight->left = tempNewRight->right;
	tempNewRight->right = tmp;

	int* tmpKey = node->value;
	node->value = tempNewRight->value;
	tempNewRight->value = tmpKey;
	AdjustHeight(tempNewRight);
	AdjustHeight(node);

}

void RRRotation(AVLTreeNode *node) {
	AVLTreeNode * tmp = node->left;
	AVLTreeNode * tempNewLeft = node->right;

	node->left = tempNewLeft;
	node->right = tempNewLeft->right;

	tempNewLeft->right = tempNewLeft->left;
	tempNewLeft->left = tmp;

	int* tmpKey = node->value;
	node->value = tempNewLeft->value;
	tempNewLeft->value = tmpKey;
	AdjustHeight(tempNewLeft);
	AdjustHeight(node);
}

void LRRotation(AVLTreeNode *node) {
	RRRotation(node->left);
	LLRotation(node);
}

void RLRotation(AVLTreeNode *node) {
	LLRotation(node->right);
	RRRotation(node);
}

AVLTreeNode *InitializeNewNode(int key) {
	AVLTreeNode * newTmp = malloc(sizeof(AVLTreeNode));
	newTmp->left = NULL;
	newTmp->right = NULL;
	newTmp->height = -1;
	newTmp->value = malloc(sizeof(int));
	*(newTmp->value) = key;
	return newTmp;
}

/**
 * prints an expression tree inorder, includes parenthesis
 * @param tree
 * @param map
 */
void printTreeInorder(AVLTreeNode* tree){
	if(tree->left != NULL){
		printTreeInorder(tree->left);
	}
	printf(" %d", *(tree->value));
	if(tree->right != NULL){
		printTreeInorder(tree->right);
	}
}

void printTreeInorderPretty(AVLTreeNode* tree){
	for(int i = tree->height; i >= 0; i--){
		printTreeInorderOnlyAt(tree, i);
		printf("\n");
	}
}
void printTreeInorderOnlyAt(AVLTreeNode* tree, int depth){
	if(tree->left != NULL){
		printTreeInorderOnlyAt(tree->left, depth);
	}
	if(tree->height == depth){
		printf(" %4d", *(tree->value));
	} else {
		printf("     ");
	}

	if(tree->right != NULL){
		printTreeInorderOnlyAt(tree->right,depth);
	}
}

