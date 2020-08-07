#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)]
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=100010;
const int mod=1e9+7;
int n,a[N],sum=1;
int qpow(int n,int k) {
    k=(k%(mod-1)+mod-1)%(mod-1);
    int res=1;
    while(k) {
        if(k&1)res=1ll*res*n%mod;
        n=1ll*n*n%mod,k>>=1;
    }
    return res;
}
const int inv3=qpow(3,mod-2);
int ans1,ans2;
signed main() {
    n=rd();
    for(int i=1;i<=n;++i)a[i]=rd(),sum=sum*(a[i]%(mod-1))%(mod-1);
    ans1=(qpow(2,sum-1)+((sum&1)?-1:1))%mod*inv3%mod;
    ans2=qpow(2,sum-1);
    printf("%lld/%lld\n",ans1,ans2);
    return 0;
}
//ans=\dfrac{2^{i-1}-(-1)^{i-1}}{3*2^{i-1}}