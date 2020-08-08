#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod=100003;
const int N=100009;
int n,k,a[N],dp[N],mi,ans;
int qpow(int n,int k) {
	int res=1;
	while(k) {
		if(k&1)res=1ll*res*n%mod;
		n=1ll*n*n%mod,k>>=1;
	}
	return res;
}
signed main() {
	n=rd(),k=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=n;i>=1;--i) {
		if(!a[i])continue;
		++mi;
		for(int j=1;j*j<=i;++j) {
			if(i%j)continue;
			a[j]^=1;
			if(j*j!=i)a[i/j]^=1;
		}
	}
	dp[n]=1;
	for(int i=n-1;i>=1;--i)
		dp[i]=1ll*(((1ll*dp[i+1]*(n-i)%mod+n)%mod)*qpow(i,mod-2))%mod;
	if(mi<=k)ans=mi;
	else {for(int i=k+1;i<=mi;++i)ans=(ans+dp[i])%mod;ans=(ans+k)%mod;}
	for(int i=1;i<=n;++i)ans=(1ll*ans*i)%mod;
	printf("%d\n",ans);return 0;
} 
