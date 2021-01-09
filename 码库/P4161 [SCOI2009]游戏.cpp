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
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) {
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=10009;
bool vis[N];
int pri[N],cnt;
int n;
LL ans,dp[N];
void Sieve(){
	for(int i=2;i<=n;++i) {
		if(!vis[i])pri[++cnt]=i;
		for(int j=1;j<=cnt&&i*pri[j]<=n;++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}
signed main() {
	n=rd();
	Sieve();
	dp[0]=1;
	for(int i=1;i<=cnt;++i) {
		for(int j=n;j>=pri[i];--j) {
			for(int k=1,t=pri[i];t<=j;++k,t*=pri[i]) {
				dp[j]+=dp[j-t];
			}
		}
	}
	for(int i=0;i<=n;++i)ans+=dp[i];
	printf("%lld\n",ans);
}
