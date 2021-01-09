#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200005;
const int M = 5000005;
int n,m,a,b;
int head[N], num_edge;
int ans[2];
bool vis[N];
struct edge {
	int nxt, to;
}e[M<<1];
void addedge(int fr, int to) {
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void bfs(int st,int ban,int o) {
	for (int i = 1; i <= n; ++ i) vis[i] = 0;
	queue<int>q;
	q.push(st),vis[st]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i =head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==ban)continue;
			if(!vis[v])vis[v]=1,q.push(v);
		}
	}
	ans[o]=0;
	for (int i = 1; i <= n; ++ i) ans[o] += ! vis[i];
	--ans[o];
}
void Main() {
	n = read(), m = read(), a = read(), b = read();
	for (int i = 1; i <= n; ++ i) head[i] = 0;
	num_edge=0;
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	bfs(a,b,0),bfs(b,a,1);
	printf("%lld\n",ans[0]*ans[1]);
}
signed main(){
	for(int T=read();T; -- T) Main();
}