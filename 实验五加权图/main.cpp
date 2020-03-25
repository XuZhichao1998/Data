#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef int VRtype;  ///
typedef string VertexName; ///顶点名称(标识)的类型
typedef char VertexVal;  ///顶点值（颜色）的类型
struct ArcCell
{
    VRtype adj; ///边权
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
struct Node{    ///节点类型：名称，颜色
    VertexName name;
    VertexVal color;
    void show(int tag=0){
        if(tag)
            cout<<"该顶点信息如下：\n";
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
class UFindSet   ///并查集类
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
class Graph{   ///无向加权图
    public:
    char * record;  ///研究顶点问题时dfs所用的辅助数组
    int MaxVex;  ///最大顶点数
    int NumVex;  ///当前顶点数
    int NumArc;   ///当前边数
    int * dis;  ///Dijkstra时记录节点到原点距离所用的辅助数组
    bool * vis;
    ArcCell ** AdjMatrix; ///邻接矩阵
    Node * vexs; ///用于记录顶点信息的数组指针
    Graph(int maxvex);
    ~Graph();
    long long getMST();
    void InitGraph(); ///输入顶点数，边数...
    int LocateVertex(const VertexName& v); ///返回节点的位置,若不存在返回-1
    void InsertVertex(const Node& v);  ///加点
    bool InsertArc(const string& uu,const string&vv,int val); ///加边
    void RemoveVertex(const VertexName& v); ///删除顶点(矩阵左移上移动)
    void RemoveArc(const VertexName& v1,const VertexName& v2); ///删除两个顶点之间的边
    bool getEdgeval(const VertexName& v1,const VertexName& v2,VRtype & Data);
    void showGraph();
    bool isEmpty(){return NumVex==0;}
    bool isFull(){return NumVex==MaxVex;}
    void showGraphWithcolor();
    void Floyd(); ///求多元最短路，直接用了AdjMatrix，会把原矩阵改掉
    void Dijkstra(int st);
    int calDu(const VertexName& v); ///计算度
    int calDu(int id);
    bool JudgeAllEven();  ///判断顶点度是否均为偶数
    bool hasRightcolor(); ///判断是否有邻接的顶点同色，是：false
    void setColor(); ///
    char getcolor(int x); ///0->'R',  1->'G',  2->'B' ,3->'Y',  4->'P'
    void dfs(int numcolor,int x,bool & isok); ///dfs产生numcolor种颜色，长度为NumVex的全排列
    void Dfs(int numofcolor,bool & isok);
    void SetAG(); ///当做无权图，仅仅为了讨论四色问题,重新输入图，进行涂色的测试
    void inputMatrix(); ///重新输入邻接矩阵
    void TestFourColor(); ///四色问题的检验
    void Clear();  ///清空图
    void showSelection(); ///显示输入提示
    void TestHanshu(); ///测试函数
};

void Graph::showGraphWithcolor()
{
    if(isEmpty())
    {
        cout<<"Empty Graph!"<<endl;
        return;
    }
    cout<<"该无向网共有"<<NumVex<<"个顶点,"<<NumArc<<"条边"<<endl;
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
    cout<<"请输无向网的顶点数，边数： ";
    cin>>NumVex>>x;
    char op[5];
    int flag = 1;
    if(NumVex<=26)
    {
        cout<<"是否以A,B,C,D...给节点命名？Y/N: ";
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
        cout<<"请输入"<<NumVex<<"个顶点的名字(标识),空格隔开："<<endl;
        for(int i=0;i<NumVex;i++)
        {
            cin>>vexs[i].name;
        }
    }
    cout<<"请输入"<<x<<"条边的顶点u,v的名称,边权val"<<endl;
    for(int i=0;i<x;i++)
    {
        cout<<"请输入第"<<i+1<<"条边的顶点u,v的名称,边权val: ";
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
    cout<<"添加边"<<uu<<"---"<<val<<"-->"<<vv<<endl;
    int pos1 = LocateVertex(uu);
    int pos2 = LocateVertex(vv);
    if(pos1==-1||pos2==-1||pos1==pos2)
    {
        cout<<"输入的顶点有误！\n";
        return false;
    }
    if(AdjMatrix[pos1][pos2].adj==INF)
    {
        NumArc++;
        cout<<"添加边成功！"<<endl;
    }
    else
    {
        cout<<"原来边的权值为"<<AdjMatrix[pos1][pos2].adj<<",被"<<val<<"覆盖\n";
    }
    AdjMatrix[pos1][pos2].adj = AdjMatrix[pos2][pos1].adj = val;
    AdjMatrix[pos1][pos2].yes = AdjMatrix[pos2][pos1].yes = true;
    return true;
}

void Graph::RemoveVertex(const VertexName& v) ///删除顶点
{
    int pos = LocateVertex(v);
    if(pos==-1)
    {
        cout<<"要删除的顶点不存在！"<<endl;
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
void Graph::RemoveArc(const VertexName& v1,const VertexName& v2) ///删除两个顶点之间的边
{
    cout<<"删除边操作，将删除"<<v1<<","<<v1<<"之间的边"<<endl;
    int pos1 = LocateVertex(v1);
    int pos2 = LocateVertex(v2);
    if(pos1==-1||pos2==-1)
    {
        cout<<"输入的顶点有误！\n";
        return;
    }
    if(AdjMatrix[pos1][pos2].adj!=INF) NumArc--;
    AdjMatrix[pos1][pos2].adj = AdjMatrix[pos2][pos1].adj = INF;
    cout<<"删除成功！"<<endl;
}
bool Graph::getEdgeval(const VertexName& v1,const VertexName& v2,VRtype & Data)
{
    int pos1 = LocateVertex(v1);
    int pos2 = LocateVertex(v2);
    if(pos1==-1||pos2==-1||pos1==pos2||AdjMatrix[pos1][pos2].yes==false||AdjMatrix[pos1][pos2].adj==INF)
    {
        cout<<"输入的顶点有误！\n";
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
    cout<<"该无向网共有"<<NumVex<<"个顶点,"<<NumArc<<"条边"<<endl;
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
        cout<<"该顶点已经存在！"<<endl;
        return;
    }
    vexs[NumVex++] = v;
    cout<<v.name<<"添加成功！它是第"<<NumVex<<"个顶点"<<endl;
}


void  Graph::Floyd()
    {
        int n = NumVex;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    AdjMatrix[j][k].adj = min(1ll*AdjMatrix[j][k].adj,1ll*AdjMatrix[j][i].adj+AdjMatrix[i][k].adj);
        cout<<"最短路如下:"<<endl;
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
            cout<<"起点"<<vexs[st].name<<"到顶点"<<vexs[i].name<<"的最短距离为"<<dis[i]<<endl;
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
        cout<<"请输入"<<NumVex<<"个顶点的颜色(R,G,B,Y):\n";
        for(int i=0;i<NumVex;i++)
            cin>>vexs[i].color;
        cout<<"设置成功！\n";
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
                cout<<"用"<<numcolor<<"种颜色上色\n";
                cout<<"如下的染色方案可以实现：\n";
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
            cout<<"用"<<numofcolor<<"种颜色不能实现这个四色图！"<<endl;
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
    void Graph::SetAG() ///当做无权图，仅仅为了讨论四色问题
    {
        cout<<"输入顶点数：";
        cin>>NumVex;
        string u,v;
        char op[10];
        for(int i=0;i<MaxVex;i++)
        {
            for(int j=0;j<MaxVex;j++)
            {
                AdjMatrix[i][j] = {INF,false}; ///清零
            }
        }
        cout<<"自动给顶点命名：";
        for(int i=0;i<NumVex;i++)
                op[0] = 'A'+i,op[1]='\0',vexs[i].name=op;
        for(int i=0;i<NumVex;i++)
            cout<<vexs[i].name<<" ";cout<<endl;
        cout<<"连续输入边u,v:(# #结束)\n";
        while(cin>>u>>v)
        {
            if(u=="#"&&v=="#") break;
            int pos1 = LocateVertex(u);
            int pos2 = LocateVertex(v);
            if(pos1==-1||pos2==-1)
            {
                cout<<"没有这个顶点！\n";
                continue;
            }
            AdjMatrix[pos1][pos2] = AdjMatrix[pos2][pos2] = {1,true};
        }
    }
    void Graph:: inputMatrix()
    {
        int x;
        int n = NumVex;
        cout<<"请输入"<<NumVex<<"*"<<NumVex<<"的邻接矩阵: (无边的输入-1)";
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
            cout<<"下面用dfs分别产生颜色种数为2,3,4,5的全排列，如果找到适合的染色方法，就停止。\n";
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
        cout<<"图已经清空！"<<endl;
    }

    void Graph::showSelection()
    {
        cout<<"=============================================================\n";
        cout<<"| 输入+ v         ：添加一个顶点v"<<endl;
        cout<<"| 输入- v         : 删除一个顶点v"<<endl;
        cout<<"| 输入? v         ：检索顶点v"<<endl;
        cout<<"| 输入# v w       ：检索连接顶点v,w的无向边"<<endl;
        cout<<"| 输入！v w       ：删除连接顶点v,w的无向边"<<endl;
        cout<<"| 输入= v w wt    ：添加一条边v,w,权值为wt"<<endl;
        cout<<"| 输入E           ：判断图是否为空  "<<endl;
        cout<<"| 输入F           ：判断图是否为满   "<<endl;
        cout<<"| 输入C           ：清空图  "<<endl;
        cout<<"| 输入Q           ：退出测试程序 "<<endl;
        cout<<"| 输入*           ：清屏"<<endl;
        cout<<"| 输入A           : 再次显示该工具栏"<<endl;
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
                    cout<<"请输入要添加的顶点名称：";
                    cin>>v;
                    InsertVertex({v,getcolor(rand()%4)});
                    break;
                case '-':
                    cout<<"请输入要删除的顶点名称：";
                    cin>>v;
                    RemoveVertex(v);
                    break;
                case '?':
                    cout<<"请输入要检索的顶点名称：";
                    cin>>v;
                    index = LocateVertex(v);
                    if(index==-1)
                    {
                        cout<<"没有这个顶点！"<<endl;
                    }
                    else
                    {
                        vexs[index].show(1);
                    }
                    break;
                case '!':
                    cout<<"请输入要删除边的两个顶点：";
                    cin>>v>>u;
                    RemoveArc(v,u);
                    break;
                case '=':
                    cout<<"请输入要添加边的两个顶点u,v和边权wt：";
                    cin>>u>>v>>wt;
                    InsertArc(u,v,wt);
                    break;
                case '#':
                    cout<<"请输入要检索的边的两个顶点u,v: ";
                    cin>>u>>v;
                    if(getEdgeval(u,v,wt))
                    {
                        cout<<"检索到了这条边：边权为"<<wt<<endl;
                    }
                    else
                    {
                        cout<<"没有这条边"<<endl;
                    }
                    break;

            }
        }

    }
    long long Graph::getMST()
    {
        cout<<"顶点数："<<NumVex<<endl;
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
        cout<<"边数："<<edge.size()<<endl;
        int k=0;
        cout<<"以下是最小生成树的边："<<endl;
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
        cout<<"最小生成树的值为：";
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
    	 cout<<"输入要求最短路的源点："; 
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
    cout<<"输入'*'结束"<<endl;
 //  while(1)
   // {
     //   if(getch()=='*') break;
    //}

    //fclose(stdin);


    return 0;
}
