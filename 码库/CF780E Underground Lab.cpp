#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N=200005;
const int M=N<<1;
int n,m,k,ans[N<<1],tot;
int hed[N],et;
struct edge{int nx,to;}e[M];
inline void adde(int u,int v){
	e[++et].nx=hed[u],e[et].to=v,hed[u]=et;
}
bool vis[N];
void dfs(int u){
	ans[++tot]=u;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;
		if(!vis[v])vis[v]=1,dfs(v),ans[++tot]=u;
	}
}
signed main(){
	n=read(),m=read(),k=read();
	rep(i,1,m){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	vis[1]=1,dfs(1);
	int len=(2*n-1)/k+1,cnt=0;
	for(int i=1;i<=tot;i+=len){
		if(i+len-1<=tot){
			printf("%d",len),++cnt;
			for(int j=i;j<=i+len-1;++j)printf(" %d",ans[j]);
			puts("");
		}else{
			printf("%d",tot-i+1),++cnt;
			for(int j=i;j<=tot;++j)printf(" %d",ans[j]);
			puts("");
		}
	}
	for(++cnt;cnt<=k;++cnt)puts("1 1");
	return 0;
}