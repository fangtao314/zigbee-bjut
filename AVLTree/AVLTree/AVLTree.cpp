#include"AVLTree.h"
static int Max(int a,int b)
{
	if(a<b)
		return b;
	else 
		return a;
}
static int Height(position p)//返回高度
{
	if(p==NULL)
		return -1;
	else
		return p->Height;
}
/*规定当左子树高于右子树大于等于2时我们需要旋转称之为Right旋转
反之右子树高于左子树时我称之为left旋转*/
static position SingleRotateRight(position k2)
{
	//左子树大于右子树
	position k1;
	k1=k2->lchild;//k1为k2的左孩子
	k2->lchild=k1->rchild;//把k1的右子树赋给k2的左孩子，则此时k2与k1断开
	k1->rchild=k2;//k2赋给k1的右孩子
	k2->Height=Max(Height(k2->lchild),Height(k2->rchild))+1;
	k1->Height=Max(Height(k1->lchild),k2->Height)+1;
	return k1;
}
static position SingleRotateLeft(position k2)
{
	//右子树大于左子树
	position k1;
	k1=k2->rchild;
	k2->rchild=k1->lchild;
	k1->lchild=k2;
	k2->Height=Max(Height(k2->lchild),Height(k2->rchild))+1;
	k1->Height=Max(Height(k1->rchild),k2->Height)+1;
	return k1;
}
static position DoubleRotateRight_Left(position k3)
{//双旋转
	//先右后左
	k3->rchild=SingleRotateRight(k3->rchild);
	return SingleRotateLeft(k3);
}
static position DoubleRotateLeft_Right(position k3)
{
	//先左后右
	k3->lchild=SingleRotateLeft(k3->lchild);
	return SingleRotateRight(k3);
}
position Find(int data,AVLTree T)//查找
{
	if(T==NULL)
		return NULL;
	else if(T->data<data)
		return Find(data,T->lchild);
	else if(T->data>data)
		return Find(data,T->rchild);
	else 
		return T;
}
position FindMin(AVLTree T)//递归查找最小
{
	if(T==NULL)
		return NULL;
	else if(T->lchild)
		return FindMin(T->lchild);
	else
		return T;
}
position FindMax(AVLTree T)//非递归查找最大
{
	position p;
	while(T)
	{
		p=T;
		T=T->rchild;
	}
	return p;
}
AVLTree Insert(int data,AVLTree T)//递归插入
{
	if(T==NULL)
	{
		T=(AVLTree)malloc(sizeof(struct AVLNode));
		T->data=data;
		T->Height=0;
		T->lchild=T->rchild=NULL;
	}
	else if(data<T->data)//插入左子树
	{
		T->lchild=Insert(data,T->lchild);
		if(Height(T->lchild)-Height(T->rchild)==2)
		{
			if(data<T->lchild->data)//表明data不在T和T->lchild之间，故单旋转就能解决.否则需要双旋转
				T=SingleRotateRight(T);
			else
				T=DoubleRotateLeft_Right(T);
		}
	}
	else if(data>T->data)
	{
		T->rchild=Insert(data,T->rchild);
		if(Height(T->rchild)-Height(T->lchild)==2)
		{
			if(data>T->rchild->data)//表明data不在T和T->rchild之间，故单旋转就能解决.否则需要双旋转
				T=SingleRotateLeft(T);
			else
				T=DoubleRotateRight_Left(T);
		}
	}
	/*else data is in the tree already,we'll do nothing*/
	T->Height=Max(Height(T->lchild),Height(T->rchild))+1;
	return T;
}
AVLTree Create_Tree(AVLTree p)//递归建树
	{
		cout<<"输入平衡二叉树(AVL树)的元素,输入-1代表结束输入：";  
        int num[20];  
        int a,i=0;  
        while(cin>>a && a!=-1)  
        {  
            num[i]=a;  
            i++;  
        }  
          
        if(num[0]==-1)  
        {  
            cout<<"AVL树为空"<<endl;  
            return NULL;  
        }  
		int k=i; 
		for(i=0;i<k;i++)  
            p=Insert(num[i],p);  
        cout<<"____建树完成____"<<endl;
		return p;
	}
void Level_order(AVLTree p)
{//层次遍历
	queue<AVLTree> q;
	AVLNode *s;
	if(p!=NULL)
		q.push(p);
	else
	{
		cout<<"树为空"<<endl;
		return;
	}
	while(!q.empty())
	{
		s=q.front();
		q.pop();
		cout<<s->data<<" ";
		if(s->lchild)
			q.push(s->lchild);
		if(s->rchild)
			q.push(s->rchild);
	}
}