#include "c1.h"
 
#ifndef STACK_H
#define STACK_H

struct Stack {
	int maxSize;				
	int	top;					
	ElemType *dataItems;	 
};
void InitStack( struct Stack &S, int maxNumber ); 
void DestroyStack( struct Stack &S );	
void Push( struct Stack &S, ElemType newDataItem );
ElemType Pop( struct Stack &S );
void clear( struct Stack &S );			
bool isEmpty( struct Stack S );					
bool isFull( struct Stack S );					 
void showStructure( struct Stack S );

#endif
