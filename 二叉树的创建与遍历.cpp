#include <bits/stdc++.h>
#include "BiTree.h"
/*
	�������Ĵ���������˳��ı�����ǰ�к��򣬵ݹ�ǵݹ�
	�߼����ʽ��
	�߼����ʽ���㽻������
	����һ��һ�۵Ķ�����
	������ 
*/
using namespace std;
/*
typedef struct BiTNode
{
	char data;
	struct BiTNode * Lchild;
	struct BiTNode * Rchild;
}BiTNode,*BiTree;
char str[1000];
typedef enum{Visit,Travel} TaskType; //���� �� ����
struct Node
{
	BiTree ptr;
	TaskType task;
};
void creatTree(BiTree &T)
{
	char ch;
	cin>>ch;
	if(ch=='#') T = nullptr;
	else
	{
		T = new BiTNode;
		T->data = ch;
		creatTree(T->Lchild);
		creatTree(T->Rchild);
	}
}
//������д��void�ĺô��Ǻ���ԭ�Ϳ���ͳһ�����ù���ʱ����Ժ���ָ��ʵ��
void PreOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	visit(T);
	PreOrder(T->Lchild,visit);
	PreOrder(T->Rchild,visit);
}
void InOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	InOrder(T->Lchild,visit);
	visit(T);
	InOrder(T->Rchild,visit);
}
void SubsequentOrder(BiTree T,void(*visit)(BiTree))
{
	if(!T) return;
	SubsequentOrder(T->Lchild,visit);
	SubsequentOrder(T->Rchild,visit);
	visit(T);
}
void visit(BiTree T)
{
	if(T)
		cout<<T->data;
}
void pre_order(BiTree T,void(*visit)(BiTree))
{
	stack<BiTree> S;
	BiTree p = T;
	while(p||!S.empty())
	{
		if(p) visit(p),S.push(p->Rchild),p = p->Lchild;
		else p = S.top(),S.pop();
	}
}
void in_order(BiTree T,void(*visit)(BiTree))
{
	stack<Node> S;
	if(T) S.push({T,Travel});
	TaskType task;
	BiTree p;
	while(!S.empty())
	{
		p = S.top().ptr;
		task = S.top().task;
		S.pop();
		if(task==Visit)
		{
			visit(p);
		}
		else      //(task==Travel)
		{
			if(p)
				S.push({p->Rchild,Travel}), //����е����� ����������
				S.push({p,Visit}),          //���ʸ��ڵ�
				S.push({p->Lchild,Travel}); //����������
		}
	}
}
void subsequent_order(BiTree T,void(*visit)(BiTree))
{
	stack<Node> S;
	if(T) S.push({T,Travel});
	TaskType task;
	BiTree p;
	while(!S.empty())
	{
		p = S.top().ptr;
		task = S.top().task;
		S.pop();
		if(task==Visit)
		{
			visit(p);
		}
		else      //(task==Travel)
		{
			if(p)
				S.push({p,Visit}),  //���ʸ��ڵ�
				S.push({p->Rchild,Travel}), //����е����� ����������
				S.push({p->Lchild,Travel}); //����������

		}
	}
}
*/


/*

AB#DE###C##
AB#C#DE###FG#H###

*/
int getDepth(const BiTree & T)
{
	if(!T) return 0;
	return max(getDepth(T->Lchild),getDepth(T->Rchild))+1;
}
void printTree(const BiTree &T)
{
	if(!T)
	{
		cout<<"������ǿ���"<<endl;
		return; 
	}
	int Height = getDepth(T);
	vector<int> blank;
	for(int i=Height-1;i>=0;i--)
		blank.push_back((1<<i)-1);
	int nowCent = 0; //��ǰ�Ĳ��� 
	int cnt = 0; //��ǰ�����Ѿ���ӡ�Ľڵ��� 
	//i:        0  1  2  3  
	//blanK[i]: 7  3  1  0
	//��ǰ����i��0,1,2,3,...Height-1
	//��ǰ���׽ڵ�Ҫ����Ŀո����� 2^(Height-1-i)-1 = blanK[i]
	//ÿ��Ŀո�����blanK[i-1] 
	queue<BiTree> Q; 
	Q.push(T);
	while(!Q.empty())
	{
		BiTree Fr = Q.front();Q.pop();
	//	cout<<"ͷ��"; 
		//cout<<Fr->data<<endl; 
		if(cnt==0)  //������еĵ�һ���ڵ㣬���ǰ��Ŀո��� 
		{
			int k = blank[nowCent];
		//	cout<<"k = "<<k<<endl;
			while(k--)
			{
				printf(" ");
			}
			//cout<<setw(blank[nowCent])<<" ";
		}
		else
		{
			//cout<<"nowCnt-1 = "<<nowCent-1<<endl;
			int k = blank[nowCent-1];
		//	cout<<"k = "<<k<<endl;
			while(k--)
			{
				printf(" ");
			}
			//cout<<setw(blank[nowCent-1])<<" ";
		}
		if(!Fr)
		{
			cout<<setw(2)<<"#"; 
		}
		else
		{
			cout<<setw(2)<<Fr->data;
			Q.push(Fr->Lchild);
			Q.push(Fr->Rchild); 
		}
		cnt++;
		if(cnt>=(1<<nowCent))
		{
			cout<<endl<<endl;
			nowCent++;
			cnt = 0;
		}
	
	}
	cout<<endl;
} 

