#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=5005;
int n,m,p[N],c[N],d,k[N],ans[N],now,match[N];
bool book[N],vis[N];
vector<int>g[N];
int dfs(int u){
	for(int v:g[u]){
		if(!vis[v]){
			vis[v]=1;
			if(!~match[v]||dfs(match[v])){
				match[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
void work(){
	while(1){
		rep(i,1,m)vis[i]=0;
		if(!dfs(now))break;
		++now;
	}
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)p[i]=read();
	rep(i,1,n)c[i]=read();
	d=read();
	rep(i,1,d)k[i]=read(),book[k[i]]=1;
	memset(match,-1,sizeof(match));
	rep(i,1,n)if(!book[i])g[p[i]].pb(c[i]);
	per(i,d,1){
		work(),ans[i]=now;
		g[p[k[i]]].pb(c[k[i]]);
	}
	rep(i,1,d)printf("%d\n",ans[i]);
	return 0;
}