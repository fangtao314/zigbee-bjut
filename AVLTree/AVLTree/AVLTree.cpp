#include"AVLTree.h"
static int Max(int a,int b)
{
	if(a<b)
		return b;
	else 
		return a;
}
static int Height(position p)//���ظ߶�
{
	if(p==NULL)
		return -1;
	else
		return p->Height;
}
/*�涨���������������������ڵ���2ʱ������Ҫ��ת��֮ΪRight��ת
��֮����������������ʱ�ҳ�֮Ϊleft��ת*/
static position SingleRotateRight(position k2)
{
	//����������������
	position k1;
	k1=k2->lchild;//k1Ϊk2������
	k2->lchild=k1->rchild;//��k1������������k2�����ӣ����ʱk2��k1�Ͽ�
	k1->rchild=k2;//k2����k1���Һ���
	k2->Height=Max(Height(k2->lchild),Height(k2->rchild))+1;
	k1->Height=Max(Height(k1->lchild),k2->Height)+1;
	return k1;
}
static position SingleRotateLeft(position k2)
{
	//����������������
	position k1;
	k1=k2->rchild;
	k2->rchild=k1->lchild;
	k1->lchild=k2;
	k2->Height=Max(Height(k2->lchild),Height(k2->rchild))+1;
	k1->Height=Max(Height(k1->rchild),k2->Height)+1;
	return k1;
}
static position DoubleRotateRight_Left(position k3)
{//˫��ת
	//���Һ���
	k3->rchild=SingleRotateRight(k3->rchild);
	return SingleRotateLeft(k3);
}
static position DoubleRotateLeft_Right(position k3)
{
	//�������
	k3->lchild=SingleRotateLeft(k3->lchild);
	return SingleRotateRight(k3);
}
position Find(int data,AVLTree T)//����
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
position FindMin(AVLTree T)//�ݹ������С
{
	if(T==NULL)
		return NULL;
	else if(T->lchild)
		return FindMin(T->lchild);
	else
		return T;
}
position FindMax(AVLTree T)//�ǵݹ�������
{
	position p;
	while(T)
	{
		p=T;
		T=T->rchild;
	}
	return p;
}
AVLTree Insert(int data,AVLTree T)//�ݹ����
{
	if(T==NULL)
	{
		T=(AVLTree)malloc(sizeof(struct AVLNode));
		T->data=data;
		T->Height=0;
		T->lchild=T->rchild=NULL;
	}
	else if(data<T->data)//����������
	{
		T->lchild=Insert(data,T->lchild);
		if(Height(T->lchild)-Height(T->rchild)==2)
		{
			if(data<T->lchild->data)//����data����T��T->lchild֮�䣬�ʵ���ת���ܽ��.������Ҫ˫��ת
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
			if(data>T->rchild->data)//����data����T��T->rchild֮�䣬�ʵ���ת���ܽ��.������Ҫ˫��ת
				T=SingleRotateLeft(T);
			else
				T=DoubleRotateRight_Left(T);
		}
	}
	/*else data is in the tree already,we'll do nothing*/
	T->Height=Max(Height(T->lchild),Height(T->rchild))+1;
	return T;
}
AVLTree Create_Tree(AVLTree p)//�ݹ齨��
	{
		cout<<"����ƽ�������(AVL��)��Ԫ��,����-1����������룺";  
        int num[20];  
        int a,i=0;  
        while(cin>>a && a!=-1)  
        {  
            num[i]=a;  
            i++;  
        }  
          
        if(num[0]==-1)  
        {  
            cout<<"AVL��Ϊ��"<<endl;  
            return NULL;  
        }  
		int k=i; 
		for(i=0;i<k;i++)  
            p=Insert(num[i],p);  
        cout<<"____�������____"<<endl;
		return p;
	}
void Level_order(AVLTree p)
{//��α���
	queue<AVLTree> q;
	AVLNode *s;
	if(p!=NULL)
		q.push(p);
	else
	{
		cout<<"��Ϊ��"<<endl;
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