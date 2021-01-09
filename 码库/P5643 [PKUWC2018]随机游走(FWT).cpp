#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=19;
const int mod=998244353;
int n,q,st,dp[1<<N],A[N],B[N],deg[N],cnt[1<<N];
int head[N],num_edge;
struct edge{
	int to,nxt;
}e[N<<1];
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
void fmod(int&x){
	x+=x>>31&mod,x-=mod,x+=x>>31&mod;
}
void dfs(int u,int ft,int msk) {
	if(msk>>(u-1)&1)return;
	int sumA=0,sumB=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		dfs(v,u,msk),fmod(sumA+=A[v]),fmod(sumB+=B[v]);
	}
	int inv=qpow(deg[u]-sumA+mod,mod-2);
	A[u]=inv,B[u]=1ll*inv*(sumB+deg[u])%mod;
}
signed main(){
	n=read(),q=read(),st=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x),++deg[x],++deg[y];
	}
	for(int msk=0;msk<1<<n;++msk){
		fill(A,A+n+1,0),fill(B,B+n+1,0),cnt[msk]=cnt[msk>>1]+(msk&1);
		dfs(st,0,msk),dp[msk]=(cnt[msk]&1?1:-1)*B[st];
	}
	for(int o=2,k=1;k<1<<n;o<<=1,k<<=1)
		for(int i=0;i<1<<n;i+=o)
			for(int j=0;j<k;++j)
				fmod(dp[i+j+k]+=dp[i+j]);
	while(q--){
		int msk=0,k=read();
		for(int i=0;i<k;++i)msk|=1<<(read()-1);
		printf("%d\n",dp[msk]);
	}
}