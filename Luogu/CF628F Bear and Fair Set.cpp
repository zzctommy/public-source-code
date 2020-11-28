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

const int N=11005;
const int M=N*7*2;
const int inf=0x3f3f3f3f;

int n,b,q,sum[N][5];
pair<int,int>p[N];
int dis[N],cur[N],mf,S,T,hed[N],et=1;
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].to=v,e[et].nx=hed[u],e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,T)cur[i]=hed[i],dis[i]=0;
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
	int rl,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(fl){
				e[i].fl-=rl,e[i^1].fl+=rl,used+=rl;
				if(used==fl)break;
			}
		}
	}
	return used;
}

signed main(){
	n=read(),b=read(),q=read(),S=q+6+1,T=S+1;
	rep(i,1,b)rep(j,0,4)sum[i][j]=sum[i-1][j]+(i%5==j);
	rep(i,1,q)p[i].fi=read(),p[i].se=read();
	sort(p+1,p+q+1),p[++q]=mkp(b,n);
	rep(i,1,q){
		if(p[i].se>=p[i-1].se)adde(S,i,p[i].se-p[i-1].se);
		else return puts("unfair"),0;
		rep(j,0,4)adde(i,q+j+1,sum[p[i].fi][j]-sum[p[i-1].fi][j]);
	}
	rep(i,1,5)adde(q+i,T,n/5);
	while(bfs(S,T))mf+=dfs(S,inf);
	puts(mf==n?"fair":"unfair");
	return 0;
}