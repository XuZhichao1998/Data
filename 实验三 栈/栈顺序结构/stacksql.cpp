#include "Stacksql.h"
using namespace std;
void InitStack( struct Stack &S, int maxNumber ) 
{
	S.maxSize = maxNumber;
	S.dataItems = new ElemType[maxNumber];
	S.top = 0; 
}

void DestroyStack( struct Stack &S )	
{
	if(S.dataItems!=NULL) delete[] S.dataItems;
	S.top = S.maxSize = 0;
}

void Push( struct Stack &S, ElemType newDataItem )
{
	if(!isFull(S))
		S.dataItems[S.top++] = newDataItem;
}

ElemType Pop( struct Stack &S )
{
	if(!isEmpty(S)) return S.dataItems[--S.top];
	else 
	{
		cout<<"ջ�Ѿ����ˣ�����pop()�ˣ�\n";
		return FALSE;
	}
}

void clear( struct Stack &S )			
{
	S.top = 0;
}

bool isEmpty( struct Stack S )					
{
	return (S.top==0);
}

bool isFull( struct Stack S )					  
{
	return (S.top==S.maxSize);
}

void showStructure( struct Stack S )
{
	if(!S.top) {cout<<"ջΪ��\n";return;}
	cout<<"ջ��ջ�׵�ջ����Ԫ��Ϊ��";
	int i;
	for(i=0;i<S.top;i++)
		cout<<S.dataItems[i]<<" ";cout<<endl; 
}

