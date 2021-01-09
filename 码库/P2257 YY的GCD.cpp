#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=10000010;
int pri[N/10],mu[N],sum[N],cnt,vis[N];
LL ans;
void Sieve() {
	mu[1]=1;
	for(int i=2;i<N;++i) {
		if(!vis[i])pri[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pri[j]<N;++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j])mu[i*pri[j]]=-mu[i];
			else break;
		}
	}
	for(int j=1;j<=cnt;++j)
		for(int i=1;i*pri[j]<N;++i)
			sum[i*pri[j]]+=mu[i];
	for(int i=1;i<N;++i)sum[i]+=sum[i-1];
}
void solve(int n,int m) {
	ans=0;
	if(n>m)n^=m^=n^=m;
	for(int l=1,r;l<=n;l=r+1)
		r=min(n/(n/l),m/(m/l)),ans+=1ll*(n/l)*(m/l)*(sum[r]-sum[l-1]);
	printf("%lld\n",ans);
}
signed main() {
	Sieve();
	for(int T=rd();T;--T)solve(rd(),rd());
	return 0;
}