#ifndef _AVLTree_H
#define _AVLTree_H
#include<iostream>
#include<queue>
using namespace std;
typedef struct AVLNode *position;
typedef struct AVLNode *AVLTree;
struct AVLNode
{
	int data;//数值
	AVLTree lchild;//左孩子
	AVLTree rchild;//右孩子
	int Height;//树的高度
};
position Find(int data,AVLTree T);
position FindMin(AVLTree T);
position FindMax(AVLTree T);
AVLTree Insert(int data,AVLTree);
AVLTree Create_Tree(AVLTree p);
void Level_order(AVLTree p);
#endif