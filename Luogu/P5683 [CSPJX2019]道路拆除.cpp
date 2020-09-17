#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=3005;
int n,m,s1,t1,s2,t2,ans=-1;
int dis[3][N];
bool vis[N];
int head[N],num_edge;
struct edge{
	int nxt,to;
}e[N<<1];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void bfs(int st,int t){
	queue<int>q;
	memset(vis,0,sizeof(vis));
	q.push(st),dis[t][st]=0,vis[st]=1;
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!vis[v])vis[v]=1,q.push(v),dis[t][v]=dis[t][u]+1;
		}
	}
}
signed main() {
	n=read(),m=read();
	for(int i=1;i<=m;++i) {
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	s1=read(),t1=read(),s2=read(),t2=read();
	memset(dis,0x3f,sizeof(dis));
	bfs(1,0),bfs(s1,1),bfs(s2,2);
	for(int i=1;i<=n;++i)
		if(dis[0][i]+dis[1][i]<=t1&&dis[0][i]+dis[2][i]<=t2)ans=max(ans,m-dis[0][i]-dis[1][i]-dis[2][i]);
	printf("%d\n",ans);
	return 0;
}
