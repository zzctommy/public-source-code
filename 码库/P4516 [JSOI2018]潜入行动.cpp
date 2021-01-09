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
const int N=100005;
const int mod=1e9+7;
void fmod(int&x){x-=mod,x+=x>>31&mod;}
struct edge{int nxt,to;}e[N<<1];
int num_edge,head[N];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
int n,k,dp[N][105][2][2],cpy[105][2][2],siz[N];
//dp[root][used][choose?][controled?]
void dfs(int u,int ft){
	siz[u]=1;
	dp[u][0][0][0]=1,dp[u][1][1][0]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		dfs(v,u);
		for(int j=0,up=std::min(siz[u],k);j<=up;++j)
			cpy[j][0][0]=dp[u][j][0][0],dp[u][j][0][0]=0,
			cpy[j][0][1]=dp[u][j][0][1],dp[u][j][0][1]=0,
			cpy[j][1][0]=dp[u][j][1][0],dp[u][j][1][0]=0,
			cpy[j][1][1]=dp[u][j][1][1],dp[u][j][1][1]=0;
		for(int j=0,up1=std::min(k,siz[u]);j<=up1;++j)
			for(int l=0,up2=std::min(k-j,siz[v]);l<=up2;++l){
				fmod(dp[u][j+l][0][0]+=1ll*cpy[j][0][0]*dp[v][l][0][1]%mod),
				fmod(dp[u][j+l][0][1]+=1ll*cpy[j][0][1]*(1ll*(dp[v][l][1][1]+dp[v][l][0][1])%mod)%mod),
				fmod(dp[u][j+l][0][1]+=1ll*cpy[j][0][0]*dp[v][l][1][1]%mod),
				fmod(dp[u][j+l][1][0]+=1ll*cpy[j][1][0]*((dp[v][l][0][1]+dp[v][l][0][0])%mod)%mod),
				fmod(dp[u][j+l][1][1]+=1ll*cpy[j][1][1]*(1ll*dp[v][l][0][0]+1ll*dp[v][l][0][1]+1ll*dp[v][l][1][0]+1ll*dp[v][l][1][1])%mod),
				fmod(dp[u][j+l][1][1]+=1ll*cpy[j][1][0]*((dp[v][l][1][1]+dp[v][l][1][0])%mod)%mod);
			}
		siz[u]+=siz[v];
	}
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	dfs(1,0),printf("%d\n",(dp[1][k][0][1]+dp[1][k][1][1])%mod);
	return 0;
}