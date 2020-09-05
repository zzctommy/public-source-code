#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define N (1000010)
int n,a[N],st[N],top,p[N],lpos[N],rpos[N];
long long sum1,sum2;
int main() {
	scanf("%d",&n);
	for(rint i=1;i<=n;++i)scanf("%d",&a[i]);
	for(rint i=1;i<=n;++i) {
		while(top&&a[st[top]]<=a[i])rpos[st[top--]]=i-1;
		lpos[i]=st[top]+1,st[++top]=i;
	} 
	while(top)rpos[st[top--]]=n;
	for(rint i=1;i<=n;++i)sum1+=1ll*a[i]*(i-lpos[i]+1)*(rpos[i]-i+1);
	memset(lpos,0,sizeof(lpos)),memset(rpos,0,sizeof(rpos));
	for(rint i=1;i<=n;++i) {
		while(top&&a[st[top]]>=a[i])rpos[st[top--]]=i-1;
		lpos[i]=st[top]+1,st[++top]=i;
	}
	while(top)rpos[st[top--]]=n;
	for(rint i=1;i<=n;++i)sum2+=1ll*a[i]*(i-lpos[i]+1)*(rpos[i]-i+1);
	printf("%lld\n",sum1-sum2);
	return 0;
}