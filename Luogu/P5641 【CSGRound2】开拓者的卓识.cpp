#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
const int N=100005;
const int M=600005;
const int mod=998244353;
int n,k,a[M],p[M],inv[N],rev[M],lg,lim;
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;return res;}
void init(int n){
	for (lg = 0, lim = 1; lim < n; ++ lg, lim <<= 1);
	for (int i = 0; i < lim; ++ i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
}
void NTT(int*a,int g,int op=0){
	for (int i = 0; i < lim; ++ i) if (i > rev[i]) std::swap(a[i], a[rev[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int wn = qpow (g, (mod - 1) / (i << 1));
		for (int j = 0; j < lim; j += i << 1) {
			int w0 = 1; 
			for (int k = 0; k < i; ++ k, w0 = 1ll * w0 * wn % mod) {
				int X = a[j + k], Y = 1ll * w0 * a[i + j + k] % mod;
				a[j + k] = (X + Y) % mod, a[i + j + k] = (X - Y + mod) % mod;
			}
		}
	}
	if(!op)return;int ilim = qpow(lim, mod - 2);
	for (int i = 0; i < lim; ++ i) a[i] = 1ll * a[i] * ilim % mod;
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i)a[i]=read();
	p[0]=1,inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;++i)p[i]=1ll*p[i-1]*(k-1+i)%mod*inv[i]%mod,a[i]=1ll*a[i]*p[i-1]%mod;
	init(n<<1),NTT(a,3),NTT(p,3);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*p[i]%mod;
	NTT(a,qpow(3,mod-2),1);
	for(int i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}