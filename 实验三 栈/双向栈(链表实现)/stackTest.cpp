#include "Stackdbl.h"
using namespace std; 
void Comm_ADD( Stack &S, ElemType data )
{
	Push(S,data);
	showStructure(S);
}

void Comm_SUB( Stack &S, ElemType &data )
{
	data = Pop(S);
	cout << data << endl;
	showStructure(S);
}

void Comm_E( Stack S )
{
	if (isEmpty(S) ) 
		cout << "YES! List is empty!" << endl;
	else
		cout << "NO! List is not empty!" << endl;
}

void Comm_F( Stack S )
{
	if (isFull(S) ) 
		cout << "YES! List is full!" << endl;
	else
		cout << "NO! List is not full!" << endl;
}

void Comm_C( Stack &S )
{
	clear( S );
}

void Comm_Other( void )
{
		
}

void Comm_Q( int &t )
{
	t = TRUE;
}

Bool isOperator( char ch )
{
	if ( ch=='+' || ch=='-' || ch=='*' || ch=='/' ) return TRUE;
	else return FALSE;
}

Bool isOpand( char ch )
{
	if ( ch>='0' && ch<='9' ) return TRUE;
	else return FALSE;
}

Bool delimitersOk( Stack &S, char *str )
{
	int  flag = 0;
	cout<<"flag = "<<flag<<endl; 
	
	char *p, ch;
	p = str;
	while ( *p )
	{
		if ( *p=='(' || *p=='[' || *p=='{' ) Push(S,*p );
		else if ( *p==')' || *p==']' || *p=='}' ) {
			if (isEmpty(S)) return FALSE;
			ch = Pop(S);
			if ( !( ch=='('&&*p==')' || ch=='['&&*p==']' || ch=='{'&&*p=='}' ) ) return FALSE;
		}
		p++;
	}
	

	if (!isEmpty(S)) return FALSE;
	else return TRUE;
}


void Comm_K( Stack &S )
{
	char str[MAXSTRING];
	if (!isEmpty(S)) clear(S);
	cout << "Input a string: ";
	cin >> str;
	if ( strlen(str)>=MAXSTRING ) {
		cout << "String too longer!" << endl;
		return;
	}

	if ( delimitersOk(S,str) )
		cout << "That'S OK!" << endl;
	else
		cout << "NO! That'S ERROR!" << endl;
}

Bool postfix( Stack &S, char *str, double &v )
{
	double x1,x2;
	char *p;
	
	p = str;
	while ( *p ) {
		if (isOpand(*p)) Push( S, (double)(*p-'0') );
		else if (isOperator(*p)) {
			if (!isEmpty(S)) x1 = Pop(S); else return FALSE;
			if (!isEmpty(S)) x2 = Pop(S); else return FALSE;
			switch ( *p ) {
				case '+' :
					Push( S, x2+x1 );
					break;
				case '-' :
					Push( S, x2-x1 );
					break;
				case '*' :
					Push( S, x2*x1 );
					break;
				case '/' :
					if ( fabs(x1)<1.0E-6 )  return FALSE;
					Push( S, x2/x1 );
					break;
			}
		}
		else return FALSE;
		p++; 
	}
	if (isEmpty(S)) return FALSE;
	else {
		v = Pop(S);
		if (isEmpty(S)) return TRUE; else return FALSE;
	}
}

void Comm_H( Stack &S )
{
	double v;
	char str[MAXSTRING];

	if (!isEmpty(S)) clear(S);
	cout << "Input a string: ";
	cin >> str;
	if ( strlen(str)>=MAXSTRING ) {
		cout << "String too longer!" << endl;
		return;
	}
	if (!postfix(S,str,v)) {
		cout << "Expression error!" << endl; 
		return;
	}
	cout << "Expression result: " << v << endl;
}
void show()
{
	cout<<"输入 + x表示 push(x)压栈"<<endl;
	cout<<"输入 -  表示 pop()弹栈"<<endl;
	cout<<"输入 e(E) 判空"<<endl;
	cout<<"输入 f(F) 判满"<<endl;
	cout<<"输入 q(Q) 退出"<<endl;
	cout<<"输入 c(C) 表示clear()清空栈"<<endl;
	cout<<"输入 h(H) 计算后缀表达式"<<endl;
	cout<<"输入 k(K) 检测括号匹配"<<endl;
	cout<<"输入 s(S) 显示栈中所有元素"<<endl;	
	
}  
void ExplanComm_Sq( Stack &S )
{
	ElemType data;
	int  T = FALSE;
	char key;
	show(); 
	do {
		cout <<  "input comm: ";
		cin >> key;
		switch( key ) {
			case '+' : 
				cin >> data;		
				Comm_ADD( S, data );
				break;
			case '-' : 
				Comm_SUB( S, data );
				break;
			case 'E' :
			case 'e' :
				Comm_E( S );
				break;
			case 'F' :
			case 'f' :
				Comm_F( S );
				break;
			case 'H' :
			case 'h' :
				Comm_H( S );
				break;
			case 'K' :
			case 'k' :
				Comm_K( S );
				break;
			case 'C' :
			case 'c' :
				Comm_C( S );
				break;
			case 'Q' :
			case 'q' :
				Comm_Q( T );
				return;
			case 's':case 'S':
				showStructure(S);
				break;
			default:
				Comm_Other();
				break;
		}
		cout << endl;
	} while( !T );
}


int main(void)
{
	Stack S; 
	cout << "Comm test!" <<endl;
	InitStack( S, 100 );
	ExplanComm_Sq(S);
	DestroyStack( S );
	return 0;
}

