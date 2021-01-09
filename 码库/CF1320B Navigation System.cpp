#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 200005
int n,m,p[N],k,ans1,ans2;
vector<int>g[N],e[N];
bool vis[N];
int dis[N];
void bfs(int st){
	queue<int>q;
	q.push(st),vis[st]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u])
			if(!vis[v])dis[v]=dis[u]+1,vis[v]=1,q.push(v);
	}
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		g[x].pb(y),e[y].pb(x);
	}
	k=read();
	for(int i=1;i<=k;++i)p[i]=read();
	bfs(p[k]);
	for(int i=1;i<k;++i){
		int cnt=0;
		if(dis[p[i+1]]+1>dis[p[i]])++ans1,++ans2;
		else{
			for(int v:g[p[i]])
				if(dis[v]+1==dis[p[i]])++cnt;
			ans2+=cnt>1;
		}
	}
	printf("%d %d\n",ans1,ans2);
}