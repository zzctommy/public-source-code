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
int n,m,A[N],B[N],C[N],F[N],rt;
LL s[N],dp[N];
bool bok[N];
pair<int,int>D[N];
vector<int>e[N],g[N];
int anc(int x){return x==F[x]?x:F[x]=anc(F[x]);}
void dfs(int u){
	s[u]=B[u],dp[u]=114514114514114514;
	if(!sz(g[u]))return dp[u]=max(A[u],B[u]),void();
	for(int v:g[u])dfs(v),s[u]+=s[v];
	for(int v:g[u])ckmin(dp[u],s[u]-s[v]+max(dp[v],(LL)C[u]));
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)A[i]=read(),B[i]=read(),D[i]=mkp(C[i]=max(A[i]-B[i],0),i),F[i]=i;
	rep(i,1,m){
		int x=read(),y=read();
		e[x].pb(y),e[y].pb(x);
	}
	sort(D+1,D+n+1);
	for(int i=1;i<=n;++i){
		int u=D[i].se;
		bok[u]=1;
		for(int v:e[u]){
			if(bok[v]&&u!=anc(v)){
				g[u].pb(anc(v)),F[anc(v)]=u;
			}
		}
	}
	rt=D[n].se,dfs(rt);
	cout<<dp[rt]<<'\n';
	return 0;
}
/*
1 0
602436426 445
*/