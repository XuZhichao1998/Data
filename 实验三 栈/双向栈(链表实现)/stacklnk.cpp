
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
}

ElemType Pop( struct Stack &S )
{
	if(isEmpty(S))
	{
		printf("栈已经空了，不能pop!\n");
		return FALSE;
	}
	StackNode *p = S.top;
	S.top = S.top->next;
	ElemType a = p->dataltem;
	delete []p;
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
		cout<<"删除"<<p->dataltem<<endl; 
		delete []p;
		p = S.top;
	}
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
	cout<<"从栈顶到栈底的元素依次是：\n (top)";
	StackNode * p = S.top;
	while(p)
	{
		cout<<" -> "<<p->dataltem;	
		p = p->next;
	} 
	cout<<"->(end)"<<endl;
	
}


