#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long ll;
const int N=100010;
char s[N];
int n,sum[N][26],a[N];
ll ans;
signed main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(rint i=1;i<=n;++i)a[i]=s[i]-'a';
	for(rint i=1;i<=n;++i) {
		sum[i][a[i]]=sum[i-1][a[i]]+1;
		for(rint j=0;j<26;++j)
			if(j!=a[i])sum[i][j]=sum[i-1][j];
	}
	for(rint i=0;i<26;++i)
		ans=max(ans,1ll*sum[n][i]);
	for(rint i=0;i<26;++i)
		for(rint j=0;j<26;++j) {
			ll t=0;
			for(rint k=1;k<=n;++k) {
				if(a[k]==i)t+=sum[n][j]-sum[k][j];
			}
			ans=max(ans,t);
		}
	printf("%lld\n",ans);
	return 0;
}