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
const int N=500005;
int n;
db q[N],f[N],g[N],ans;
int et,hed[N];
struct edge{int nx,to;db vl;}e[N<<1];
void adde(int u,int v,db d){e[++et].nx=hed[u],e[et].to=v,e[et].vl=d,hed[u]=et;}
void dfs1(int u,int ft){
	f[u]=1-q[u];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u),f[u]*=f[v]*e[i].vl+1-e[i].vl;
	}
}
void dfs2(int u,int ft){
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		db tmp=f[v]*e[i].vl+1-e[i].vl,P=g[u]/tmp;
		if(tmp>1e-8)g[v]=f[v]*(e[i].vl*P+1-e[i].vl);
		dfs2(v,u);
	}
}
signed main(){
	n=read();
	rep(i,2,n){
		int x=read(),y=read(),z=read();db d=1.*z/100;
		adde(x,y,d),adde(y,x,d);
	}
	rep(i,1,n)q[i]=1.*read()/100;
	dfs1(1,0),g[1]=f[1],dfs2(1,0);
	rep(i,1,n)ans+=1.-g[i];
	printf("%.6lf\n",ans);
	return 0;
}
/*
3
1 2 50
1 3 50
50 0 0

*/