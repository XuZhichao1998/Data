#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef int VRtype;  ///
typedef string VertexName; ///��������(��ʶ)������
typedef char VertexVal;  ///����ֵ����ɫ��������
struct ArcCell
{
    VRtype adj; ///��Ȩ
    bool yes;
};
struct Edge
{
    int u,v;
    int weight;
    Edge(int u,int v,int we):u(u),v(v),weight(we){}
    bool operator < (const Edge& p)const{
        if(weight!=p.weight) return weight < p.weight;
        if(u!=p.u) return u<p.u;
        return v<p.v;
    }
};
struct Node{    ///�ڵ����ͣ����ƣ���ɫ
    VertexName name;
    VertexVal color;
    void show(int tag=0){
        if(tag)
            cout<<"�ö�����Ϣ���£�\n";
        cout<<name<<"("<<color<<")";
        if(tag) cout<<endl;
    }
    Node(VertexName v,VertexVal ch){
        name = v;
        color = ch;
    }
    Node()
    {
        srand(time(nullptr));
        int x = rand()%4;
        if(x==0) color = 'R';
        else if(x==1) color = 'G';
        else if(x==2) color = 'B';
        else if(x==3) color = 'Y';
        else color = 'P';
    }
};
class UFindSet   ///���鼯��
{
    private:
    int n;
    int * pre;
    public:
    UFindSet(int nn=100)
    {
        n = nn;
        pre = new int[n];
        for(int i=0;i<n;i++)
            pre[i] = i;
    }
    void init(){for(int i=0;i<n;i++) pre[i] = i;}
    int Find(int x)
    {
        return (x==pre[x])?x:pre[x] = Find(pre[x]);
    }
    bool join(int x, int y)
    {
        int fx = Find(x);
        int fy = Find(y);
        if(fx==fy) return false;
        pre[fy] = fx;
        return true;
    }

    ~UFindSet()
    {
        delete[]pre;
    }
};
class Graph{   ///�����Ȩͼ
    public:
    char * record;  ///�о���������ʱdfs���õĸ�������
    int MaxVex;  ///��󶥵���
    int NumVex;  ///��ǰ������
    int NumArc;   ///��ǰ����
    int * dis;  ///Dijkstraʱ��¼�ڵ㵽ԭ��������õĸ�������
    bool * vis;
    ArcCell ** AdjMatrix; ///�ڽӾ���
    Node * vexs; ///���ڼ�¼������Ϣ������ָ��
    Graph(int maxvex);
    ~Graph();
    long long getMST();
    void InitGraph(); ///���붥����������...
    int LocateVertex(const VertexName& v); ///���ؽڵ��λ��,�������ڷ���-1
    void InsertVertex(const Node& v);  ///�ӵ�
    bool InsertArc(const string& uu,const string&vv,int val); ///�ӱ�
    void RemoveVertex(const VertexName& v); ///ɾ������(�����������ƶ�)
    void RemoveArc(const VertexName& v1,const VertexName& v2); ///ɾ����������֮��ı�
    bool getEdgeval(const VertexName& v1,const VertexName& v2,VRtype & Data);
    void showGraph();
    bool isEmpty(){return NumVex==0;}
    bool isFull(){return NumVex==MaxVex;}
    void showGraphWithcolor();
    void Floyd(); ///���Ԫ���·��ֱ������AdjMatrix�����ԭ����ĵ�
    void Dijkstra(int st);
    int calDu(const VertexName& v); ///�����
    int calDu(int id);
    bool JudgeAllEven();  ///�ж϶�����Ƿ��Ϊż��
    bool hasRightcolor(); ///�ж��Ƿ����ڽӵĶ���ͬɫ���ǣ�false
    void setColor(); ///
    char getcolor(int x); ///0->'R',  1->'G',  2->'B' ,3->'Y',  4->'P'
    void dfs(int numcolor,int x,bool & isok); ///dfs����numcolor����ɫ������ΪNumVex��ȫ����
    void Dfs(int numofcolor,bool & isok);
    void SetAG(); ///������Ȩͼ������Ϊ��������ɫ����,��������ͼ������Ϳɫ�Ĳ���
    void inputMatrix(); ///���������ڽӾ���
    void TestFourColor(); ///��ɫ����ļ���
    void Clear();  ///���ͼ
    void showSelection(); ///��ʾ������ʾ
    void TestHanshu(); ///���Ժ���
};

