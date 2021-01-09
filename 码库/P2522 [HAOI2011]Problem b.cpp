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
const int N=50010;
int pri[N/10],cnt,vis[N],mu[N],sum[N];
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
	for(int i=1;i<N;++i)sum[i]=sum[i-1]+mu[i];
}
LL solve(int n,int m,int k) {
	if(n>m)n^=m^=n^=m;
	LL res=0;
	for(int l=1,r;l*k<=n;l=r+1) 
		r=min(n/(n/l),m/(m/l)),res+=1ll*(n/(l*k))*(m/(l*k))*(sum[r]-sum[l-1]);
	return res;
}
signed main() {
	Sieve();
	for(int n=rd();n;--n) {
		int a=rd(),b=rd(),c=rd(),d=rd(),k=rd();
		printf("%lld\n",solve(b,d,k)+solve(a-1,c-1,k)-solve(b,c-1,k)-solve(a-1,d,k));
	}
	return 0;
}