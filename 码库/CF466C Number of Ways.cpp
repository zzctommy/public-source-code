#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10;
int sum[N],n,ans,tmp;
signed main() {
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&sum[i]),sum[i]+=sum[i-1];
	for(int i=1;i<=n;++i) {
		if(i>1&&i<n&&sum[i]*3==sum[n]*2)ans+=tmp;
		if(sum[i]*3==sum[n])++tmp;
	}
	printf("%lld\n",ans);
	return 0;
}