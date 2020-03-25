
#include "PointList.h"
#include <iostream>
using std::cin;
using std::cout; 
using std::endl;

void InitPointList( struct PointList &L )
{
	L.cursor = -1;
	L.size = 0;
}

	
void  appendPoint( PointList &L, Point newPoint )	
{
	if (L.size<MAXLISTSIZE) {
		L.points[L.size].x = newPoint.x;
		L.points[L.size].y = newPoint.y;
		L.size = L.size+1;
		L.cursor = L.size-1; //cursor:¹â±ê¡¢Ö¸Õë 
	}
}

void  clear(PointList &L) 							
{
	L.size = 0;
	L.cursor = -1;
}

bool  isEmpty(PointList L) 						
{
	if (L.size==0) return TRUE;
	else return FALSE;
}

bool  isFull(PointList L) 							
{
	if (L.size>=MAXLISTSIZE) return TRUE;
	else return FALSE;
}

void  gotoBeginning(PointList &L) 
{
	L.cursor = 0;
}

void  gotoEnd (PointList &L) 	
{
	L.cursor = L.size-1;
}

bool  gotoNext(PointList &L) 	
{
	if ( L.cursor<L.size-1 ) { 
		L.cursor = L.cursor+1;
		return TRUE;
	}
	else return FALSE;
}

bool  gotoPrior(PointList &L) 	
{
	if ( L.cursor>0 ) { 
		L.cursor = L.cursor-1;
		return TRUE;
	}
	else return FALSE;
}

struct Point getCursor(PointList L)	
{
	Point p;
	p.x = p.y = 0;

	if ( !isEmpty(L) )
		return L.points[L.cursor];
	else 
		return p;
}

void showStructure(PointList L)
{
	int i;
	cout << "element number is " << L.size << endl;
	cout << "cursor pos is " << L.cursor << endl;
	cout << "element is follow: " << endl;
	for ( i=0; i<L.size; i++ )
		cout << "element " << i+1 << ":  " << L.points[i].x << "," << L.points[i].y << endl; 	
}

int  getNumber(PointList L)
{
	return L.size;
}


void insertAtBeginnig( PointList &L, Point newPoint )
{
	int i;
	if ( isFull(L) ) return;
	for ( i=L.size-1; i>=0; i-- ) 
		L.points[i+1] = L.points[i];
	L.points[0].x = newPoint.x;
	L.points[0].y= newPoint.y;
	L.cursor = 0;
	L.size = L.size+1;
}
