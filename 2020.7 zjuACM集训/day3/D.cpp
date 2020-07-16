#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define int long long
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=8000010;
const int mod=1e9+7;
int qpow(int n,int k) {
	int res=1;
	while(k) {
		if(k&1)res=res*n%mod;
		n=n*n%mod;k>>=1;
	}
	return res;
}
const int inv2=qpow(2,mod-2);
int pri[N],phi[N],cnt;
int sum_phi[N];
bool vis[N];
int n,ans;
inline void init() {
	phi[1]=1;
	for(int i=2;i<N;++i) {
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pri[j]<N;++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	for(int i=1;i<N;++i)sum_phi[i]=(sum_phi[i-1]+phi[i])%mod;
}
unordered_map<int,int>mp_phi;
int djs_phi(int x) {
	if(x<N)return sum_phi[x];
	if(mp_phi.find(x)!=mp_phi.end())return mp_phi[x];
	int res=((((x%mod)*((x+1)%mod))%mod)*inv2)%mod;
	for(int l=2,r;l<=x;l=r+1)
		r=x/(x/l),res=(res-((r-l+1)%mod)*djs_phi(x/l)%mod+mod)%mod;
	return mp_phi[x]=(res%mod+mod)%mod;
}
signed main() {
	init(),n=rd();
	for(int l=1,r;l<=n;l=r+1)
		r=n/(n/l),ans=(ans+(2*djs_phi(n/l)%mod-1+mod)%mod*(djs_phi(r)-djs_phi(l-1)+mod)%mod+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
