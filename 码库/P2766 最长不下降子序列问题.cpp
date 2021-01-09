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

#define N 1005
#define M (N*N)
const int inf=0x3f3f3f3f;
int n,a[N];
int ans1,ans2,ans3;
int lsh[N],len,dp[N],tr[N];
int hed[N],et=1,S,T;
int dis[N],cur[N];
struct edge{int nx,to,fl;}e[M];
void addedge(int u,int v,int fl){e[++et].nx=hed[u],e[et].to=v,e[et].fl=fl,hed[u]=et;}
void adde(int u,int v,int fl){addedge(u,v,fl),addedge(v,u,0);}
void add(int x,int d){for(int i=x;i<=n;i+=i&-i)ckmax(tr[i],d);}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)ckmax(res,tr[i]);return res;}

bool bfs(int s,int t){
	queue<int>q;
	rep(i,1,T)cur[i]=hed[i],dis[i]=0;
	dis[s]=1,q.push(s);
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
	int rl=0,used=0;
	for(int i=cur[u];i;i=e[i].nx){
		int v=e[i].to;cur[u]=i;
		if(e[i].fl&&dis[v]==dis[u]+1){
			rl=dfs(v,min(e[i].fl,fl-used));
			if(rl)used+=rl,e[i].fl-=rl,e[i^1].fl=rl;
		}
	}
	return used;
}
signed main(){
	n=read();
	if(n==1)return puts("1\n1\n1"),0;
	rep(i,1,n)a[i]=lsh[i]=read();
	sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
	rep(i,1,n)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	rep(i,1,n)dp[i]=ask(a[i])+1,add(a[i],dp[i]),ckmax(ans1,dp[i]);
	printf("%d\n",ans1);

	S=n*2+1,T=S+1;
	rep(i,1,n){adde(i,i+n,1);if(dp[i]==1)adde(S,i,1);if(dp[i]==ans1)adde(i+n,T,1);}
	rep(i,1,n)rep(j,i+1,n)if(a[i]<=a[j]&&dp[i]+1==dp[j])adde(i+n,j,1);
	while(bfs(S,T))ans2+=dfs(S,inf);
	printf("%d\n",ans2);

	ans3=ans2;
	adde(S,1,inf),adde(1,1+n,inf);
	if(dp[n]==ans1)adde(n*2,T,inf),adde(n,n*2,inf);
	while(bfs(S,T))ans3+=dfs(S,inf);
	printf("%d\n",ans3);
}