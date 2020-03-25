#include "ListDBL.h"
using namespace std;
void InitList( struct List &L ) //����һ�����б�
{
	L.Length = 0;
	L.CurPos = L.EndPos = L.StartPos = NULL;   
}

void DestroyList( List &L ) //�ͷŴ洢�б���ڴ�
{
	if(L.Length==0) return;
	L.Length = 0;
	ListNode * head = L.StartPos;
	ListNode * p = L.StartPos->next;
	while(p!=head)
	{
		head -> next = p -> next;
		//cout<<"ɾ��"<<p->data<<"\n"; 
		delete[]p;
		p = head->next;
	}	
	//cout<<"ɾ��"<<head->data<<endl; 
	delete[] head;
	L.CurPos = L.EndPos = L.StartPos = NULL;
}

/*
void insert(List & L,ElemType &newData)
����������б���
���б�ǿգ����������ָ��֮��
���������������Ϊ�б�ĵ�һ�������
������ɺ�ǰָ��ָ�������� 
*/
void insert( List &L, ElemType &newData )  
{
	ListNode * now = new ListNode;
	now -> data = newData;
	L.Length++;
	if(L.Length==1) //��Ϊ�� 
	{
		L.CurPos = now;
		L.EndPos = now;
		L.StartPos = now;
		now->prior = now;
		now->next = now;
		return; 
	}
	now->prior = L.CurPos;
	now->next = L.CurPos->next;
	L.CurPos->next = now;
	L.EndPos = L.CurPos = now;
}

/*
int remove(List & L)
ɾ���б���ָ������ǵ������
�������б�ǿգ��ƶ�ָ��ָ��ɾ�����������һ�������
���ɾ�������������б�ĩβ���ƶ�ָ��ָ���б�ʼ�� 
*/
int remove( List &L ) 
{
	if(L.Length==0||L.CurPos==NULL) return 0; //��Ϊ�ջ�ָ��ָ��Ϊ�� 
	if(L.Length==1) 
	{
		delete[] L.CurPos;
		L.CurPos = L.EndPos = L.StartPos = NULL;
		L.Length = 0;
		return 1; 
	} 
	L.Length--;
	if(L.CurPos==L.EndPos)  //ɾ��β�ڵ� 
	{
		ListNode * p = L.CurPos->prior; 
		delete[] L.CurPos;
		p->next = L.StartPos;
		L.StartPos->prior = p;
		L.EndPos = p;
		L.CurPos = L.StartPos;
		return 1;
	}
	else if(L.CurPos==L.StartPos)  //ɾ��ͷ��� 
	{
		ListNode * p = L.CurPos;
		L.CurPos = L.CurPos->next;
		L.StartPos = L.CurPos;
		L.StartPos->prior = L.EndPos;
		delete[]p;
		L.EndPos->next = L.StartPos;
		return 1;	
	}
	else 
	{
		ListNode * p = L.CurPos;
		L.CurPos = L.CurPos->next;
		p->prior->next = L.CurPos;
		L.CurPos->prior = p->prior;
		delete[]p;
		return 1;	
	}
	
	
}


void replace( List &L, ElemType &newDataItem ) //�滻ָ��ָ���Ԫ��ΪnewDataItem 
{
	if(L.CurPos!=NULL) L.CurPos->data = newDataItem,cout<<"������"<<newDataItem <<endl;
}

void clear( List &L )  //ɾ���б������������							  
{
	DestroyList(L); 
}


bool isEmpty(List L) 						
{
	return (L.Length==0);
}


bool isFull(List L) 						
{
	return false;
}


void gotoBeginning(List &L) 				
{
	L.CurPos = L.StartPos;
}


void gotoEnd(List &L) 					
{
	L.CurPos = L.EndPos;
}

/*
bool gotoNext( List L ) 
Ҫ���б�ǿա�
���������б�ָ�벻���б�ĩβ���ƶ�ָ�뵽�б����һ�����������true�����򣬷���false��
*/
bool gotoNext(List &L) 
{
	if(L.Length==0 || L.CurPos==L.EndPos) return false;
	L.CurPos = L.CurPos->next;
	return true;
}
	
/*
bool gotoPrior( List L ) 
Ҫ���б�ǿա�
���������б�ָ�벻���б�ʼ���ƶ�ָ�뵽�б��ǰһ����������� true�����򣬷���false��
*/				
bool gotoPrior(List &L) 
{
	if(L.Length==0 || L.CurPos==L.StartPos) return false;
	L.CurPos = L.CurPos->prior;
	return true;
}

