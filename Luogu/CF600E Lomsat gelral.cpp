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
const int N=100010;
int n,c[N],mx;
int son[N],siz[N],cnt[N];
LL sum,ans[N];
int num_edge,head[N];
struct edge {
	int nxt,to;
}e[N<<1];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].to=to;
	e[num_edge].nxt=head[from];
	head[from]=num_edge;
}
void dfs1(int u,int ft) {
	siz[u]=1;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void calc(int u,int ft,int sn) {
	++cnt[c[u]];
	if(cnt[c[u]]>mx)sum=c[u],mx=cnt[c[u]];
	else if(cnt[c[u]]==mx)sum+=c[u];
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==sn||v==ft)continue;
		calc(v,u,sn);
	}
}
void clear(int u,int ft) {
	--cnt[c[u]];
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		clear(v,u);
	}
}
void dfs(int u,int ft,int cl) {
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft||v==son[u])continue;
		dfs(v,u,1);
	}
	if(son[u])dfs(son[u],u,0);
	calc(u,ft,son[u]),ans[u]=sum;
	if(cl)clear(u,ft),mx=sum=0;
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)c[i]=rd();
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	dfs1(1,0),dfs(1,0,0);
	for(rint i=1;i<=n;++i)printf("%lld%c",ans[i]," \n"[i==n]);
	return 0;
}