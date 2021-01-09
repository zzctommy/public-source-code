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
const int N=100005;
const int M=200005;
int n,m,deg[N],ord[N],ans;
int et,hed[N];
bool vis[N];
pair<int,int>p[N];
struct edge{int nx,to;}e[M];
struct node{int x,y;}E[M];
void addedge(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
signed main(){
	n=read(),m=read();
	rep(i,1,m){
		int x=read(),y=read();
		E[i].x=x,E[i].y=y;
		++deg[x],++deg[y];
	}
	rep(i,1,n)p[i]=mkp(deg[i],i);
	sort(p+1,p+n+1);
	rep(i,1,n)ord[p[i].se]=i;
	rep(i,1,m)
		if(ord[E[i].x]>ord[E[i].y])addedge(E[i].x,E[i].y);
		else addedge(E[i].y,E[i].x);
	rep(u,1,n){
		for(int i=hed[u];i;i=e[i].nx)vis[e[i].to]=1;
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			for(int j=hed[v];j;j=e[j].nx)
				if(vis[e[j].to])++ans;
		}
		for(int i=hed[u];i;i=e[i].nx)vis[e[i].to]=0;
	}
	printf("%d\n",ans);
	return 0;
}