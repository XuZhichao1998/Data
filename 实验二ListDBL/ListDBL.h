#include "c1.h"
#ifndef LISTDBL_H
#define LISTDBL_H

struct ListNode {   ///结点
	ElemType data; ///数据
	ListNode  *prior, *next; ///前驱指针，后继指针
};
struct List {    ///链表
	ListNode *StartPos; ///首节点
	ListNode *EndPos;  ///尾节点
	ListNode *CurPos;  ///当前指针
	int 	  Length;  ///链表长度
};
void InitList( List &L );  ///初始化链表
void DestroyList( List &L ); ///销毁链表
void insert( List &L, ElemType &newData ); ///在CurPos出插入数据newData
int  remove( List &L ); ///删除当前节点
void clear( List &L );  ///清空链表
bool isEmpty( List L ); ///判断空
bool isFull( List L );///判断满
bool isEnd( List L ); ///将
bool isHead( List L ); ///判断当前指针是否指向首元结点
void gotoBeginning( List &L ); ///当前指针指向首元节点
void gotoEnd( List &L ); ///当前指针指向尾节点
bool gotoNext( List &L ); ///使当前指针指向下一个节点
bool gotoPrior( List &L ); ///使当前指针指向前一个节点
ElemType getCursor(List L ); ///返回当前指针的数据元素
void showStructure( List L ); ///显示链表所有元素
void replace( List &L, ElemType &newDataItem ); ///将当前位置的节点元素替换为newData
int  getLength( List L );
int  getCurPosition( List L ); ///得到当前元素在链表中的位置(第几个)
void Shift_R( List &L );  ///字符串循环右移
void Shift_L( List &L ); ///字符串循环左移
void SwapItem( List &L ); ///交换字符串首尾
void Reverse( List &L ); ///
void showListData( List &L ); ///显示链表所有元素
void CreatList( List &L, char str[] );///用str数组中的字符串创建新的链表
void ReplaceList( List &L, char str[] ); ///用str数组中存的字符串替原链表

#endif
