#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
const int M=700005;
const int mod=998244353;
int n,m;
int sum[N],dp[N],ind[N];
struct edge{
	int nxt,to;
}e[M];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
void topo(){
	queue<int>q;
	for(int i=1;i<=n;++i)sum[i]=1;
	for(int i=1;i<=n;++i)if(!ind[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			fmod(sum[v]+=sum[u]);
			fmod(dp[v]+=sum[u]),fmod(dp[v]+=dp[u]);
			if(!--ind[v])q.push(v);
		}
	}
}
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		addedge(x,y),++ind[y];
	}
	topo();
	for(int i=1;i<=n;++i)fmod(sum[0]+=sum[i]),fmod(dp[0]+=dp[i]);
	printf("%lld\n",1ll*dp[0]*qpow(sum[0],mod-2)%mod);
	return 0;
}