int isOperator(char ch)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/') return ch;
	else return 0;
}
void creatExpreeTree(BiTree &T)
{
	char ch;
	cin>>ch;
	T = new BiTNode;
	T->data = ch;
	if(isOperator(ch))
	{
		creatExpreeTree(T->Lchild);
		creatExpreeTree(T->Rchild);
	}
	else T->Lchild = T->Rchild = nullptr;
}
bool cal(int op,int ansl,int ansr,int & result)
{
	if(op=='-'&&ansr==0)
	{
		cerr<<"Can't divied zero!\n";
		return false;
	}
	switch(op)
	{
		case '+':result = ansl+ansr; break;
		case '-':result = ansl-ansr; break;
		case '*':result = ansl*ansr; break;
		case '/':result = ansl/ansr; break;
		default:cerr<<"UnKnown Operator: "<<(char)op<<"!\n";
				result = 1; return false;
	}
	return true;
}
int calExpressTree(BiTree &T)
{
	if(!T) return 0;
	if(isdigit(T->data)) return T->data -'0';
	int op = isOperator(T->data);
	if(!op)
	{
		cerr<<"UnKnown Operator!\n";
		exit(-1);
	}
	int ansl = calExpressTree(T->Lchild);
	int ansr = calExpressTree(T->Rchild);
	if(op=='/'&&ansr==0)
	{
		cerr<<"Can't divied zero!\n";
		exit(-1);
	}
	int result = 1000;
	if(cal(op,ansl,ansr,result)) return result;
	else
	{
		exit(-1);
	}
	return result;
}
void Destroy(BiTree & T)
{
	if(!T) return;
	//cout<<"T->data = "<<T->data<<endl;
	if(T->Lchild==nullptr&&T->Rchild==nullptr)
	{
	//	cout<<"ɾ����"<<T->data<<endl;
		delete []T;
		return;
	}
	Destroy(T->Lchild);
	Destroy(T->Rchild);
	//cout<<"ɾ����"<<T->data<<endl;
	delete[]T;
}
void CreatLogiTree(BiTree & T)
{
	char ch;
	cin>>ch;
	T = new BiTNode;
	T->data = ch;
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/')
	{
		if(ch=='/')
		{
			cerr<<"The operator("<<ch<<") is invaide in LogiTree!\n";
			exit(-1);
		}
		if(ch!='-')
			CreatLogiTree(T->Lchild);
		else T->Lchild = nullptr;
		CreatLogiTree(T->Rchild);
	}
	else if(ch=='0'||ch=='1') T->Lchild = T->Rchild = nullptr;
	else
	{
		cerr<<"The operator("<<ch<<") is invaide in LogiTree!\n";
		exit(-1);
	}
}
int calLogiTree(BiTree T)
{
	if(!T) return 0;
	if(isdigit(T->data))
	{
	//cout<<"T->data = "<<T->data<<endl;
		int res = T->data -'0';
		//cout<<"res = "<<res<<endl;
		return res;

	}
	int op = isOperator(T->data);
	if(!op)
	{
		cerr<<"UnKnown Operator!\n";
		exit(-1);
	}
	if(op=='-')
	{
		int res = calLogiTree(T->Rchild);
		//cout<<"res = "<<res<<endl;
		//cout<<"-"<<res<<" = "<<(int)(!res)<<"\n";  //???
		return !res;
	}
	else
	{
		int ansl = calLogiTree(T->Lchild);
		int ansr = calLogiTree(T->Rchild);
		if(op=='+')
		{
			//cout<<ansl<<" + "<<ansr<<" = "<<(ansl||ansr)<<endl;
			return (ansl||ansr);
		}
		else if(op=='*')
		{
			//cout<<ansl<<" * "<<ansr<<" = "<<(ansl&&ansr)<<endl;
			return (ansl&&ansr);
		}
		else
		{
			cout<<"The operator("<<(char)op<<") is invaide in LogiTree!\n";
			exit(-1);
		}
	}
	//return result;
}
void CopyExpressTree(BiTree T,BiTree &TT)
{
	if(!T)
	{
		TT = nullptr;
		return;
	} 
	TT = new BiTNode;
	TT ->data = T->data;
	CopyExpressTree(T->Lchild,TT->Lchild);
	CopyExpressTree(T->Rchild,TT->Rchild);
}
void CommuteExpressTree(BiTree& T)
{
	if(!T) return;
	swap(T->Lchild,T->Rchild);
	CommuteExpressTree(T->Lchild);
	CommuteExpressTree(T->Rchild);
}
void CommuteLogiTree(BiTree& T)
{
	if(!T) return;
	//if(T->Lchild!=nullptr)    //���Lchild���գ�˵�����Ƿ����㣬˵�����Խ���
	if(T->data!='-')
		swap(T->Lchild,T->Rchild);
	CommuteLogiTree(T->Lchild);
	CommuteLogiTree(T->Rchild);
}
int main(void)
{

//	freopen("in.txt","r",stdin);
    BiTree T=nullptr,TT=nullptr;
    cout<<"������������"<<endl;
	creatTree(T);
	CopyExpressTree(T,TT);
	cout<<"�ѽ������T����ΪTT"<<endl; 
	cout<<"���������\n";
	PreOrder(T,visit); cout<<" (T)" <<endl;
	PreOrder(TT,visit); cout<<"(TT)" <<endl;
	cout<<"���������\n";
	InOrder(T,visit); cout<<"(T)"<<endl;
	InOrder(TT,visit); cout<<"(TT)"<<endl;
	cout<<"����������\n";
	SubsequentOrder(T,visit);cout<<"(T)"<<endl;
	SubsequentOrder(TT,visit);cout<<"(TT)"<<endl;
	cout<<"�ǵݹ��������:"<<endl;
	pre_order(T,visit);cout<<endl;
	cout<<"�ǵݹ��������:"<<endl;
	in_order(T,visit);cout<<endl;
	cout<<"�ǵݹ�������:"<<endl;
	subsequent_order(T,visit);cout<<endl; 
	cout<<"�������Ϊ��"<<getDepth(T)<<endl;
	printTree(T);
	
	
	int n = 2;
	while(n--)
	{
		BiTree tt=nullptr;
		cout<<"�����������ʽ��ǰ׺���ʽ��"<<endl;
		creatExpreeTree(tt);
		//PreOrder(tt,visit);
		cout<<"The result of this expression is: ";
		cout<<calExpressTree(tt)<<endl<<endl;
		CommuteExpressTree(tt);
		cout<<"������ı��ʽ���������";
		PreOrder(tt,visit);cout<<endl;
		cout<<"������ı��ʽ���������";
		InOrder(tt,visit); 
		cout<<"The result of this expression is: ";
		cout<<calExpressTree(tt)<<endl<<endl;
	    Destroy(tt);
	}
	fclose(stdin); 
	

	
    freopen("in1.txt","r",stdin);
 	n = 2;
    while(n--)
    {
    	BiTree  ttt = nullptr;
		CreatLogiTree(ttt);
		cout<<"������ϣ�"<<endl;
		bool result = calLogiTree(ttt);
		cout<<"����ǰ���������Ϊ: ";
		PreOrder(ttt,visit);cout<<endl;
		cout<<"��ǰ���������";
		InOrder(ttt,visit);cout<<endl;
		cout<<"��ǰ���������";
		subsequent_order(ttt,visit);cout<<endl;
		cout<<"*******************************************ans1: "<<result<<endl;
		CommuteLogiTree(ttt);
		cout<<"��������߼����ʽ���������";
		PreOrder(ttt,visit);cout<<endl;
		cout<<"�������������";
		InOrder(ttt,visit);cout<<endl;
		cout<<"������������";
		subsequent_order(ttt,visit); cout<<endl;
		cout<<"The result of this Logic expression is: \n";
		result = calLogiTree(ttt);
		cout<<"*****************************************ans2 = "<<result<<endl;
		Destroy(ttt);
	}



	return 0;
}
