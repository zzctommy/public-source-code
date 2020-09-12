#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200010;
struct edge {
	int to,nxt,val;
}e[N<<1];
int head[N],num_edge,n,T,ans1,ans2,siz[N];
void addedge(int from,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[from]=num_edge;
}
void dfs1(int u,int ft) {
	siz[u]=1;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]&1)ans1+=e[i].val;
	}
}
void dfs2(int u,int ft) {
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dfs2(v,u);
		ans2+=e[i].val*min(siz[v],n-siz[v]);
	}
}
signed main() {
	T=rd();
	while(T--) {
		n=rd(),n<<=1;ans1=0,ans2=0;
		memset(head,0,sizeof(head));
		num_edge=0;
		for(rint i=1;i<n;++i) {
			int x=rd(),y=rd(),z=rd();
			addedge(x,y,z),addedge(y,x,z);
		}
		dfs1(1,0),dfs2(1,0);
		printf("%lld %lld\n",ans1,ans2);
	}
	return 0;
}