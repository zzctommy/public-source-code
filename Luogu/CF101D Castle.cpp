#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
const int N=100005;
int n,siz[N];
LL f[N],g[N];
vector<pair<int,int> >e[N];
bool cmp(const int&a,const int&b){
	return g[a]*siz[b]<g[b]*siz[a];
}
void dfs(int u,int ft){
	siz[u]=1;
	vector<int>t;
	for(pair<int,int>i:e[u]){
		int v=i.y;if(v==ft)continue;
		dfs(v,u),f[u]+=siz[v]*i.x+f[v],siz[u]+=siz[v],g[v]+=i.x*2,g[u]+=g[v],t.pb(v);
	}
	sort(t.begin(),t.end(),cmp);int now=siz[u]-1;
	for(int i:t)f[u]+=g[i]*(now-=siz[i]);
}
signed main(){
	n=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		e[x].pb(mkp(z,y)),e[y].pb(mkp(z,x));
	}
	dfs(1,0),printf("%.13lf\n",1.*f[1]/(n-1));
}