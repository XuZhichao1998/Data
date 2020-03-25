#include "c1.h"
 
#ifndef STACK_H
#define STACK_H

#define MAXSTRING 64

struct Stack {
	int maxSize;				//Maximum number of data items in the stack
	int	top;					//Index of the top data items
	int down;
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
void Push_D( struct Stack &S, ElemType newDataItem );
ElemType Pop_D( struct Stack &S );
void clear_D( struct Stack &S );			
bool isEmpty_D( struct Stack S );					
bool isFull_D( struct Stack S );	

#endif