void Graph::showGraphWithcolor()
{
    if(isEmpty())
    {
        cout<<"Empty Graph!"<<endl;
        return;
    }
    cout<<"������������"<<NumVex<<"������,"<<NumArc<<"����"<<endl;
    cout<<"      ";
    for(int i=0;i<NumVex;i++)
        cout<<setw(11)<<vexs[i].name<<"("<<vexs[i].color<<")";cout<<endl;
    for(int i=0;i<NumVex;i++)
    {
        cout<<setw(4)<<vexs[i].name<<"("<<vexs[i].color<<")";
        for(int j=0;j<NumVex;j++)
        {
            if(AdjMatrix[i][j].adj==INF) cout<<setw(12)<<"INF"<<"   ";
            else
                cout<<setw(12)<<AdjMatrix[i][j].adj<<"   ";
        }
        cout<<endl;
    }
}

void showError()
{
    cout<<"Memroy Error!"<<endl;
    exit(-1);
}
Graph::Graph(int maxvex=10)
{
    record = nullptr;
    NumVex = NumArc = 0;
    MaxVex = maxvex;
    if(!(AdjMatrix=new ArcCell*[maxvex])) showError();
    for(int i=0;i<maxvex;i++)
    {
        if(!(AdjMatrix[i] = new ArcCell[maxvex])) showError();
        for(int j=0;j<maxvex;j++)
        {
            AdjMatrix[i][j].adj =  (i!=j)?INF:0;

            AdjMatrix[i][j].yes = (i==j);
        }

    }
    if(!(vexs = new Node[maxvex])) showError();
}
Graph::~Graph()
{
    delete[]vexs;
    for(int i=0;i<MaxVex;i++)
        delete[]AdjMatrix[i];
    delete AdjMatrix;
}

void Graph::InitGraph()
{
    int x;
    cout<<"�����������Ķ������������� ";
    cin>>NumVex>>x;
    char op[5];
    int flag = 1;
    if(NumVex<=26)
    {
        cout<<"�Ƿ���A,B,C,D...���ڵ�������Y/N: ";
        cin>>op;
        if(op[0]=='Y'||op[0]=='y')
        {
            for(int i=0;i<NumVex;i++)
                op[0] = 'A'+i,op[1]='\0',vexs[i].name=op;
        }
        flag = 0;
    }
    if(flag == 1)
    {
        cout<<"������"<<NumVex<<"�����������(��ʶ),�ո������"<<endl;
        for(int i=0;i<NumVex;i++)
        {
            cin>>vexs[i].name;
        }
    }
    cout<<"������"<<x<<"���ߵĶ���u,v������,��Ȩval"<<endl;
    for(int i=0;i<x;i++)
    {
        cout<<"�������"<<i+1<<"���ߵĶ���u,v������,��Ȩval: ";
        string uu,vv;
        int val;
        cin>>uu>>vv>>val;
        InsertArc(uu,vv,val);

    }
}
int Graph:: LocateVertex(const VertexName& v)
{
    for(int i=0;i<NumVex;i++)
        if(vexs[i].name==v) return i;
    return -1;
}
bool Graph::InsertArc(const string& uu,const string& vv,int val)
{
    cout<<"��ӱ�"<<uu<<"---"<<val<<"-->"<<vv<<endl;
    int pos1 = LocateVertex(uu);
    int pos2 = LocateVertex(vv);
    if(pos1==-1||pos2==-1||pos1==pos2)
    {
        cout<<"����Ķ�������\n";
        return false;
    }
    if(AdjMatrix[pos1][pos2].adj==INF)
    {
        NumArc++;
        cout<<"��ӱ߳ɹ���"<<endl;
    }
    else
    {
        cout<<"ԭ���ߵ�ȨֵΪ"<<AdjMatrix[pos1][pos2].adj<<",��"<<val<<"����\n";
    }
    AdjMatrix[pos1][pos2].adj = AdjMatrix[pos2][pos1].adj = val;
    AdjMatrix[pos1][pos2].yes = AdjMatrix[pos2][pos1].yes = true;
    return true;
}

