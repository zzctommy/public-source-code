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
const int N=200010;
const int M=400010;
const int inf=2e9;
struct node {
	int u,v,l,a;
}a[M];
bool cmp(const node &a,const node &b) {
	return a.a>b.a;
}
struct edge {
	int nxt,to,val;
}e[M<<1];
int T,n,m,Q,K,S,lastans;
int fa[N<<1],cnt;
int dis[N],vis[N];
int bz[20][N<<1];
int val[N<<1],ans[N<<1];
int head[N<<1],num_edge;
void addedge(int fr,int to,int v=0) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=v;
	head[fr]=num_edge;
}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
struct DIS {
	int u,dis;
	bool operator < (const DIS &rhs)const{return dis>rhs.dis;}
	DIS(){}
	DIS(int a,int b){u=a,dis=b;}
};
void dij() {
	priority_queue<DIS>q;
	for(int i=1;i<=n;++i)dis[i]=inf,vis[i]=0;
	q.push(DIS(1,0)),dis[1]=0;
	while(!q.empty()) {
		DIS now=q.top();q.pop();
		int u=now.u;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].val) {
				dis[v]=dis[u]+e[i].val;
				if(!vis[v])q.push(DIS(v,dis[v]));
			}
		}
	}
}
void dfs(int u) {
	for(int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		dfs(v);
		ans[u]=min(ans[u],ans[v]);
	}
}
void clear_graph(){
	num_edge=0;
	memset(head,0,sizeof(head));
}
void clear() {
	lastans=0;
	cnt=n;
	memset(bz,0,sizeof(bz));
}
void solve() {
	n=rd(),m=rd();
	clear(),clear_graph();
	for(int i=1;i<=m;++i) {
		a[i].u=rd(),a[i].v=rd(),a[i].l=rd(),a[i].a=rd();
		addedge(a[i].u,a[i].v,a[i].l),addedge(a[i].v,a[i].u,a[i].l);
	}
	dij();
	sort(a+1,a+m+1,cmp);
	clear_graph();
	for(int i=1;i<=n*2;++i)fa[i]=i;
	for(int i=1;i<=n;++i)ans[i]=dis[i];
	for(int i=n+1;i<=n*2;++i)ans[i]=inf;
	for(int i=1;i<=m;++i) {
		int fx=find(a[i].u),fy=find(a[i].v);
		if(fx!=fy) {
			++cnt,val[cnt]=a[i].a;
			bz[0][fx]=cnt,bz[0][fy]=cnt;
			fa[fx]=fa[fy]=cnt;
			addedge(cnt,fx),addedge(cnt,fy);
			if(cnt==n*2-1)break;
		}
	}
	for(int i=1;i<=19;++i)
		for(int j=1;j<=2*n-1;++j)
			bz[i][j]=bz[i-1][bz[i-1][j]];
	dfs(cnt);
	Q=rd(),K=rd(),S=rd();
	while(Q--) {
		int v=(rd()+K*lastans-1)%n+1,p=1ll*(1ll*rd()+K*lastans)%(S+1);
		for(int i=19;i>=0;--i)
			if(bz[i][v]&&val[bz[i][v]]>p)v=bz[i][v];
		printf("%d\n",lastans=ans[v]);
	}
}
signed main() {
	T=rd();
	while(T--)solve();
	return 0;
}