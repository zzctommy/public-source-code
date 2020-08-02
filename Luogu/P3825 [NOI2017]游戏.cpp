#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int rdc() {
    char ch=getchar();
    while(!isalpha(ch))ch=getchar();
    if(ch<='C')return ch-'A';
    if(ch<='c')return ch-'a';
    return -1;
}
#define fyyAKIOI 50010
const int NJN=fyyAKIOI;
const int N=NJN<<1;
const int M=N<<1;
int n,d,m,mp[NJN],id[10];
int num_edge,head[N];
int scc[N],timer,dfn[N],low[N],Col,stk[N],top;
int f[3][2]={{1,2},{0,2},{0,1}};
struct node {
    int i,x,j,y;
}a[M];
struct edge{
    int nxt,to;
}e[M];
void addedge(int fr,int to) {
    ++num_edge;
    e[num_edge].nxt=head[fr];
    e[num_edge].to=to;
    head[fr]=num_edge;
}
void clear() {
    num_edge=0;
    memset(head,0,sizeof(head));
    memset(scc,0,sizeof(scc));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    Col=0,top=0,timer=0;
}
void tarjan(int u) {
    dfn[u]=low[u]=++timer,stk[++top]=u;
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
        else if(!scc[v])low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]) {
        scc[u]=++Col;
        while(stk[top]!=u)scc[stk[top--]]=Col;
        --top;
    }
}
void solve() {
    clear();
    for(int z=1;z<=m;++z) {
        int i=a[z].i,x=a[z].x,j=a[z].j,y=a[z].y;
        if(x==mp[i])continue;
        int f1=i+n*(f[mp[i]][0]!=x),t1=j+n*(f[mp[j]][0]!=y);
        int f2=f1>n?f1-n:f1+n,t2=t1>n?t1-n:t1+n;
        if(y==mp[j])addedge(f1,f2);
        else addedge(f1,t1),addedge(t2,f2);
    }
    for(int i=1;i<=n*2;++i)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;++i)if(scc[i]==scc[i+n])return;
    for(int i=1;i<=n;++i)putchar('A'+f[mp[i]][scc[i]>scc[i+n]]);
    exit(0);
}
void dfs(int stp) {
    if(stp>d) {
        solve();
        return;
    }
    mp[id[stp]]=0,dfs(stp+1);
    mp[id[stp]]=1,dfs(stp+1);
}
signed main() {
    n=rd(),rd();
    for(int i=1;i<=n;++i) {
        mp[i]=rdc();
        if(mp[i]==-1)id[++d]=i;
    }
    m=rd();
    for(int i=1;i<=m;++i)a[i].i=rd(),a[i].x=rdc(),a[i].j=rd(),a[i].y=rdc();
    dfs(1);puts("-1");return 0;
}