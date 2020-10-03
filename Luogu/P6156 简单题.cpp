#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=10000005;
const int mod = 998244353;
int n;LL k;
int pw[N],S[N],f[N], pri[N], cnt;
bool vis[N];
int qpow(int n,int k,int res=1){
	for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;
	return res;
}
void init(const int&N){
	pw[1]=1,f[1]=1;
	for(int i=2;i<=N;++i){
		if (!vis[i]) pri[++cnt] = i, pw[i] = qpow(i, k), f[i] = i - 1;
		for (int j = 1; j <= cnt && i * pri[j] <= N; ++ j) {
			vis[i * pri[j]] = 1, pw[i * pri[j]] = 1ll * pw[i] * pw[pri[j]] % mod;
			if (i % pri[j] == 0) {
				if(i / pri[j] % pri[j]) f[i * pri[j]] = -1ll * f[i / pri[j]] * pri[j] % mod;
				break;
			}
			pw[i * pri[j]] =1ll * pw[i] * pw[pri[j]] % mod, f [i * pri[j]] = 1ll * f[i] * f[pri[j]] % mod;
		}
	}
	for(int i=1;i<=N;++i)f[i]=(1ll*pw[i]*f[i]%mod+f[i-1])%mod,pw[i]=(pw[i]+pw[i-1])%mod;
	for(int i=1;i<=N;++i)S[i]=(S[i-1]+pw[i])%mod;
}
int query(int n){
	int res=0;
	for(int l=1,r;l<=n;l=r+1)
		r=n/(n/l),res=(res+1ll*(S[(n/l)*2]-S[n/l]*2)*(f[r]-f[l-1])%mod)%mod;
	return (res+mod)%mod;
}
signed main(){
	n=read(), scanf("%lld", &k), k %= mod - 1,init(n<<1);
	printf("%d\n",query(n));
}
/*
5000000 1000000000000000000
305836999
*/
