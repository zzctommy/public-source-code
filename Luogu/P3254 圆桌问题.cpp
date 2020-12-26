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
#define per(i,y,x) for(int i=y,i##end=x;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}

const int N=450;
const int M=9e4;
const int inf=0x3f3f3f3f;

int m,n,r[N],c[N];
int hed[N],et=1,S,T,dis[N],cur[N],mf;
vector<int>ans[N];
struct edge{int nx,to,fl,id;}e[M];
void addedge(int u,int v,int fl,int id=0){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,e[et].id=id,hed[u]=et;}
void adde(int u,int v,int fl,int id=0){addedge(u,v,fl,id),addedge(v,u,0,id);}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,T)dis[i]=0,cur[i]=hed[i];
	q.push(s),dis[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(e[i].fl&&!dis[v]){
				dis[v]=dis[u]+1,q.push(v);
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int fl){
	if(u==T)return fl;
	int used=0,rl;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(fl-used,e[i].fl));
			if(rl){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used==fl)break;
			}
		}
	}
	return used;
}
signed main(){
	m=read(),n=read(),S=n+m+1,T=S+1;
	rep(i,1,m)r[i]=read(),adde(S,i,r[i]),r[0]+=r[i];
	rep(i,1,n)c[i]=read(),adde(i+m,T,c[i]);
	rep(i,1,m)rep(j,1,n)adde(i,j+m,1,i);
	while(bfs(S,T))mf+=dfs(S,T);
	if(mf!=r[0])return puts("0"),0;
	for(int i=2;i<et;i+=2)
		if(e[i^1].fl&&e[i].id)ans[e[i].id].pb(e[i].to-m);
	puts("1");
	rep(i,1,n){
		rep(j,0,r[i]-1)printf("%d ",ans[i][j]);
		puts("");
	}
	return 0;
}