
#include "Stacklnk.h"
using namespace std;
void InitStack( struct Stack &S, int maxNumber ) 
{
	S.top = NULL;
	S.Size = 0; 
}

void DestroyStack( struct Stack &S )	
{
	StackNode * p = S.top;
	while(S.top)
	{
		S.top = S.top->next;
		delete[]p;
		p = S.top;
	}
}

void Push( struct Stack &S, ElemType newDataItem )
{
	StackNode * p = new StackNode;
	p->dataltem = newDataItem;
	p->next = S.top;
	S.top = p; 
	S.Size++;
}

ElemType Pop( struct Stack &S )
{
	if(isEmpty(S))
	{
		printf("ջ�Ѿ����ˣ�����pop!\n");
		return FALSE;
	}
	StackNode *p = S.top;
	S.top = S.top->next;
	ElemType a = p->dataltem;
	delete []p;
	S.Size--;
	return a;
}

void clear( struct Stack &S )			
{
	if(isEmpty(S))
	{
		return;
	}
	StackNode * p = S.top;
	while(S.top)
	{
		S.top = S.top->next;
		cout<<"ɾ��"<<p->dataltem<<endl; 
		delete []p;
		p = S.top;
	}
	cout<<"ջ�Ѿ����\n"; 
}

bool isEmpty( struct Stack S )					
{
	return S.top==NULL;
}

bool isFull( struct Stack S )					  
{
	return false;
}

void showStructure( struct Stack S )
{
	if(S.Size==0) 
	{
		cout<<"ջΪ��"<<endl;
		return; 
	}
	cout<<"��ջ����ջ�׵�Ԫ�������ǣ�\n (top)";
	StackNode * p = S.top;
	while(p)
	{
		cout<<" -> "<<p->dataltem;	
		p = p->next;
	} 
	cout<<"->(end)"<<endl;
	
}


