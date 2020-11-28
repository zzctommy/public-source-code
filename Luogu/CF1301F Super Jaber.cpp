#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
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
#define N 1005
#define K 45
int n,m,k,c[N*N],dis[K][N*N];
vector<int>e[N*N],in[K];
#define id(x,y) ((x-1)*m+y)
void bfs(int col){
	static bool pushed[K],vis[N*N];
	memset(pushed,0,sizeof(pushed));
	memset(vis,0,sizeof(vis));
	queue<int>q;
	for(int i:in[col])vis[i]=1,q.push(i);
	pushed[col]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		
		if(!pushed[c[u]]){
			for(int v:in[c[u]])if(!vis[v])vis[v]=1,dis[col][v]=dis[col][u]+1,q.push(v);
			pushed[c[u]]=1;
		}
		for(int v:e[u])
			if(!vis[v])vis[v]=1,dis[col][v]=dis[col][u]+1,q.push(v);
	}
}
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n*m;++i)
		in[c[i]=read()].pb(i);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			if(i>1)e[id(i,j)].pb(id(i-1,j)),e[id(i-1,j)].pb(id(i,j));
			if(i<n)e[id(i,j)].pb(id(i+1,j)),e[id(i+1,j)].pb(id(i,j));
			if(j>1)e[id(i,j)].pb(id(i,j-1)),e[id(i,j-1)].pb(id(i,j));
			if(j<m)e[id(i,j)].pb(id(i,j+1)),e[id(i,j+1)].pb(id(i,j));
		}
	for(int i=1;i<=k;++i)bfs(i);
	for(int q=read();q;--q){
		int r1=read(),c1=read(),r2=read(),c2=read();
		int st=id(r1,c1),ed=id(r2,c2),res=abs(r1-r2)+abs(c1-c2);
		for(int i=1;i<=k;++i)res=min(res,dis[i][st]+dis[i][ed]+1);
		printf("%d\n",res);
	}
	return 0;
}
/*
4 4 8
1 2 2 8
1 3 4 7
5 1 7 6
2 3 8 8
4
1 1 2 2
1 1 3 4
1 1 2 4
1 1 4 4

*/