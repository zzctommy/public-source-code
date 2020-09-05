#include <bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
int mod;
const int N=1100;
int qpow(int n,int k) {
	int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;
	return res;
}
int n,k,a[N*N<<1],x[N],lim,lg,rev[N*N<<1];
vector<int>v;
void NTT(int *a,int g) {
    for(rint i=0;i<lim;++i)
        if(i>rev[i])swap(a[i],a[rev[i]]);
    for(rint i=1;i<lim;i<<=1) {
        LL wn=qpow(g,(mod-1)/(i<<1));
        for(rint j=0;j<lim;j+=(i<<1)) {
            LL w0=1;
            for(rint k=0;k<i;++k,w0=w0*wn%mod) {
                LL X=a[j+k],Y=w0*a[j+k+i]%mod;
                a[j+k]=(X+Y)%mod;
                a[j+k+i]=(X-Y+mod)%mod;
            }
        }
    }
}
signed main() {
	n=rd(),k=rd();
	for(rint i=1;i<=n;++i)x[i]=rd();
	for(lim=1,lg=0;lim<=524288;lim<<=1,++lg);
	for(rint i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	
	for(rint i=1;i<=n;++i)++a[x[i]];
	mod=998244353;
	NTT(a,3);
	for(rint i=0;i<lim;++i)a[i]=qpow(a[i],k);
	NTT(a,qpow(3,mod-2));
	for(rint i=0,inv=qpow(lim,mod-2);i<lim;++i)a[i]=1ll*a[i]*inv%mod;
	for(rint i=0;i<=1000000;++i)if(a[i])v.push_back(i);
	
	memset(a,0,sizeof(a));
	for(rint i=1;i<=n;++i)++a[x[i]];
	mod=1004535809;
	NTT(a,3);
	for(rint i=0;i<lim;++i)a[i]=qpow(a[i],k);
	NTT(a,qpow(3,mod-2));
	for(rint i=0,inv=qpow(lim,mod-2);i<lim;++i)a[i]=1ll*a[i]*inv%mod;
	for(rint i=0;i<=1000000;++i)if(a[i])v.push_back(i);
	
	sort(v.begin(),v.end());
	int len=unique(v.begin(),v.end())-v.begin();
	for(rint i=0;i<len;++i)printf("%d ",v[i]);
	return 0;
}