#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 1009
#define inf (0x3f3f3f3f)
int n,m;
struct egde {
	int nxt,to,c,f;
}e[N<<1];
struct node {
	int fr,to,c,f;
	node(){fr=to=c=f=0;}
	node(int x,int y,int z,int w){fr=x,to=y,c=z,f=w;}
}a[N];
struct dd {
	int dis,u;
	inline bool operator < (const dd&rhs)const{return dis>rhs.dis;}
	dd(int a,int b){u=a,dis=b;}
};
int head[N],num_edge,dis[N],vis[N];
double ans;
void addedge(int fr,int to,int c,int f) {
	++num_edge;
	e[num_edge].c=c;
	e[num_edge].f=f;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
int dij(int lim) {
	for(int i=1;i<=n;++i)dis[i]=inf,vis[i]=0;
	dis[1]=0;
	priority_queue<dd>q;
	q.push(dd(1,0));
	while(!q.empty()) {
		dd now=q.top();q.pop();
		int u=now.u;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(e[i].f<lim)continue;
			if(dis[v]>dis[u]+e[i].c) {
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])q.push(dd(v,dis[v]));
			}
		}
	}
	return dis[n];
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd(),c=rd(),f=rd();
		addedge(x,y,c,f),addedge(y,x,c,f);
		a[i]=node(x,y,c,f);
	}
	for(int i=1;i<=m;++i)ans=max(ans,1.*a[i].f/dij(a[i].f));
	printf("%d\n",(int)(1000000*ans));
	return 0;
}