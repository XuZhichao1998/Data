#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
char s[maxn];
char suffix[maxn];
bool bracketMatching(char *s);
stack<double> Operand;
stack<char> Operator;
int val[300]; //����������ջ�е����ȼ�
void init()
{
	val['#'] = -1;
	val['('] = 0;
	val['+'] = 1;
	val['-'] = 1;
	val[')'] = 2;
	val['*'] = 2;
	val['/'] = 2;
}
const double decimal[10] = {0,0.1,0.01,0.001,0.0001,0.00001,0.000001,0.0000001};
double getDouble(char* s,int & index,int len)   //�������֣�ʵ�ֶ�λ���Ķ���
{
	double ans = 0;
	int flag = 1,cnt=0;
	//cout<<"�������֣�index = "<<index<<endl;
	while(s[index]==' ') index++;
	index--;
	while(index<len)
	{
		index++;
		if((s[index]>='0'&&s[index]<='9'))
		{
			if(flag)
				ans = ans * 10 + s[index]-'0';
			else ans += decimal[++cnt];
		}
		else if(s[index]=='.')
		{
			flag = 0;
		}
		else
		{
			//cout<<"����index = "<<index<<endl;
			return ans;
		}
	}
	return ans;
}
bool isOperator(char ch)
{
	return (ch=='+'||ch=='-'||ch=='*'||ch=='/');
}
double cal(double n1,double n2,char ch,bool& flag)   //���������������Ľ��
{
	flag = 1;
//	cout<<n1<<" "<<ch<<" "<<n2<<" = ";
	switch(ch)
	{
		case '+':
			return n1+n2;
		case '-':
			return n1-n2;
		case '/':
			if(n2==0)
			{
				flag = 0;
				return -1;
			}
			return n1/n2;
		default:
			return n1*n2;
	}
	return 0;
}
bool popAndCal(char ch)    //��������ջ���Σ����������ջ
{
	double n2 = Operand.top();
	Operand.pop();
	double n1 = Operand.top();
	Operand.pop();
	bool flag;
	double Num = cal(n1,n2,ch,flag);
	if(!flag)
	{
		cout<<"Can't divide zero!\n RunTime Error\n";
		return -1;	//����0
	}
	//cout<<Num<<endl;
	Operand.push(Num);
	return 1;
}



double calPostfix(char * s)   //�����׺���ʽ
{
	while(!Operand.empty()) Operand.pop();   //������
	while(!Operator.empty()) Operator.pop(); //�����
	Operator.push('#');
	int len = strlen(s);
	double getNum=0;
	for(int i=0; i<len; i++)
	{
		if(isdigit(s[i]))
		{
			getNum = getDouble(s,i,len);
			//cout<<"��������Ϊ��"<<getNum<<endl;
			Operand.push(getNum);
			i--;
		}
		else if(isOperator(s[i]))
		{
			if(popAndCal(s[i])==-1)
			{
				return -1;
			}
		}
	}
	return Operand.top();
}/*
double calMidfix(char * s)  //�˺�ʵ��ֱ�Ӽ�����׺���ʽ
{
	int len = strlen(s);
	while(!Operand.empty()) Operand.pop();   //������
	while(!Operator.empty()) Operator.pop(); //�����
	Operator.push('#');
	double Num=0;
	double getNum=0;
	for(int i=0;i<len;i++)
	{
		if(isdigit(s[i]))
		{
			getNum = getDouble(s,i,len);
			cout<<"��������Ϊ��"<<getNum<<endl;
			Operand.push(getNum);
			i--;
		}
		else if(isOperator(s[i]))
		{
			while(val[s[i]]<=val[Operator.top()])
			{

			}
		}
		else if(s[i]=='(')
		{
			Operator.push("(");
		}
		else if(s[i]==')')
		{

		}
	}
	return Operand.top();
}*/
//1 * 2 + (4 - 6 / 3 )* 9
void getPostfix(char * s )    //�˺�������׺���ʽת�����˺�׺���ʽ
{
	while(!Operator.empty()) Operator.pop();
	Operator.push('#');
	int len = strlen(s);
	int cnt = 0;
	for(int i=0; i<len; i++)
	{
		//	cout<<"i = "<<i<<endl;
		if(!isOperator(s[i])&&s[i]!='('&&s[i]!=')')
		{
			if(i>0&&!isdigit(s[i-1])) suffix[cnt++] = ' ';
			suffix[cnt++] = s[i];
			continue;
		}
		else if(s[i]=='(')
		{
			Operator.push(s[i]);
		}
		else if(s[i]==')')
		{
			while(!Operator.empty()&&Operator.top()!='(')
			{
				//cout<<"ջ��Ϊ��"<<Operator.top()<<endl;
				suffix[cnt++] = Operator.top();
				Operator.pop();
			}
			Operator.pop();
		}
		else
		{
			//cout<<"s[i] = "<<s[i]<<endl;
			while(!Operator.empty()&&val[(int)Operator.top()]>=val[(int)s[i]])
			{
				//cout<<"ջ��Ϊ��"<<Operator.top()<<endl;
				suffix[cnt++] = Operator.top();
				Operator.pop();
			}
			Operator.push(s[i]);
		}
	}
	while(Operator.top()!='#')
	{
		suffix[cnt++] = Operator.top();
		Operator.pop();
	}
	suffix[cnt] = '\0';
	//cout<<"����"<<endl;
}
int main()
{
	//freopen("in.txt","r",stdin);
	double ans;
	init();
	while(cin.getline(s,200))
	{
		bool isMatching = bracketMatching(s);
		if(!isMatching)
		{
			printf("%s ��ƥ��\n",s);
			continue;
		}
		//ans = calPostfix(s);

		//	cout<<"ans = "<<ans<<endl;
		getPostfix(s);
		cout<<"ת��Ϊ��׺���ʽ��Ϊ�� "<<suffix<<endl;
		cout<<calPostfix(suffix)<<endl;

	}




	return 0;
}
bool bracketMatching(char *s)   //�������ƥ��
{
	stack<char> a;
	int len = strlen(s);
	for(int i=0; i<len; i++)
	{
		if(s[i]=='('||s[i]=='['||s[i]=='{')
		{
			a.push(s[i]);
		}
		else if(s[i]==')')
		{
			if(a.empty()) return false;
			if(a.top()=='(')
			{
				a.pop();
			}
			else return false;
		}
		else if(s[i]=='}')
		{
			if(a.empty()) return false;
			if(a.top()=='{')
			{
				a.pop();
			}
			else return false;
		}
		else if(s[i]==']')
		{
			if(a.empty()) return false;
			if(a.top()=='[')
			{
				a.pop();
			}
			else return false;
		}
	}
	if(!a.empty()) return false;
	return true;
}
