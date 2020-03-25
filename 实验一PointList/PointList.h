#include "c1.h"
 
#ifndef POINTLIST_H
#define POINTLIST_H

typedef int Bool;

#define MAXLISTSIZE	100 							// Default maximum list size 

struct Point {   	
	float x, y;  									// Point coordinates 
};

struct PointList {
  	int    size; 									// Actual number of points in the list
	int    cursor; 									// Cursor index
	struct Point points[MAXLISTSIZE]; 				// Array containing the points
};

//Init Point List
void InitPointList( PointList &L );
	
// List manipulation operations 
void appendPoint( PointList &L, Point newPoint );		// Append point to list
void clear( PointList &L ); 							// Clear list  

// List status operations 
bool isEmpty(PointList L); 							// List is empty
bool isFull(PointList L); 							// List is full

// List iteration operations 
void gotoBeginning(PointList &L); 					// Go to beginning
void gotoEnd (PointList &L); 						// Go to end
bool gotoNext(PointList &L); 						// Go to next point
bool gotoPrior(PointList &L); 						// Go to prior point
Point getCursor(PointList L);						// Return point
int  getNumber(PointList L);						// Return number of points

// Output the list structure - used in testing/debugging
void showStructure(PointList L);
void insertAtBeginnig( PointList &L, Point newPoint ); 

#endif