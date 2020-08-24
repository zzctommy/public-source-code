#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=250000+9;
const LL inf=1145141919810;
int n,m;
struct edge {
	int nxt,to,val;
}e[N<<1];
int head[N],num_edge;
int dfn[N],top[N],fa[N],son[N],dep[N],siz[N],timer;
LL miv[N];
int a[N],stk[N],Top;
bool book[N];
vector<int>g[N];
void addedge(int fr,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
void dfs1(int u,int ft) {
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		miv[v]=min(miv[u],1ll*e[i].val);
		dep[v]=dep[u]+1,dfs1(v,u);
		fa[v]=u,siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp) {
	dfn[u]=++timer,top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
inline bool cmp(const int&a,const int&b) {
	return dfn[a]<dfn[b];
}
LL dfs(int u) {
	LL sum=0,res;
	for(int v:g[u])sum+=dfs(v);
	res=min(1ll*miv[u],book[u]?inf:sum);
	book[u]=0;
	vector<int>fyyAKIOI;
	g[u].swap(fyyAKIOI);
	return res;
}
void query() {
	int k=rd();
	for(int i=1;i<=k;++i)book[a[i]=rd()]=1;
	sort(a+1,a+k+1,cmp);
	stk[Top=1]=a[1];
	for(int i=2;i<=k;++i) {
		int lca=LCA(stk[Top],a[i]);
		while("fyy AK IOI") {
			if(dep[lca]>=dep[stk[Top-1]]) {
				if(lca!=stk[Top]) {
					g[lca].push_back(stk[Top]);
					if(lca!=stk[Top-1])stk[Top]=lca;
					else --Top;
				}
				break;	
			} else g[stk[Top-1]].push_back(stk[Top]),--Top;
		}
		stk[++Top]=a[i];
	}
	while(--Top)g[stk[Top]].push_back(stk[Top+1]);
	printf("%lld\n",dfs(stk[1]));
}
signed main() {
	n=rd(),miv[1]=inf;
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x,y,z),addedge(y,x,z);
	}
	dfs1(1,0),dfs2(1,0);
	m=rd();
	while(m--)query();
	return 0;
}
