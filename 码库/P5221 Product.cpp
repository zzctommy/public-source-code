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
const int N=1000005;
const int mod=104857601;
int n,fz=1,fm=1,ans;
int pri[785050],cnt,phi[N];
bool vis[N];
inline int qpow(int x,int y,int ret=1){
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1)
		ret=1ll*ret*x%mod; return ret;
}
void qmod(int&x,int mod){
	x+=x>>31&mod,x-=mod,x+=x>>31&mod;
}
void Sieve(const int&N) {
	phi[1]=1;
	for (int i=2;i<=N;++i){
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for (int j=1;j<=cnt&&i*pri[j]<=N;++j) {
			vis[i*pri[j]]=1;
			if (i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			phi[i*pri[j]]=phi[i]*phi[pri[j]];
		}
	}
	for(int i=1;i<=N;++i)qmod(phi[i]+=phi[i-1],mod-1);
}
signed main(){
	n=read(),Sieve(n);
	for(int i=1;i<=n;++i)fz=1ll*i*fz%mod;fz=qpow(fz,n<<1);
	for(int i=1;i<=n;++i)fm=1ll*fm*qpow(i,(phi[n/i]<<1)-1)%mod;
	fm=qpow(fm,mod-2);
	ans=1ll*fz*fm%mod*fm%mod,printf("%d\n",ans);
	return 0;
}