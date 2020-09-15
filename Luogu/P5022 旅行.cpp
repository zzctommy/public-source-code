#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
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
const int N=5005;
int n,m,deg[N];
int head[N],num_edge;
int t[N],tot,ans[N],ban[2],son[N];
int top;
int loop[N],dfn[N],timer,pre[N],loop_cnt;
bool vis[N];
struct edge {
	int nxt,to;
}e[N<<1];
struct node {
	int u,ft;
	node(){u=ft=0;}
	node(int u_,int ft_){u=u_,ft=ft_;}
}stk[N];
inline void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].to=to;
	e[num_edge].nxt=head[fr];
	head[fr]=num_edge;
}
inline void dfs(){
	stk[top=1]=node(1,0),tot=0;
	memset(vis,0,sizeof(vis));
	while(top) {
		node now=stk[top--];
		int u=now.u,ft=now.ft;
		t[++tot]=u,vis[u]=1;
		int len=0;
		for(int i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(v==ft||(u==ban[0]&&v==ban[1])||(u==ban[1]&&v==ban[0])||vis[v])continue;
			son[++len]=v;
		}
		sort(son+1,son+len+1,greater<int>());
		for(int i=1;i<=len;++i)stk[++top]=node(son[i],u);
	}
}
inline void upd() {
	if(tot<n)return;
	for(int i=1;i<=n;++i)
		if(ans[i]<t[i])return;
		else if(ans[i]>t[i])break;
	for(int i=1;i<=n;++i)ans[i]=t[i];
}
void findloop(int u) {
	dfn[u]=++timer;
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==pre[u])continue;
		if(dfn[v]) {
			if(dfn[v]<dfn[u])continue;
			loop[++loop_cnt]=u;
			for(;v!=u;v=pre[v])loop[++loop_cnt]=v;
			
		}else pre[v]=u,findloop(v);
	}
}
signed main() {
	n=rd(),m=rd();
	memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		if(x>y)x^=y^=x^=y;
		addedge(x,y),addedge(y,x);
	}
	if(m<n) dfs(),upd();
	else {
		findloop(1);
		for(int i=1;i<=loop_cnt;++i)
			ban[0]=loop[i],ban[1]=loop[i+1>n?1:i+1],dfs(),upd();
	}
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	return 0;
}
