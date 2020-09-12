#include<bits/stdc++.h>
using namespace std;
inline int rd(){
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=100009;
const int K=105;
int n,m,k,S,a[N],dis[K][N];
int vis[N];
struct edge {
	int nxt,to;
}e[N<<1];
int head[N],num_edge;
inline void addedge(int fr,int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
struct node {
	int u,dis;
	node(){u=dis=0;}
	node(int u_,int dis_){u=u_,dis=dis_;}
};
void bfs(int t) {
	queue<node>q;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;++i)if(a[i]==t)q.push(node(i,0)),vis[i]=1;
	while(!q.empty()) {
		node now=q.front();q.pop();
		int u=now.u,d=now.dis;
		dis[t][u]=d;
		for(int i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(!vis[v])vis[v]=1,q.push(node(v,d+1));
		}
	}
}
signed main() {
	n=rd(),m=rd(),k=rd(),S=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		addedge(x,y),addedge(y,x);
	}
	for(int i=1;i<=k;++i)bfs(i);
	for(int i=1;i<=n;++i) {
		long long res=0;
		priority_queue<int,vector<int>,greater<int> >pq;
		for(int j=1;j<=k;++j)pq.push(dis[j][i]);
		for(int j=1;j<=S;++j)res+=pq.top(),pq.pop();
		printf("%lld ",res);
	}
	return 0;
}