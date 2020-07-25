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
const int N=4000010;
const int M=N*6;
int n,m,k,cnt,a[N];
struct edge {
	int nxt,to;
}e[M];
int head[N],num_edge;
void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
int dfn[N],timer,low[N],scc[N],st[N],top,Col;
void tarjan(int u) {
	dfn[u]=low[u]=++timer,st[++top]=u;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		scc[u]=++Col;
		while(st[top]!=u)scc[st[top--]]=Col;
		--top;
	}
}
//1->n:key
//n+1->2n:not key
//2n+1->3n:pre key
//3n+1->4n:no key pre
signed main() {
	n=rd(),m=rd(),k=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		addedge(x+n,y),addedge(y+n,x);
	}
	for(int i=1;i<=k;++i) {
		for(int j=1,num=rd();j<=num;++j) {
			a[j]=rd();
			addedge(a[j]+3*n,a[j]+n);
			addedge(a[j],a[j]+2*n);
			if(j==1)continue;
			addedge(a[j],a[j-1]+3*n);
			addedge(a[j-1]+2*n,a[j]+n);
			addedge(a[j-1]+2*n,a[j]+2*n);
			addedge(a[j]+3*n,a[j-1]+3*n);
		}
	}
	for(int i=1;i<=(n<<2);++i)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;++i)if(scc[i]==scc[i+n]||scc[i+2*n]==scc[i+3*n])return puts("NIE"),0;
	return puts("TAK"),0;
}