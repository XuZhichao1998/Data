#include "c1.h"
 
#ifndef STACK_H
#define STACK_H

struct StackNode {
	ElemType  dataltem; 		// Stack data item 
	struct StackNode *next; 	// Pointer to the next data item 
};

struct Stack {
	int	Size;		 
	struct StackNode *top;	 
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