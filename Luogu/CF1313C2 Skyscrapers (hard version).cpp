#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define int long long
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=500005;
const int inf=100000000000000;
int dp1[N],dp2[N],n,a[N],ans[N],pre[N],suf[N],lp[N],rp[N],st[N],top,p,sum;
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1;i<=n;++i) {
		while(top&&a[st[top]]>a[i])--top;
		lp[i]=st[top];st[++top]=i;
	}
	top=0,st[++top]=n+1;
	for(rint i=n;i>=1;--i) {
		while(top&&a[st[top]]>a[i])--top;
		rp[i]=st[top];st[++top]=i;
	}
	for(rint i=1;i<=n;++i)dp1[i]=(i-lp[i])*a[i]+dp1[lp[i]];
	for(rint i=n;i>=1;--i)dp2[i]=(rp[i]-i)*a[i]+dp2[rp[i]];
	for(rint i=1;i<=n;++i)if(dp1[i]+dp2[i]-a[i]>sum)sum=dp1[i]+dp2[i]-a[i],p=i;
	for(rint i=p,tmp=a[p];i>=1;--i)ans[i]=min(a[i],tmp),tmp=ans[i];
	for(rint i=p,tmp=a[p];i<=n;++i)ans[i]=min(a[i],tmp),tmp=ans[i];
	for(rint i=1;i<=n;++i)printf("%lld ",ans[i]);
	return 0;
}