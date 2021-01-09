#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int n,m;
int head[N],num_edge;
bool vis[N],istree[N<<1];
int d[30],dis[N],ans;
struct edge {
	int to,nxt,val;
}e[N<<1];
void addedge(int from,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[from]=num_edge;
}
void build(int u) {
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(vis[v])continue;
		istree[i]=1;
		dis[v]=dis[u]^e[i].val,build(v);
	}
}
void add(int x) {
	for(int i=30;i>=0;--i)
		if(x>>i&1) {
			if(d[i])x^=d[i];
			else {d[i]=x;break;}
		}
}
void dfs(int u) {
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(istree[i])dfs(v);
		else if(u<v)add(dis[u]^dis[v]^e[i].val);
	}
}
void calc() {
	ans=dis[n];
	for(int i=30;i>=0;--i)
		ans=min(ans,ans^d[i]);
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd(),z=rd();
		if(x==y)add(z);
		else addedge(x,y,z),addedge(y,x,z);
	}
	build(1),dfs(1),calc();
	printf("%d\n",ans);
	return 0;
}
