#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
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
const int N=20010;
int n,q;
LL G[N];
int fa[19][N],dep[N];
struct xxj {
	LL d[64];
	xxj(){memset(d,0,sizeof(d));}
	void ins(LL x) {
		for(int i=60;i>=0;--i) {
			if(x>>i&1) {
				if(d[i])x^=d[i];
				else {d[i]=x;break;}
			}
		}
	}
	LL ask_max() {
		LL res=0;
		for(int i=60;i>=0;--i)
			if((res^d[i])>res)res^=d[i];
		return res;
	}
	void print() {
		for(int i=0;i<=60;++i)
			if(d[i])printf("%lld ",d[i]);
		puts("");
	}
}bz[19][N];
struct edge {
	int nxt,to;
}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs(int u,int ft) {
	bz[0][u].ins(G[u]);
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		fa[0][v]=u;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
xxj merge(const xxj &a,const xxj &b) {
	xxj res=a;
	for(int i=60;i>=0;--i)
		if(b.d[i])res.ins(b.d[i]);
	return res;
}
void init() {
	dfs(1,0);
	for(int i=1;i<=18;++i)
		for(int j=1;j<=n;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]],bz[i][j]=merge(bz[i-1][j],bz[i-1][fa[i-1][j]]);
}
LL query(int x,int y) {
	xxj res;
	if(dep[x]<dep[y])x^=y^=x^=y;
	int delta=dep[x]-dep[y];
	for(int i=18;i>=0;--i)
		if(delta>>i&1)res=merge(res,bz[i][x]),x=fa[i][x];
	if(x==y){res.ins(G[x]);return res.ask_max();}
	for(int i=18;i>=0;--i)
		if(fa[i][x]!=fa[i][y]) {
			res=merge(res,bz[i][x]);
			res=merge(res,bz[i][y]);
			x=fa[i][x],y=fa[i][y];
		}
	res.ins(G[x]);
	res.ins(G[y]);
	res.ins(G[fa[0][x]]);
	return res.ask_max();
}
signed main() {
	n=rd(),q=rd();
	for(int i=1;i<=n;++i)scanf("%lld",&G[i]);
	for(int i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	init();
	while(q--) {
		int x=rd(),y=rd();
		printf("%lld\n",query(x,y));
	}
	return 0;
}