void Graph::RemoveVertex(const VertexName& v) ///ɾ������
{
    int pos = LocateVertex(v);
    if(pos==-1)
    {
        cout<<"Ҫɾ���Ķ��㲻���ڣ�"<<endl;
        return;
    }
    for(int i=pos+1;i<NumVex;i++)
        vexs[i-1] = vexs[i];
    for(int i=pos+1;i<NumVex;i++)
    {
        for(int j=0;j<NumVex;j++)
            AdjMatrix[i-1][j] = AdjMatrix[i][j];
    }
    for(int j=pos+1;j<NumVex;j++)
    {
        for(int i=0;i<NumVex;i++)
            AdjMatrix[i][j-1] = AdjMatrix[i][j];
    }
    NumVex--;

}
void Graph::RemoveArc(const VertexName& v1,const VertexName& v2) ///ɾ����������֮��ı�
{
    cout<<"ɾ���߲�������ɾ��"<<v1<<","<<v1<<"֮��ı�"<<endl;
    int pos1 = LocateVertex(v1);
    int pos2 = LocateVertex(v2);
    if(pos1==-1||pos2==-1)
    {
        cout<<"����Ķ�������\n";
        return;
    }
    if(AdjMatrix[pos1][pos2].adj!=INF) NumArc--;
    AdjMatrix[pos1][pos2].adj = AdjMatrix[pos2][pos1].adj = INF;
    cout<<"ɾ���ɹ���"<<endl;
}
bool Graph::getEdgeval(const VertexName& v1,const VertexName& v2,VRtype & Data)
{
    int pos1 = LocateVertex(v1);
    int pos2 = LocateVertex(v2);
    if(pos1==-1||pos2==-1||pos1==pos2||AdjMatrix[pos1][pos2].yes==false||AdjMatrix[pos1][pos2].adj==INF)
    {
        cout<<"����Ķ�������\n";
        return false;
    }
    Data = AdjMatrix[pos1][pos2].adj;
    return true;
}

void Graph::showGraph()
{
    if(isEmpty())
    {
        cout<<"Empty Graph!"<<endl;
        return;
    }
    cout<<"������������"<<NumVex<<"������,"<<NumArc<<"����"<<endl;
    cout<<"      ";
    for(int i=0;i<NumVex;i++)
        cout<<setw(11)<<vexs[i].name;cout<<endl;
    for(int i=0;i<NumVex;i++)
    {
        cout<<setw(6)<<vexs[i].name;
        for(int j=0;j<NumVex;j++)
        {
            //if(AdjMatrix[i][j].yes==false&&i!=j) cout<<setw(11)<<"INF";
            if(AdjMatrix[i][j].adj==INF) cout<<setw(11)<<"INF";
            else
                cout<<setw(11)<<AdjMatrix[i][j].adj;
        }
        cout<<endl;
    }
}

void Graph::InsertVertex(const Node& v)
{
    if(LocateVertex(v.name)!=-1)
    {
        cout<<"�ö����Ѿ����ڣ�"<<endl;
        return;
    }
    vexs[NumVex++] = v;
    cout<<v.name<<"��ӳɹ������ǵ�"<<NumVex<<"������"<<endl;
}


