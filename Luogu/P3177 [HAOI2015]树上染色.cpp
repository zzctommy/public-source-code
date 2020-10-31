#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 2005
int n,k,siz[N];
LL dp[N][N],cpy[N];
int head[N],num_edge;
struct edge{int nxt,to,val;}e[N<<1];
void addedge(int fr,int to,int val){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	e[num_edge].val=val;
	head[fr]=num_edge;
}
void ckmax(LL&x,LL y){if(x<y)x=y;}
void dfs(int u,int ft){
	siz[u]=1,dp[u][0]=dp[u][1]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		dfs(v,u);
		for(int j=0;j<=siz[u];++j)cpy[j]=dp[u][j];
		for(int j=0,mx1=min(siz[u],k);j<=mx1;++j)
			for(int l=0,mx2=min(siz[v],k-j);l<=mx2;++l)
				ckmax(dp[u][j+l],cpy[j]+dp[v][l]+1ll*l*(k-l)*e[i].val+1ll*(siz[v]-l)*(n-k-(siz[v]-l))*e[i].val);
		siz[u]+=siz[v];
	}
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		addedge(x,y,z),addedge(y,x,z);
	}
	memset(dp,-0x3f,sizeof(dp));
	dfs(1,0);
	printf("%lld\n",dp[1][k]);
	return 0;
}