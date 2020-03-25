#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl; 
using std::stack;
#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED
typedef struct BiTNode
{
	char data;
	struct BiTNode * Lchild;
	struct BiTNode * Rchild;
}BiTNode,*BiTree;
typedef enum{Visit,Travel} TaskType; //���� �� ����
struct Node
{
	BiTree ptr;
	TaskType task;
};
void creatTree(BiTree &T)
{
	char ch;
	cin>>ch;
	if(ch=='#') T = nullptr;
	else
	{
		T = new BiTNode;
		T->data = ch;
		creatTree(T->Lchild);
		creatTree(T->Rchild);
	}
}
//������д��void�ĺô��Ǻ���ԭ�Ϳ���ͳһ�����ù���ʱ����Ժ���ָ��ʵ��
void PreOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	visit(T);
	PreOrder(T->Lchild,visit);
	PreOrder(T->Rchild,visit);
}
void InOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	if(T->Lchild&&T->Rchild)
		cout<<"("; 
	InOrder(T->Lchild,visit);
	visit(T);
	InOrder(T->Rchild,visit);
	if(T->Lchild&&T->Rchild)
		cout<<")";
}
void SubsequentOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	SubsequentOrder(T->Lchild,visit);
	SubsequentOrder(T->Rchild,visit);
	visit(T);
}
void visit(BiTree T)
{
	if(T)
		cout<<T->data;
}
void pre_order(BiTree T,void(*visit)(BiTree))
{
	/*if(!T)
	{
		cout<<"The Tree is empty!"<<endl;
		return;
	}*/
	stack<BiTree> S;
	BiTree p = T;
	while(p||!S.empty())
	{
		if(p) visit(p),S.push(p->Rchild),p = p->Lchild;
		else p = S.top(),S.pop();
	}
}
void in_order(BiTree T,void(*visit)(BiTree))
{
	stack<Node> S;
	if(T) S.push({T,Travel});
	TaskType task;
	BiTree p;
	while(!S.empty())
	{
		p = S.top().ptr;
		task = S.top().task;
		S.pop();
		if(task==Visit)
		{
			visit(p);
		}
		else      //(task==Travel)
		{
			if(p)
				S.push({p->Rchild,Travel}), //����е����� ����������
				S.push({p,Visit}),          //���ʸ��ڵ�
				S.push({p->Lchild,Travel}); //����������
		}
	}
}
void subsequent_order(BiTree T,void(*visit)(BiTree))
{
	stack<Node> S;
	if(T) S.push({T,Travel});
	TaskType task;
	BiTree p;
	while(!S.empty())
	{
		p = S.top().ptr;
		task = S.top().task;
		S.pop();
		if(task==Visit)
		{
			visit(p);
		}
		else      //(task==Travel)
		{
			if(p)
				S.push({p,Visit}),  //���ʸ��ڵ�
				S.push({p->Rchild,Travel}), //����е����� ����������
				S.push({p->Lchild,Travel}); //����������

		}
	}
}


#endif // BITREE_H_INCLUDED
