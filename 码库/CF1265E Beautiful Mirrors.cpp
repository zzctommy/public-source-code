#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int long long
#define rint register int
#define pb push_back
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int mod=998244353;
int qpow(int n,int k) {
	int res=1;
	while(k) {
		if(k&1)res=1ll*res*n%mod;
		n=1ll*n*n%mod,k>>=1;
	}
	return res;
}
int n,ans;
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i) {
		int x=rd();
		ans=(ans+1)*100%mod*qpow(x,mod-2)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}