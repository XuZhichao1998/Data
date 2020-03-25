#include "ListDBL.h"
using namespace std;
void InitList( struct List &L ) //创建一个空列表
{
	L.Length = 0;
	L.CurPos = L.EndPos = L.StartPos = NULL;   
}

void DestroyList( List &L ) //释放存储列表的内存
{
	if(L.Length==0) return;
	L.Length = 0;
	ListNode * head = L.StartPos;
	ListNode * p = L.StartPos->next;
	while(p!=head)
	{
		head -> next = p -> next;
		//cout<<"删除"<<p->data<<"\n"; 
		delete[]p;
		p = head->next;
	}	
	//cout<<"删除"<<head->data<<endl; 
	delete[] head;
	L.CurPos = L.EndPos = L.StartPos = NULL;
}

/*
void insert(List & L,ElemType &newData)
插入数据项到列表。如
果列表非空，插入数据项到指针之后，
否则插入数据项作为列表的第一个数据项。
操作完成后当前指针指向该数据项。 
*/
void insert( List &L, ElemType &newData )  
{
	ListNode * now = new ListNode;
	now -> data = newData;
	L.Length++;
	if(L.Length==1) //表为空 
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
删除列表中指针所标记的数据项。
如果结果列表非空，移动指针指向删除数据项的下一个数据项。
如果删除的数据项在列表末尾，移动指针指向列表开始。 
*/
int remove( List &L ) 
{
	if(L.Length==0||L.CurPos==NULL) return 0; //表为空或指针指向为空 
	if(L.Length==1) 
	{
		delete[] L.CurPos;
		L.CurPos = L.EndPos = L.StartPos = NULL;
		L.Length = 0;
		return 1; 
	} 
	L.Length--;
	if(L.CurPos==L.EndPos)  //删除尾节点 
	{
		ListNode * p = L.CurPos->prior; 
		delete[] L.CurPos;
		p->next = L.StartPos;
		L.StartPos->prior = p;
		L.EndPos = p;
		L.CurPos = L.StartPos;
		return 1;
	}
	else if(L.CurPos==L.StartPos)  //删除头结点 
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


void replace( List &L, ElemType &newDataItem ) //替换指针指向的元素为newDataItem 
{
	if(L.CurPos!=NULL) L.CurPos->data = newDataItem,cout<<"换成了"<<newDataItem <<endl;
}

void clear( List &L )  //删除列表中所有数据项。							  
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
要求：列表非空。
结果：如果列表指针不在列表末尾，移动指针到列表的下一个数据项并返回true，否则，返回false。
*/
bool gotoNext(List &L) 
{
	if(L.Length==0 || L.CurPos==L.EndPos) return false;
	L.CurPos = L.CurPos->next;
	return true;
}
	
/*
bool gotoPrior( List L ) 
要求：列表非空。
结果：如果列表指针不在列表开始，移动指针到列表的前一个数据项并返回 true，否则，返回false。
*/				
bool gotoPrior(List &L) 
{
	if(L.Length==0 || L.CurPos==L.StartPos) return false;
	L.CurPos = L.CurPos->prior;
	return true;
}

/*	
ElemType getCursor( List L ) 
要求：列表非空。
结果：返回指针所标记数据项的值。
*/			
ElemType getCursor(List L)					
{
	return (L.CurPos->data);
}


void showStructure(List L)
{
	if(L.Length==0)
	{
		cout<<"链表为空！"<<endl;
		return;
	}
	cout<<"该双向链表为：head";
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
	if(L.Length<=1) return;//移了和没移效果一样 
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
要求：无
结果：一个字谜中的字母左移一个位置，最左边的字母移到字谜最右边。
*/
void Shift_L( List &L )  //字母都左移一个位置，最左边的移到最右边 
{
	if(L.Length<=1) return;//移了和没移效果一样 
	ElemType temp = L.StartPos->data;
	ListNode * p = L.StartPos;
	while(p!=L.EndPos)
	{
		p->data = p->next->data;
		p = p->next;
	}
	L.EndPos->data = temp;
}

void Reverse( List &L ) //倒置一个列表中的数据项顺序，不移动指针的位置 
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

void SwapItem( List &L )  //将列表的首尾元素互换 
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
		cout<<"表的长度为："<<getLength(L)<<endl;
		int flag = 1;
		gotoBeginning(L);
		while(flag)
		{
			gotoEnd(L);
			//if(L.CurPos!=L.StartPos) gotoPrior(L);
			if(L.Length==0) break;
			cout<<"\n-----------------------------------\n";
			cout<<"当前列表的长度为："<<getLength(L)<<endl; 
			cout<<"当前指针指的元素为："<<getCursor(L)<<endl;
			flag = remove(L);
			cout<<"删除当前元素后的列表为：\n"; 
			showStructure(L);
			Reverse(L);
			cout<<"翻转：\n"; 
			showStructure(L);
			Reverse(L);
			int ttt = L.Length;
			if(ttt<=5)
			while(ttt--)
			{
				cout<<"左移：\n";
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
