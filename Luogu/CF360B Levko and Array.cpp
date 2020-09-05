#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2005;
int n,k,a[N],l,r,ans; 
bool check(int x) {
	int f[N]={0};
	for(int i=1;i<=n;++i) {
		f[i]=i-1;
		for(int j=1;j<i;++j) {
			if(abs(a[i]-a[j])<=(i-j)*x)
				f[i]=min(f[i],f[j]+i-j-1);
		}
		if(f[i]+n-i<=k)return true;
	}
	return false;
}
signed main() {
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	for(int i=1;i<n;++i)
		r=max(r,abs(a[i]-a[i+1]));
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}