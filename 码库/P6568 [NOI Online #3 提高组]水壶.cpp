#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],s[1000005],ans,k;
signed main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
	for(int i=k+1;i<=n;++i)ans=max(ans,s[i]-s[i-k-1]);
	printf("%d\n",ans);
	return 0;
}