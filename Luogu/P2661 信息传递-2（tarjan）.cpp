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
const int N=2e5+10;
int n,ans=1<<28;
int st[N],top,timer,dfn[N],low[N],scc[N],C;
int num_edge,head[N];
struct edge {
    int to,nxt;
}e[N];
void addedge(int from,int to) {
    ++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
void tarjan(int u) {
	low[u]=dfn[u]=++timer,st[++top]=u;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		scc[u]=++C;int siz=1;
		while(st[top]!=u)scc[st[top--]]=C,++siz;
		--top;
		if(siz>1)ans=min(ans,siz);
	}
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)addedge(i,rd());
	for(rint i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	printf("%d\n",ans);
	return 0;
}
