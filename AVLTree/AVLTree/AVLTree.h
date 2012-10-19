#ifndef _AVLTree_H
#define _AVLTree_H
#include<iostream>
#include<queue>
using namespace std;
typedef struct AVLNode *position;
typedef struct AVLNode *AVLTree;
struct AVLNode
{
	int data;//��ֵ
	AVLTree lchild;//����
	AVLTree rchild;//�Һ���
	int Height;//���ĸ߶�
};
position Find(int data,AVLTree T);
position FindMin(AVLTree T);
position FindMax(AVLTree T);
AVLTree Insert(int data,AVLTree);
AVLTree Create_Tree(AVLTree p);
void Level_order(AVLTree p);
#endif