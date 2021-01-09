#include<bits/stdc++.h>
using namespace std;
#define rint register int 
#define N (200010)
#define len (rp[i]-lp[i]+1)
int st[N],top;
int n,a[N],lp[N],rp[N],ans[N];
int main() {
	scanf("%d",&n);
	for(rint i=1;i<=n;++i)scanf("%d",&a[i]);
	for(rint i=1;i<=n;++i) {
		while(top&&a[st[top]]>a[i])rp[st[top]]=i-1,--top;
		lp[i]=st[top]+1;st[++top]=i;
	}
	while(top)rp[st[top--]]=n;
	for(rint i=1;i<=n;++i)
		ans[len]=max(ans[len],a[i]);
	for(rint i=n-1;i>=1;--i)
		ans[i]=max(ans[i],ans[i+1]);
	for(rint i=1;i<=n;++i)
		printf("%d ",ans[i]);
	return 0;
}