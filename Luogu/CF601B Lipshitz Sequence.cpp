#include<bits/stdc++.h>
using namespace std;
#define rint register int 
#define N 100010
int n,q,h[N],a[N],l,r,top,st[N],lp[N],rp[N];
long long ans;
int main() {
	scanf("%d%d",&n,&q);
	for(rint i=1;i<=n;++i)scanf("%d",&h[i]);
	while(q--) {
		scanf("%d%d",&l,&r),--r,ans=0;
		int len=r-l+1;
		for(rint i=1;i<=len;++i)
			a[i]=abs(h[l+i-1]-h[l+i]);
		for(rint i=1;i<=len;++i) {
			while(top&&a[st[top]]<a[i])rp[st[top--]]=i-1;
			lp[i]=st[top]+1;st[++top]=i;
		}
		while(top)rp[st[top--]]=len;
		for(rint i=1;i<=len;++i)ans+=1ll*a[i]*(i-lp[i]+1)*(rp[i]-i+1);
		printf("%lld\n",ans);
	}
	return 0;
}