#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=55010;
const int M=N*8;
const int inf=1e8;
int n,m,s,t,sum;
int head[N],num_edge=1;
int dep[N],cur[N],maxflow;
struct edge {
    int nxt,val,to;
}e[M];
void addedge(int from,int to,int val) {
    ++num_edge;
    e[num_edge].nxt=head[from];
    e[num_edge].to=to;
    e[num_edge].val=val;
    head[from]=num_edge;
}
bool bfs(){
    for(rint i=1;i<=t;++i)
        dep[i]=0,cur[i]=head[i];
    dep[s]=1;queue<int>q;q.push(s);
    while(!q.empty()) {
        int u=q.front();q.pop();
        for(rint i=head[u];i;i=e[i].nxt) {
            int v=e[i].to;
            if(!dep[v]&&e[i].val)
                dep[v]=dep[u]+1,q.push(v);
        }
    }
    return dep[t]>0;
}
int dfs(int u,int flow) {
    if(u==t){maxflow+=flow;return flow;}
    int used=0,rlow;
    for(rint i=cur[u];i;i=e[i].nxt) {
        int v=e[i].to;cur[u]=i;
        if(e[i].val&&dep[v]==dep[u]+1) {
            rlow=dfs(v,min(e[i].val,flow-used));
            if(rlow) {
                used+=rlow;
                e[i].val-=rlow;
                e[i^1].val+=rlow;
                if(used==flow)break;
            }
        }
    }
    return used;
}
signed main() {
}