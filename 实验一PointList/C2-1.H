// c2-1.h 线性表的动态分配顺序存储结构

#include "c1.h"
 
#ifndef C2_1_H
#define C2_1_h

#define LIST_INIT_SIZE 10 // 线性表存储空间的初始分配量
#define LISTINCREMENT 2 // 线性表存储空间的分配增量

struct SqList
{
   ElemType *elem;	// 存储空间基址
   int length;		// 当前长度
   int listsize;	// 当前分配的存储容量(以sizeof(ElemType)为单位)
};

extern Status InitList(SqList &L);
extern Status DestroyList(SqList &L);
extern Status ClearList(SqList &L);
extern Status ListEmpty(SqList L);
extern int ListLength(SqList L);
extern Status GetElem(SqList L,int i,ElemType &e);
extern int LocateElem(SqList L,ElemType e,Status(*compare)(ElemType,ElemType));
extern Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e);
extern Status NextElem(SqList L,ElemType cur_e,ElemType &next_e);
extern Status ListInsert(SqList &L,int i,ElemType e);
extern Status ListDelete(SqList &L,int i,ElemType &e);
extern Status ListTraverse(SqList L,void(*vi)(ElemType&));


#endif