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
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
int n,q,ans,a[N];
int vis[N],pri[N/10],mu[N],cnt,f[N],num[N],g[N];
void init() {
	for(int i=1;i<N;++i)
		for(int j=1;i*j<N;++j)
			g[i]+=num[i*j]*j;
	mu[1]=1;
	for(int i=2;i<N;++i) {
		if(!vis[i])pri[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pri[j]<N;++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j])mu[i*pri[j]]=-mu[i];
			else break;
		}
	}
	for(int i=1;i<N;++i)
		for(int j=1;i*j<N;++j)
			f[i*j]+=mu[i]*i;
	for(int i=1;i<N;++i)
		ans+=i*f[i]*g[i]*g[i];
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)++num[a[i]=rd()];
	init();
	printf("%lld\n",ans);
	return 0;
}