#include <bits/stdc++.h>
#include "BiTree.h"
/*
	二叉树的创建于三中顺序的遍历：前中后序，递归非递归
	逻辑表达式树
	逻辑表达式运算交换检验
	复制一棵一眼的二叉树
	销毁树 
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
typedef enum{Visit,Travel} TaskType; //访问 和 遍历
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
//函数都写成void的好处是函数原型可以统一，调用过的时候可以函数指针实现
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
				S.push({p->Rchild,Travel}), //最不迫切的任务 遍历右子树
				S.push({p,Visit}),          //访问根节点
				S.push({p->Lchild,Travel}); //遍历左子树
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
				S.push({p,Visit}),  //访问根节点
				S.push({p->Rchild,Travel}), //最不迫切的任务 遍历右子树
				S.push({p->Lchild,Travel}); //遍历左子树

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
		cout<<"这棵树是空树"<<endl;
		return; 
	}
	int Height = getDepth(T);
	vector<int> blank;
	for(int i=Height-1;i>=0;i--)
		blank.push_back((1<<i)-1);
	int nowCent = 0; //当前的层数 
	int cnt = 0; //当前层数已经打印的节点数 
	//i:        0  1  2  3  
	//blanK[i]: 7  3  1  0
	//当前层数i：0,1,2,3,...Height-1
	//当前层首节点要输入的空格数： 2^(Height-1-i)-1 = blanK[i]
	//每层的空格数：blanK[i-1] 
	queue<BiTree> Q; 
	Q.push(T);
	while(!Q.empty())
	{
		BiTree Fr = Q.front();Q.pop();
	//	cout<<"头："; 
		//cout<<Fr->data<<endl; 
		if(cnt==0)  //如果是行的第一个节点，输出前面的空格数 
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
	//	cout<<"删除："<<T->data<<endl;
		delete []T;
		return;
	}
	Destroy(T->Lchild);
	Destroy(T->Rchild);
	//cout<<"删除："<<T->data<<endl;
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
	//if(T->Lchild!=nullptr)    //如果Lchild不空，说明不是非运算，说明可以交换
	if(T->data!='-')
		swap(T->Lchild,T->Rchild);
	CommuteLogiTree(T->Lchild);
	CommuteLogiTree(T->Rchild);
}
int main(void)
{

//	freopen("in.txt","r",stdin);
    BiTree T=nullptr,TT=nullptr;
    cout<<"请输入表达树："<<endl;
	creatTree(T);
	CopyExpressTree(T,TT);
	cout<<"已将表达树T复制为TT"<<endl; 
	cout<<"先序遍历：\n";
	PreOrder(T,visit); cout<<" (T)" <<endl;
	PreOrder(TT,visit); cout<<"(TT)" <<endl;
	cout<<"中序遍历：\n";
	InOrder(T,visit); cout<<"(T)"<<endl;
	InOrder(TT,visit); cout<<"(TT)"<<endl;
	cout<<"后续遍历：\n";
	SubsequentOrder(T,visit);cout<<"(T)"<<endl;
	SubsequentOrder(TT,visit);cout<<"(TT)"<<endl;
	cout<<"非递归先序遍历:"<<endl;
	pre_order(T,visit);cout<<endl;
	cout<<"非递归中序遍历:"<<endl;
	in_order(T,visit);cout<<endl;
	cout<<"非递归后序遍历:"<<endl;
	subsequent_order(T,visit);cout<<endl; 
	cout<<"树的深度为："<<getDepth(T)<<endl;
	printTree(T);
	
	
	int n = 2;
	while(n--)
	{
		BiTree tt=nullptr;
		cout<<"输入算术表达式的前缀表达式："<<endl;
		creatExpreeTree(tt);
		//PreOrder(tt,visit);
		cout<<"The result of this expression is: ";
		cout<<calExpressTree(tt)<<endl<<endl;
		CommuteExpressTree(tt);
		cout<<"交换后的表达式先序遍历：";
		PreOrder(tt,visit);cout<<endl;
		cout<<"交换后的表达式中序遍历：";
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
		cout<<"建树完毕！"<<endl;
		bool result = calLogiTree(ttt);
		cout<<"交换前的先序遍历为: ";
		PreOrder(ttt,visit);cout<<endl;
		cout<<"换前中序遍历：";
		InOrder(ttt,visit);cout<<endl;
		cout<<"换前后序遍历：";
		subsequent_order(ttt,visit);cout<<endl;
		cout<<"*******************************************ans1: "<<result<<endl;
		CommuteLogiTree(ttt);
		cout<<"交换后的逻辑表达式先序遍历：";
		PreOrder(ttt,visit);cout<<endl;
		cout<<"换后中序遍历：";
		InOrder(ttt,visit);cout<<endl;
		cout<<"换后后序遍历：";
		subsequent_order(ttt,visit); cout<<endl;
		cout<<"The result of this Logic expression is: \n";
		result = calLogiTree(ttt);
		cout<<"*****************************************ans2 = "<<result<<endl;
		Destroy(ttt);
	}



	return 0;
}
