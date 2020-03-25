#include "PointList.h"
#include "PointList.cpp" 
using std::cin; 
using std::cout;
using std::endl; 
void InitTestPointList( PointList &polygon )
{
	Point vertex; 	
	int	  i, N;
	
	InitPointList( polygon ); //初始化多边形: size=0,cursor=-1; 

	cout << "Enter the number of point of polygon: " << endl; //polygon多边形 
ll:	cin >> N;
	if ( N<=0 || N>=MAXLISTSIZE ) {
		cout << "Error!  input again! "  << endl;
		goto ll;
	}
		
	cout << "Input each point!" << endl;
	for ( i=0; i<N; i++ ) {
		cin >> vertex.x >> vertex.y;
		appendPoint( polygon, vertex ); 
	}
}

void TestPointList( PointList &polygon ) //顺序遍历 
{
	Point vertex; 				

	if ( !isEmpty(polygon) )
	{ 
		gotoBeginning(polygon);	//Go to beginning of list
		do {
			vertex = getCursor(polygon);
			cout << "(" << vertex.x << "," << vertex.y << ")" << endl;
		} while( gotoNext(polygon) );		//Go to next point (if any)
	}
}

void TestMakeSquare( PointList &L )
{
	Point vertex; 
	int i=0;
	if ( !isEmpty(L) )
	{
		gotoBeginning(L);	
		do {
			vertex= getCursor(L); i++;
			cout << "(" << vertex.x << "," << vertex.y << ")" << endl;
		} while ( gotoNext(L) && i<4 );		//Go to next point (if any)	
	}
}

void TestMakeDragon( PointList &L )
{
	Point vertex; 
	if ( !isEmpty(L) )
	{
		gotoBeginning(L);	
		do {
			vertex= getCursor(L); 
			cout << "(" << vertex.x << "," << vertex.y << ")" << endl;
		} while ( gotoNext(L) );		//Go to next point (if any)	
	}
}

void TestMakeSpline( PointList &L ) //曲线、齿条 
{
	Point vertex; 
	if ( !isEmpty(L) )
	{
		gotoBeginning(L);	
		do {
			vertex= getCursor(L); 
			cout << "(" << vertex.x << "," << vertex.y << ")" << endl;
		} while ( gotoNext(L) );		//Go to next point (if any)	
	}
}


bool Comm_isTranslation(PointList &List, PointList &otherList )
{
	Point vertex1, vertex2, delta; 
	
	if ( isEmpty(List) || isEmpty(otherList)  ) return FALSE;
	if ( getNumber(List)!=getNumber(otherList) ) return FALSE;

	gotoBeginning(List);	
	gotoBeginning(otherList);	
	vertex1 = getCursor(List); 
	vertex2 = getCursor(otherList); 
	delta.x = vertex1.x-vertex2.x; 
	delta.y = vertex1.y-vertex2.y;
	do {
		vertex1 = getCursor(List); 
		vertex2 = getCursor(otherList); 
		if ( ( vertex1.x!=vertex2.x+delta.x ) || ( vertex1.y!=vertex2.y+delta.y ) ) return FALSE;		
	} while ( gotoNext(List) && gotoNext(otherList) );	
	
	return TRUE;
}

bool Comm_isRotate(PointList &List, PointList &otherList )
{
	return FALSE;
}

bool Comm_isScall(PointList &List, PointList &otherList )
{
	return FALSE;
}


void Comm_APPand( PointList &L, Point vertex )
{
	appendPoint( L, vertex );
	vertex = getCursor( L );	
	cout << vertex.x << ", " << vertex.y << endl;
}

void Comm_Alta( PointList &L )
{
	Point vertex;
	vertex = getCursor( L );	
	cout << vertex.x << ", " << vertex.y << endl;
}
			

void Comm_N( PointList &L ) //输出下一个点 
{
	Point vertex;
	gotoNext( L ); 
	vertex = getCursor( L );	
	cout << vertex.x << ", " << vertex.y << endl;
}

void Comm_P( PointList &L ) //输出上一个点 
{
	Point vertex;
	gotoPrior( L ); 
	vertex = getCursor( L );	
	cout << vertex.x << ", " << vertex.y << endl;
}

void Comm_Head( PointList &L ) //输出第一个点 
{
	Point vertex;
	gotoBeginning( L );
	vertex = getCursor( L );	
	cout << vertex.x << ", " << vertex.y << endl;
}

void Comm_End( PointList &L ) //输出最后一个点 
{
	Point vertex;
	gotoEnd( L ); 
	vertex = getCursor( L );	
	cout << vertex.x << ", " << vertex.y << endl;
}

void Comm_E( PointList &L ) //判空 
{
	if (isEmpty(L) ) 
		cout << "YES! List is empty!" << endl;
	else
		cout << "NO! List is not empty!" << endl;
}

void Comm_F( PointList &L ) //判满 
{
	if (isFull(L) ) 
		cout << "YES! List is full!" << endl;
	else
		cout << "NO! List is not full!" << endl;
}

void Comm_C( PointList &L ) //清空表 
{
	clear( L );
}


void Comm_Other( void )
{
		
}

void Comm_Q( int &t )
{
	t = TRUE;
}


void Comm_T( PointList &List )
{
	PointList otherList;
	InitTestPointList( List );
	InitTestPointList( otherList );
	if ( Comm_isTranslation(List,otherList) )
		cout << "YES! They are Translation!" << endl;
	else
		cout << "NO! They are not Translation!" << endl;
}

void Comm_Jin( PointList &L, Point newPoint )
{
	insertAtBeginnig( L, newPoint );
	showStructure(L);
}

void showCommon()
{
	cout<<"输入+ x y表示把点(x,y)添加到点列表当中"<<endl;
	cout<<"输入@"	
} 
void ExplanComm_Sq( PointList &L )
{
	int  T = FALSE;
	char key;
	do {
		cout <<  "input comm: ";
		cin >> key;
		switch( key ) {
			case '+' : 
				Point vertex;
				cin >> vertex.x >> vertex.y;		
				Comm_APPand( L, vertex );
				break;
			case '@' :
				Comm_Alta( L );
				break;
			case 'N' :
			case 'n' :	
				Comm_N( L );
				break;
			case 'P' :
			case 'p' :
				Comm_P( L );
				break;
			case '<' :
				Comm_Head( L );
				break;
			case '>' :
				Comm_End( L );
				break;
			case 'E' :
			case 'e' :
				Comm_E( L );
				break;
			case 'F' :
			case 'f' :
				Comm_F( L );
				break;
			case 'C' :
			case 'c' :
				Comm_C( L );
				break;
			case 'Q' :
			case 'q' :
				Comm_Q( T );
				return;
			case 'T' :
			case 't' :
				Comm_T( L );
				break;
			case '#' :
				Point newPoint;
				cin >> newPoint.x >> newPoint.y;
				Comm_Jin( L, newPoint );
				break;
			default:
				Comm_Other(); //什么都不做 
				break;
		}
		cout << endl;
	} while( !T );
}


int main(void)
{
	PointList polygon; 
	
	cout << "Program test!" <<endl;
		
	
	cout << "Test list show!" <<endl;
	InitTestPointList( polygon );
	TestPointList( polygon );   //visit List!顺序访问 

	cout << "Test list Square!" <<endl;
	InitTestPointList( polygon );
	TestMakeSquare( polygon );   //Square test!
	

	cout << "Comm test(命令测试)!" <<endl;
	InitPointList( polygon );
	ExplanComm_Sq(polygon);
	return 0;
}
