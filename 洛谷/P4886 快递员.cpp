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
const int N=1e5+10;
int n,m,ans=1<<30;
struct edge {
	int nxt,val,to;
}e[N<<1];
int head[N],num_edge;
int mx[N],root,siz[N];
int a[N],X[N],Y[N],dis[N],bel[N];
bool used[N];
void addedge(int from,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[from]=num_edge;
}
void getroot(int u,int ft,int totsize) {
	siz[u]=1,mx[u]=0;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft||used[v])continue;
		getroot(v,u,totsize);
		siz[u]+=siz[v];
		mx[u]=max(mx[u],siz[v]);
	}
	mx[u]=max(mx[u],totsize-siz[u]);
	if(mx[u]<mx[root])root=u;
}
void dfs(int u,int ft,int rt) {
	bel[u]=rt;
	for(rint i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==ft)continue;
		dis[v]=dis[u]+e[i].val;
		dfs(v,u,rt);
	}
}
void solve(int x) {
	if(used[x]){printf("%d\n",ans);exit(0);}
	used[x]=1;dis[x]=0;
	for(rint i=head[x];i;i=e[i].nxt) {
		int v=e[i].to;
		dis[v]=dis[x]+e[i].val,dfs(v,x,v);
	}
	int Mx=0,tr=0;
	for(rint i=1;i<=m;++i)
		if(dis[X[i]]+dis[Y[i]]>Mx)Mx=dis[X[i]]+dis[Y[i]],a[a[0]=1]=i;
		else if(Mx==dis[X[i]]+dis[Y[i]])a[++a[0]]=i;
	ans=min(ans,Mx);
	for(rint i=1;i<=a[0];++i) {
		if(bel[X[a[i]]]!=bel[Y[a[i]]]) {printf("%d\n",ans);exit(0);}
		if(!tr)tr=bel[X[a[i]]];
		else if(tr!=bel[X[a[i]]]||tr!=bel[Y[a[i]]]) {printf("%d\n",ans);exit(0);}
	}
	root=0,getroot(tr,x,siz[tr]),solve(root);
}
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<n;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x,y,z),addedge(y,x,z);
	}
	for(rint i=1;i<=m;++i)X[i]=rd(),Y[i]=rd();
	mx[root=0]=n,getroot(1,0,n),solve(root);
}
