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

const int N=1050;
const int M=6e4+7;
const int inf=0x3f3f3f3f;

int k,n,a[N],num;
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
	k=read(),n=read(),S=n+k+1,T=S+1;
	rep(i,1,k)adde(i+n,T,a[i]=read()),num+=a[i];
	rep(i,1,n){
		int x=read();
		adde(S,i,1);
		rep(j,1,x)adde(i,read()+n,1,i);
	}
	while(bfs(S,T))mf+=dfs(S,inf);
	if(mf!=num)return puts("No Solution!"),0;
	for(int i=2;i<et;i+=2)
		if(e[i].id&&e[i^1].fl)ans[e[i].to-n].pb(e[i].id);
	rep(i,1,k){
		printf("%d:",i);
		rep(j,0,a[i]-1)printf(" %d",ans[i][j]);
		puts("");
	}
}