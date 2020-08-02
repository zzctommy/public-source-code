#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=5000010;
const int mod=1000000007;
int T,n,m,k,ans;
int pri[N/10],cnt,f[N],pw[N/10],vis[N];
int qpow(int n,int k){
    int res=1;
    while(k) {
        if(k&1)res=res*n%mod;
        n=n*n%mod,k>>=1;
    }
    return res;
}
void Sieve() {
    f[1]=1;
    for(int i=2;i<N;++i) {
        if(!vis[i])pri[++cnt]=i,pw[cnt]=qpow(i,k),f[i]=pw[cnt]-1;
        for(int j=1;j<=cnt&&i*pri[j]<N;++j) {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0){f[i*pri[j]]=f[i]*pw[j]%mod;break;}
            else f[i*pri[j]]=f[i]*f[pri[j]]%mod;
        }
    }
    for(int i=1;i<N;++i)f[i]=(f[i]+f[i-1])%mod;
}
void solve() {
    n=rd(),m=rd();
    ans=0;
    if(n>m)n^=m^=n^=m;
    for(int l=1,r;l<=n;l=r+1) {
        r=min(n/(n/l),m/(m/l));
        ans=(ans+((n/l)*(m/l)%mod)*(f[r]-f[l-1]+mod)%mod)%mod;
    }
    printf("%lld\n",ans);
}
signed main() {
    T=rd(),k=rd();
    Sieve();
    for(;T;--T)solve();
}