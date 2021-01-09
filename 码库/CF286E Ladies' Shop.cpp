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
const int N=3000010;
int n,m,p[N],ans;
int A[N],B[N];
const int mod=998244353;
int qpow(int n,int k,int P=mod) {
    int res=1;
    while(k) {
        if(k&1)res=1ll*res*n%P;
        n=1ll*n*n%P,k>>=1;
    }
    return res;
}
const int G=3;
const int IG=qpow(G,mod-2);
int lim,lg,rev[N];
void init(int n) {
    for(lim=1,lg=0;lim<n;lim<<=1,++lg);
    for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int g,int op=0) {
    for(int i=0;i<lim;++i)
        if(i>rev[i])swap(a[i],a[rev[i]]);
    for(int i=1;i<lim;i<<=1) {
        int wn=qpow(g,(mod-1)/(i<<1));
        for(int j=0;j<lim;j+=(i<<1)) {
            int w0=1;
            for(int k=0;k<i;++k,w0=1ll*w0*wn%mod) {
                int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
                a[j+k]=(X+Y)%mod,a[i+j+k]=(X-Y+mod)%mod;
            }
        }
    }
   if(!op)return;int ilim=qpow(lim,mod-2);
   for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
signed main() {
    n=ans=rd(),m=rd();
    for(int i=1;i<=n;++i) {
        p[i]=rd();
        if(p[i]<=m)A[p[i]]=B[p[i]]=1;
    }
    init(m<<1),NTT(B,G);
    for(int i=0;i<lim;++i)B[i]=1ll*B[i]*B[i]%mod;
    NTT(B,IG,1);
    for(int i=1;i<=m;++i) {
        if(!B[i])continue;
        --ans;
        if(!A[i])return puts("NO"),0;
    }
    printf("YES\n%d\n",ans);
    for(int i=1;i<=m;++i)if(!B[i]&&A[i])printf("%d ",i);
    return 0;
}