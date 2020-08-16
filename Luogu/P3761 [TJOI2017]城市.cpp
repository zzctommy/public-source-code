#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=5010;
const int inf=1000000007;
struct edge{
    int nxt,to,val;
}e[N<<1];
int n,ans=inf;
int head[N],num_edge;
vector<int>d,w;
void addedge(int fr,int to,int val) {
    ++num_edge,
    e[num_edge].nxt=head[fr],
    e[num_edge].to=to,
    e[num_edge].val=val,
    head[fr]=num_edge;
}
int f[N],ff[N],g[N],gg[N],S,T,res;
void dfs(int u,int ft,int&res) {
    ff[u]=u,gg[u]=u;
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(v==ft)continue;
        dfs(v,u,res);
        if(f[v]+e[i].val>=f[u])g[u]=f[u],gg[u]=ff[u],f[u]=f[v]+e[i].val,ff[u]=ff[v];
        else if(f[v]+e[i].val>g[u])g[u]=f[v]+e[i].val,gg[u]=ff[v];
        if(f[u]+g[u]>res)res=f[u]+g[u],S=ff[u],T=gg[u];
    }
}
int dfsd(int u,int ft,int tar) {
    if(u==tar) {d.pb(u);return 1;}
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(v==ft)continue;
        if(dfsd(v,u,tar)) {d.pb(u),w.pb(e[i].val);return 1;}
    }
    return 0;
}
void dfsr(int u,int ft,int&dis,int tp) {
    dis=min(dis,max(tp,f[u]));
    for(int i=head[u];i;i=e[i].nxt) {
        int v=e[i].to;
        if(v==ft)continue;
        dfsr(v,u,dis,e[i].val+max(f[v]+e[i].val==f[u]?g[u]:f[u],tp));
    }
}
void clear() {
    res=0;
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
}
signed main() {
    n=rd();
    for(int i=1;i<n;++i) {
        int x=rd(),y=rd(),z=rd();
        addedge(x,y,z),addedge(y,x,z);
    }
    dfs(1,0,res),dfsd(S,0,T);
    for(uint i=0;i<d.size()-1;++i) {
        int x=d[i],y=d[i+1],r1=inf,r2=inf,d1=0,d2=0;
        clear(),dfs(x,y,d1),dfsr(x,y,r1,0);if(r1+w[i]>ans)continue;
        clear(),dfs(y,x,d2),dfsr(y,x,r2,0),ans=min(ans,max(max(d1,d2),r1+r2+w[i]));
    }
    printf("%d\n",ans);
    return 0;
}