// Problem: P4609 [FJOI2016]建筑师
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4609
// Memory Limit: 250 MB
// Time Limit: 1000 ms

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
int S1[50005][205],fac[205],ifc[205];
#define mod 1000000007
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int comb(int n,int m){return n<m?0:1ll*fac[n]*1ll*ifc[m]%mod*ifc[n-m]%mod;}
void init(){
	fac[0]=1;rep(i,1,200)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[200]=qpow(fac[200],mod-2);per(i,199,0)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
	S1[0][0]=1;rep(i,1,50000)rep(j,1,200)S1[i][j]=(S1[i-1][j-1]+1ll*S1[i-1][j]*(i-1)%mod)%mod;
}
signed main(){
	init();
	for(int T=read();T;--T){
		int n=read(),A=read(),B=read();
		if(A+B-1>n)puts("0");
		else printf("%lld\n",1ll*comb(A+B-2,A-1)*S1[n-1][A+B-2]%mod);
	}
	return 0;
}