// c1.h (������)

#include<string.h>
#include<ctype.h>
#include<malloc.h> // malloc()��
#include<limits.h> // INT_MAX��
#include<cstdio> // EOF(=^Z��F6),NULL
#include<stdlib.h> // atoi()
#include<io.h> // eof()
#include<math.h> // floor(),ceil(),abs()
#include<process.h> // exit()
#include<iostream> // cout,cin

#ifndef C_H
#define C_H

#define TRUE		1
#define FALSE		0
#define OK			1
#define ERROR		0
#define INFEASIBLE -1

typedef int Status; // Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK��
typedef int Boolean; // Boolean�ǲ�������,��ֵ��TRUE��FALSE

#define defMaxStackSize 100;		

typedef int Bool;
//typedef int	ElemType;
//typedef char	ElemType;
typedef double	ElemType;

#endif
