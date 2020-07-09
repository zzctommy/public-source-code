#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=100010;
const int M=200010;
int n,m,ans;
int timer,low[N],dfn[N],st[N],top,scc[N],C;
int num_edge=1,head[N];
struct edge {
    int to,nxt;
}e[M<<1];
void addedge(int from,int to) {
    ++num_edge,e[num_edge].nxt=head[from],e[num_edge].to=to,head[from]=num_edge;
    ++num_edge,e[num_edge].nxt=head[to],e[num_edge].to=from,head[to]=num_edge;
}
void tarjan(int u,int ft) {
    low[u]=dfn[u]=++timer,st[++top]=u;
    int flg=0;
    for(rint i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(v==ft&&!flg){flg=1;continue;}
        if(!dfn[v])tarjan(v,u),low[u]=min(low[u],low[v]);
        else if(!scc[v])low[u]=min(low[u],dfn[v]);
        if(dfn[u]<low[v])++ans;
    }
    if(low[u]==dfn[u]) {
        scc[u]=++C;
        while(st[top]!=u)scc[st[top--]]=C;
        --top;
    }
}
signed main() {
    n=rd(),m=rd();
    for(rint i=1;i<=m;++i)addedge(rd(),rd());
    for(rint i=1;i<=n;++i)if(!dfn[i])tarjan(i,i);
    printf("%d\n",ans);return 0;
}
