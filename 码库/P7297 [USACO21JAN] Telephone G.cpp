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
const int K=52;
const int N=50005;
const int M=N*K*2;
int n,k,c[K][K],b[N],lst[K],dis[N];
bool vis[N];
int hed[N],et;
struct edge{int nx,to,vl;}e[M];
void adde(int u,int v,int d){e[++et].nx=hed[u],e[et].to=v,e[et].vl=d,hed[u]=et;}
void Dij(){
	priority_queue<pair<int,int> >pq;
	memset(dis,0x3f,sizeof(dis));
	pq.push(mkp(dis[1]=0,1));
	while(!pq.empty()){
		int u=pq.top().se;pq.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(ckmin(dis[v],dis[u]+e[i].vl)){
				if(!vis[v])pq.push(mkp(-dis[v],v));
			}
		}
	}
}
signed main(){
	n=read(),k=read();
	rep(i,1,n)b[i]=read();
	rep(i,1,k){
		static char str[K];
		scanf("%s",str+1);
		rep(j,1,k)c[i][j]=str[j]-'0';
	}
	for(int i=1;i<=n;++i){
		rep(j,1,k)if(c[b[i]][j]&&lst[j])adde(i,lst[j],i-lst[j]);
		lst[b[i]]=i;
	}
	memset(lst,0,sizeof(lst));
	for(int i=n;i>=1;--i){
		rep(j,1,k)if(c[b[i]][j]&&lst[j])adde(i,lst[j],lst[j]-i);
		lst[b[i]]=i;
	}
	for(int i=1;i<=n;++i)if(c[b[i]][b[n]])adde(i,n,n-i);
	Dij();
	printf("%d\n",dis[n]!=0x3f3f3f3f?dis[n]:-1);
	return 0;
}