/*	
ElemType getCursor( List L ) 
Ҫ���б�ǿա�
���������ָ��������������ֵ��
*/			
ElemType getCursor(List L)					
{
	return (L.CurPos->data);
}


void showStructure(List L)
{
	if(L.Length==0)
	{
		cout<<"����Ϊ�գ�"<<endl;
		return;
	}
	cout<<"��˫������Ϊ��head";
	ListNode * now = L.StartPos;
	while(1)
	{
		cout<<" -> "<<now->data;
		now = now->next;
		if(now==L.StartPos) break;
	}
	cout<<endl;
	
}

int  getLength( List L )
{
	return L.Length;
}

int  getCurPosition( List L )
{
	int ans = 1;
	ListNode * p = L.StartPos;
	while(p!=L.CurPos&&p!=L.EndPos)
	{
		p = p->next;
		ans++;
		if(p==L.CurPos) break;
	}
	return ans;
}
 
void Shift_R( List &L )
{
	if(L.Length<=1) return;//���˺�û��Ч��һ�� 
	ElemType temp = L.EndPos->data;
	ListNode * p = L.EndPos;
	while(p!=L.StartPos)
	{
		p->data = p->prior->data;
		p = p->prior;
	}
	L.StartPos->data = temp;
}

/*
void shiftLeft() 
Ҫ����
�����һ�������е���ĸ����һ��λ�ã�����ߵ���ĸ�Ƶ��������ұߡ�
*/
void Shift_L( List &L )  //��ĸ������һ��λ�ã�����ߵ��Ƶ����ұ� 
{
	if(L.Length<=1) return;//���˺�û��Ч��һ�� 
	ElemType temp = L.StartPos->data;
	ListNode * p = L.StartPos;
	while(p!=L.EndPos)
	{
		p->data = p->next->data;
		p = p->next;
	}
	L.EndPos->data = temp;
}

void Reverse( List &L ) //����һ���б��е�������˳�򣬲��ƶ�ָ���λ�� 
{
	if(L.Length<2) return;
	ListNode * Px=L.StartPos, * Nx=L.EndPos;
	int Ip = 1, In = L.Length;
	while(Ip<In)
	{
		swap(Px->data,Nx->data);
		Px = Px->next, Nx = Nx->prior;
		Ip++,In--;
	}
}

void SwapItem( List &L )  //���б����βԪ�ػ��� 
{
	if(L.Length<=1) return;
	ElemType temp = L.EndPos->data;
	L.EndPos->data = L.StartPos->data;
	L.StartPos->data = temp; 
}

void showListData( List &L )
{
	showStructure(L);
}

bool isEnd( List L )
{
	return (L.CurPos==L.EndPos);
} 	
					
bool isHead( List L )
{
	return (L.CurPos==L.StartPos);
} 						

void CreatList( List &L, char str[] )
{
	InitList(L);
	for(;*str;str++)
	{
		insert(L,*str);
	}
}

void ReplaceList( List &L, char str[] )
{
	DestroyList(L);
	CreatList(L,str);
}
/*
int main()
{
	int T = 1;
	while(T--)
	{
		List L;
		InitList(L);
		for(char ch='A';ch<='Z';++ch)
			insert(L,ch);
		cout<<"��ĳ���Ϊ��"<<getLength(L)<<endl;
		int flag = 1;
		gotoBeginning(L);
		while(flag)
		{
			gotoEnd(L);
			//if(L.CurPos!=L.StartPos) gotoPrior(L);
			if(L.Length==0) break;
			cout<<"\n-----------------------------------\n";
			cout<<"��ǰ�б�ĳ���Ϊ��"<<getLength(L)<<endl; 
			cout<<"��ǰָ��ָ��Ԫ��Ϊ��"<<getCursor(L)<<endl;
			flag = remove(L);
			cout<<"ɾ����ǰԪ�غ���б�Ϊ��\n"; 
			showStructure(L);
			Reverse(L);
			cout<<"��ת��\n"; 
			showStructure(L);
			Reverse(L);
			int ttt = L.Length;
			if(ttt<=5)
			while(ttt--)
			{
				cout<<"���ƣ�\n";
				Shift_L(L);showStructure(L);	
			}
			
			cout<<endl<<endl;
		}
		DestroyList(L);
		showStructure(L);
		
	}
	
	
	return 0;
}
*/
