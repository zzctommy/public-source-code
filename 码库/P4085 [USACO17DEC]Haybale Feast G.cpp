#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
#define N 100009
int n,m,F[N],S[N],lp[N],rp[N],stk[N],top,ans=1e18,sum[N];
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)F[i]=rd(),S[i]=rd(),sum[i]=sum[i-1]+F[i];
	for(int i=1;i<=n;++i) {
		while(top&&S[stk[top]]<=S[i])rp[stk[top--]]=i-1;
		lp[i]=stk[top]+1,stk[++top]=i;
	}
	while(top)rp[stk[top--]]=n;
	for(int i=1;i<=n;++i)
		if(sum[rp[i]]-sum[lp[i]-1]>=m)ans=min(ans,S[i]);
	printf("%lld\n",ans);
	return 0;
}