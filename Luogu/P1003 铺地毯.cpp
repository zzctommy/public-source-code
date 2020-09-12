#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll x,y,n,a[10005],b[10005],g[10005],k[10005],status=-1;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&a[i],&b[i],&g[i],&k[i]);
	} 
	scanf("%lld%lld",&x,&y);
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=x&&b[i]<=y&&g[i]+a[i]>=x&&k[i]+b[i]>=y)status=i;
	}
	printf("%lld\n",status);
	return 0;
}