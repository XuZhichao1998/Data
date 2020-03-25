#include "c1.h"
#ifndef LISTDBL_H
#define LISTDBL_H

struct ListNode {   ///���
	ElemType data; ///����
	ListNode  *prior, *next; ///ǰ��ָ�룬���ָ��
};
struct List {    ///����
	ListNode *StartPos; ///�׽ڵ�
	ListNode *EndPos;  ///β�ڵ�
	ListNode *CurPos;  ///��ǰָ��
	int 	  Length;  ///������
};
void InitList( List &L );  ///��ʼ������
void DestroyList( List &L ); ///��������
void insert( List &L, ElemType &newData ); ///��CurPos����������newData
int  remove( List &L ); ///ɾ����ǰ�ڵ�
void clear( List &L );  ///�������
bool isEmpty( List L ); ///�жϿ�
bool isFull( List L );///�ж���
bool isEnd( List L ); ///��
bool isHead( List L ); ///�жϵ�ǰָ���Ƿ�ָ����Ԫ���
void gotoBeginning( List &L ); ///��ǰָ��ָ����Ԫ�ڵ�
void gotoEnd( List &L ); ///��ǰָ��ָ��β�ڵ�
bool gotoNext( List &L ); ///ʹ��ǰָ��ָ����һ���ڵ�
bool gotoPrior( List &L ); ///ʹ��ǰָ��ָ��ǰһ���ڵ�
ElemType getCursor(List L ); ///���ص�ǰָ�������Ԫ��
void showStructure( List L ); ///��ʾ��������Ԫ��
void replace( List &L, ElemType &newDataItem ); ///����ǰλ�õĽڵ�Ԫ���滻ΪnewData
int  getLength( List L );
int  getCurPosition( List L ); ///�õ���ǰԪ���������е�λ��(�ڼ���)
void Shift_R( List &L );  ///�ַ���ѭ������
void Shift_L( List &L ); ///�ַ���ѭ������
void SwapItem( List &L ); ///�����ַ�����β
void Reverse( List &L ); ///
void showListData( List &L ); ///��ʾ��������Ԫ��
void CreatList( List &L, char str[] );///��str�����е��ַ��������µ�����
void ReplaceList( List &L, char str[] ); ///��str�����д���ַ�����ԭ����

#endif
