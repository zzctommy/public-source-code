// Problem: E. Counting Arrays
// Contest: Codeforces - Educational Codeforces Round 33 (Rated for Div. 2)
// URL: https://codeforces.com/contest/893/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms

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
const int N=2000005;
#define mod 1000000007
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int n,pri[N/10],pct,low[N],fac[N],pw2[N],ifc[N];
bool vis[N];
void init(const int&n=N-1){
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++pct]=i,low[i]=i;
		for(int j=1;j<=pct&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1,low[i*pri[j]]=pri[j];
			if(i%pri[j]==0)break;
		}
	}
	fac[0]=1;for(int i=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[n]=qpow(fac[n],mod-2);for(int i=n-1;i>=0;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	pw2[0]=1;for(int i=1;i<=n;++i)pw2[i]=1ll*pw2[i-1]*2%mod;
}
int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod;}
signed main(){
	init();
	for(int T=read();T;--T){
		int x=read(),y=read(),res=1;
		map<int,int>mp;
		while(x>1)++mp[low[x]],x/=low[x];
		for(auto j:mp)res=1ll*res*comb(y+j.se-1,y-1)%mod;
		res=1ll*res*pw2[y-1]%mod;
		printf("%d\n",res);
	}
}