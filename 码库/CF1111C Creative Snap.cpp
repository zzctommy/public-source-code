#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int K=100009;
const int M=K*21;
const int inf=1e15;
int n,k,A,B,a[K],cnt[M],dp[M],ls[M],rs[M],tot,rt;
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p,int l,int r) {
	cnt[p]=cnt[ls[p]]+cnt[rs[p]];
	dp[p]=min(dp[ls[p]]+dp[rs[p]],cnt[p]?B*(r-l+1)*cnt[p]:A);
}
void solve(int l,int r,int &p,int pos) {
	if(!p)p=++tot;
	if(l==r){++cnt[p],dp[p]=cnt[p]*B;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)solve(l,mid,ls[p],pos);
	else solve(mid+1,r,rs[p],pos);
	pushup(p,l,r);
}
signed main() {
	n=read(),k=read(),A=read(),B=read();
	dp[0]=A;
	for(int i=1;i<=k;++i)solve(1,1<<n,rt,read());
	printf("%lld\n",dp[1]);
	return 0;
}