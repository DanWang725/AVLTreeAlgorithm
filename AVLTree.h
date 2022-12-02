#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define STR_MAX 1000
typedef struct avlTree{
	struct avlTree* left;
	struct avlTree* right;
	int * value;
	int height;
}AVLTreeNode;

int BalanceFactor(AVLTreeNode * node);
void Balance(AVLTreeNode * head);
void InsertNode(AVLTreeNode* parent, AVLTreeNode * newNode);
int Height(AVLTreeNode * node);
void AdjustHeight(AVLTreeNode* node);
void LLRotation(AVLTreeNode * node);
void RRRotation(AVLTreeNode * node);
void LRRotation(AVLTreeNode * node);
void RLRotation(AVLTreeNode * node);
AVLTreeNode* InitializeNewNode();
void printTreeInorder(AVLTreeNode * tree);
void printTreeInorderOnlyAt(AVLTreeNode* tree, int depth);
void printTreeInorderPretty(AVLTreeNode* tree);

