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
const int N=400005;
int n,m,S,T;
LL dis[N];
bool vis[N];
struct edge{
	int v,w,id;
	inline bool operator < (const edge&t)const{return w<t.w;}
	edge(){v=w=id=0;}
	edge(int v_,int w_,int i_){v=v_,w=w_,id=i_;}
};
vector<edge>E[N];
vector<pair<LL,int> >e[N];
void Dij(){
	priority_queue<pair<LL,int> >pq;
	memset(dis,0x3f,sizeof(dis));
	pq.push(mkp(dis[S]=0,S));
	while(!pq.empty()){
		int u=pq.top().se;pq.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=0,up=sz(e[u]);i<up;++i){
			int v=e[u][i].se;
			if(dis[v]>dis[u]+e[u][i].fi){
				dis[v]=dis[u]+e[u][i].fi;
				if(!vis[v])pq.push(mkp(-dis[v],v));
			}
		}
	}
}
signed main(){
	n=read(),m=read(),S=m*2+2,T=S+1;
	rep(i,1,m){
		int x=read(),y=read(),z=read();
		assert(z<=2000000);
		E[x].pb(edge(y,z,i<<1)),E[y].pb(edge(x,z,i<<1|1));
	}
	rep(u,1,n){
		sort(E[u].begin(),E[u].end());
		for(int i=0,up=sz(E[u]);i<up;++i){
			int v=E[u][i].v,w=E[u][i].w,id=E[u][i].id;
			if(i)e[id].pb(mkp(0,E[u][i-1].id)),e[E[u][i-1].id].pb(mkp(w-E[u][i-1].w,id));
			if(u==1)e[S].pb(mkp(w,id));
			if(v==n)e[id].pb(mkp(w,T));
			e[id].pb(mkp(w,id^1));
		}
	}
	Dij();
	printf("%lld\n",dis[T]);
	return 0;
}