void  Graph::Floyd()
    {
        int n = NumVex;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    AdjMatrix[j][k].adj = min(1ll*AdjMatrix[j][k].adj,1ll*AdjMatrix[j][i].adj+AdjMatrix[i][k].adj);
        cout<<"���·����:"<<endl;
        showGraph();

    }
    void Graph:: Dijkstra(int st)
    {
        int n = NumVex;
        dis = new int[MaxVex];
        vis = new bool[MaxVex];
        for(int i=0;i<NumVex;i++)
            vis[i] = 0,dis[i] = AdjMatrix[st][i].adj;
        vis[st] = true;
        dis[st] = 0;
        int Mindis,p=-1;
        for(int i=0;i<n;i++)
        {
            p = -1;
            Mindis = INF;
            for(int j=0;j<n;j++)
            {
                if(!vis[j]&&dis[j]<Mindis) p = j,Mindis = dis[j];
            }
            if(p==-1) break;
            vis[p] = true;
            for(int j=0;j<n;j++)
            {
                if(!vis[j]&&1ll*dis[j]>1ll*dis[p]+AdjMatrix[p][j].adj)
                {
                    dis[j] = dis[p]+AdjMatrix[p][j].adj;
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            cout<<"���"<<vexs[st].name<<"������"<<vexs[i].name<<"����̾���Ϊ"<<dis[i]<<endl;
        }
        delete[]vis;
        delete[]dis;
    }
    bool Graph:: hasRightcolor()
    {
        for(int i=0;i<NumVex;i++)
        {
            for(int j=i+1;j<NumVex;j++)
            {
                if(AdjMatrix[i][j].yes==true&&vexs[i].color==vexs[j].color) return false;
            }
        }
        return true;
    }
    void Graph:: setColor()
    {
        showGraph();
        cout<<"������"<<NumVex<<"���������ɫ(R,G,B,Y):\n";
        for(int i=0;i<NumVex;i++)
            cin>>vexs[i].color;
        cout<<"���óɹ���\n";
    }


    char Graph:: getcolor(int x)
    {
        switch(x)
        {
            case 0: return 'R';
            case 1: return 'G';
            case 2: return 'B';
            case 3: return 'Y';
            case 4: return 'P';
            default: return 'H';
        }
    }
    void Graph:: dfs(int numcolor,int x,bool & isok)
    {
        if(isok) return;
        if(x==NumVex)
        {
            for(int i=0;i<NumVex;i++)
                vexs[i].color = record[i];
            if(hasRightcolor())
            {
                cout<<"��"<<numcolor<<"����ɫ��ɫ\n";
                cout<<"���µ�Ⱦɫ��������ʵ�֣�\n";
                showGraphWithcolor();
                isok = true;
            }
            return;
        }
        for(int i=0;i<numcolor;i++)
        {
            record[x] = getcolor(i);
            dfs(numcolor,x+1,isok);
        }
    }
    void Graph::Dfs(int numofcolor,bool & isok)
    {
        record = new char[NumVex];
        isok = false;
        dfs(numofcolor,0,isok);
        if(!isok)
        {
            cout<<"��"<<numofcolor<<"����ɫ����ʵ�������ɫͼ��"<<endl;
        }
        delete[] record;
    }
    int Graph:: calDu(const VertexName& v)
    {
        int id = LocateVertex(v);
        if(id==-1) return -1;
        int ans = 0;
        for(int i=0;i<NumVex;i++)
        {
            if(i==id) continue;
            if(AdjMatrix[id][i].yes) ans++;
        }
        return ans;
    }
    int Graph:: calDu(int id)
    {
        if(id==-1||id>=NumVex) return -1;
        int ans = 0;
        for(int i=0;i<NumVex;i++)
        {
            if(i==id) continue;
            if(AdjMatrix[id][i].yes) ans++;
        }
        return ans;
    }
    bool Graph:: JudgeAllEven()
    {
        for(int i=0;i<NumVex;i++)
        {
            if(calDu(i)%2) return false;
        }
        return true;
    }
    void Graph::SetAG() ///������Ȩͼ������Ϊ��������ɫ����
    {
        cout<<"���붥������";
        cin>>NumVex;
        string u,v;
        char op[10];
        for(int i=0;i<MaxVex;i++)
        {
            for(int j=0;j<MaxVex;j++)
            {
                AdjMatrix[i][j] = {INF,false}; ///����
            }
        }
        cout<<"�Զ�������������";
        for(int i=0;i<NumVex;i++)
                op[0] = 'A'+i,op[1]='\0',vexs[i].name=op;
        for(int i=0;i<NumVex;i++)
            cout<<vexs[i].name<<" ";cout<<endl;
        cout<<"���������u,v:(# #����)\n";
        while(cin>>u>>v)
        {
            if(u=="#"&&v=="#") break;
            int pos1 = LocateVertex(u);
            int pos2 = LocateVertex(v);
            if(pos1==-1||pos2==-1)
            {
                cout<<"û��������㣡\n";
                continue;
            }
            AdjMatrix[pos1][pos2] = AdjMatrix[pos2][pos2] = {1,true};
        }
    }
    void Graph:: inputMatrix()
    {
        int x;
        int n = NumVex;
        cout<<"������"<<NumVex<<"*"<<NumVex<<"���ڽӾ���: (�ޱߵ�����-1)";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
              {
                  cin>>x;
                  if(i==j) AdjMatrix[i][j] = {0,true};
                  else if(x<0) AdjMatrix[i][j] ={INF,false};
                  else AdjMatrix[i][j] =  {x,true};
              }
        }
    }
    void Graph:: TestFourColor()
    {

            SetAG();
            cout<<"������dfs�ֱ������ɫ����Ϊ2,3,4,5��ȫ���У�����ҵ��ʺϵ�Ⱦɫ��������ֹͣ��\n";
            for(int i=2;i<=5;i++)
            {
                bool isok = false;
                Dfs(i,isok);
                if(isok) return;
            }

    }
    void Graph::Clear()
    {
        NumVex = NumArc = 0;
        for(int i=0;i<MaxVex;i++)
        {
            for(int j=0;j<MaxVex;j++)
            {
                AdjMatrix[i][j].adj = (i==j)?0:INF;
                AdjMatrix[i][j].yes = (i==j);
            }
        }
        cout<<"ͼ�Ѿ���գ�"<<endl;
    }

    void Graph::showSelection()
    {
        cout<<"=============================================================\n";
        cout<<"| ����+ v         �����һ������v"<<endl;
        cout<<"| ����- v         : ɾ��һ������v"<<endl;
        cout<<"| ����? v         ����������v"<<endl;
        cout<<"| ����# v w       ���������Ӷ���v,w�������"<<endl;
        cout<<"| ���룡v w       ��ɾ�����Ӷ���v,w�������"<<endl;
        cout<<"| ����= v w wt    �����һ����v,w,ȨֵΪwt"<<endl;
        cout<<"| ����E           ���ж�ͼ�Ƿ�Ϊ��  "<<endl;
        cout<<"| ����F           ���ж�ͼ�Ƿ�Ϊ��   "<<endl;
        cout<<"| ����C           �����ͼ  "<<endl;
        cout<<"| ����Q           ���˳����Գ��� "<<endl;
        cout<<"| ����*           ������"<<endl;
        cout<<"| ����A           : �ٴ���ʾ�ù�����"<<endl;
        cout<<"=============================================================\n";
    }
    void Graph::TestHanshu()
    {
        showSelection();
        char op;
        char str[10];
        VertexName v,u;
        int wt,index;
        bool ok=true;
        while(ok)
        {
            cin>>str;
            op = str[0];
            switch(op)
            {
                case 'A':case 'a':showSelection();break;
                case 'Q':case 'q':ok = false;break;
                case 'C':case 'c':Clear();break;
                case 'S':         showGraph();break;
                case 's':         showGraphWithcolor();break;
                case '*': system("CLS");break;
                case 'E':case 'e':
                    if(isEmpty())
                    {
                        cout<<"Yes, is Empty\n";
                    }
                    else cout<<"No, not Empty\n";
                    break;
                case 'F':case 'f':
                    if(isFull())
                    {
                        cout<<"Yes, is Full\n";
                    }
                    else cout<<"No, not Full\n";
                    break;
                case '+':
                    cout<<"������Ҫ��ӵĶ������ƣ�";
                    cin>>v;
                    InsertVertex({v,getcolor(rand()%4)});
                    break;
                case '-':
                    cout<<"������Ҫɾ���Ķ������ƣ�";
                    cin>>v;
                    RemoveVertex(v);
                    break;
                case '?':
                    cout<<"������Ҫ�����Ķ������ƣ�";
                    cin>>v;
                    index = LocateVertex(v);
                    if(index==-1)
                    {
                        cout<<"û��������㣡"<<endl;
                    }
                    else
                    {
                        vexs[index].show(1);
                    }
                    break;
                case '!':
                    cout<<"������Ҫɾ���ߵ��������㣺";
                    cin>>v>>u;
                    RemoveArc(v,u);
                    break;
                case '=':
                    cout<<"������Ҫ��ӱߵ���������u,v�ͱ�Ȩwt��";
                    cin>>u>>v>>wt;
                    InsertArc(u,v,wt);
                    break;
                case '#':
                    cout<<"������Ҫ�����ıߵ���������u,v: ";
                    cin>>u>>v;
                    if(getEdgeval(u,v,wt))
                    {
                        cout<<"�������������ߣ���ȨΪ"<<wt<<endl;
                    }
                    else
                    {
                        cout<<"û��������"<<endl;
                    }
                    break;

            }
        }

    }
    long long Graph::getMST()
    {
        cout<<"��������"<<NumVex<<endl;
        long long ans = 0;
        set<Edge> edge;
        for(int i=0;i<NumVex;i++)
        {
            for(int j=i+1;j<NumVex;j++)
            {
                if(AdjMatrix[i][j].adj!=INF)
                {
                    edge.insert(Edge(i,j,AdjMatrix[i][j].adj));
                }
            }
        }
        UFindSet ufset(NumVex+3);
        set<Edge>::iterator it;
        cout<<"������"<<edge.size()<<endl;
        int k=0;
        cout<<"��������С�������ıߣ�"<<endl;
        for(it = edge.begin();k<NumVex-1&& it!=edge.end(); ++it)
        {
            int uu = it->u;
            int vv = it->v;
            int ww = it->weight;
            cout<<vexs[uu].name<<" "<<vexs[vv].name<<" : "<<ww<<endl;
            if(ufset.join(uu,vv))
            {
                //cout<<ww<<"("<<uu<<","<<vv<<")"<<endl;
                ans+=ww,k++;
            }
        }
        cout<<"��С��������ֵΪ��";
        cout<<"ans = "<<ans<<endl;
        return ans;
    }
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Graph * p = new Graph(20);
    p->showGraph();
   
    p->InitGraph();
    p->showGraph();
    string nn;
    while(1)
    {
    	 cout<<"����Ҫ�����·��Դ�㣺"; 
    	cin>>nn;
    	if(p->LocateVertex(nn)!=-1) break;
	}
   
    p->Dijkstra( p->LocateVertex(nn));
    p->Floyd();
    cout<<"MST!\n";
    p->getMST();
     p->showGraphWithcolor(); 
    p->TestFourColor();
    p->TestFourColor();
    p->TestHanshu();
    delete p;
    cout<<"����'*'����"<<endl;
 //  while(1)
   // {
     //   if(getch()=='*') break;
    //}

    //fclose(stdin);


    return 0;
}
