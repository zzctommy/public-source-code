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
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
const int N=100005;
int n,k,a[N],ans;
struct edge{int nx,to;}e[N];
int hed[N],et;
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
int dfs(int u){
	int mx=0;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;ckmax(mx,dfs(v));
	}
	//cerr<<u<<' '<<mx<<'\n';
	if(a[u]!=1&&mx==k-1)return ++ans,0;
	return mx+1;
}
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read();
	rep(i,2,n)adde(a[i],i);
	if(a[1]!=1)++ans,a[1]=1;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}