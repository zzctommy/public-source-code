#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1000000007;
const int N=5010;
int s[N],f[N],h[N],n,m,mx,sum;
vector<int>vec[N];
signed main() {
	scanf("%lld%lld",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%lld",&s[i]);
	for(int i=1; i<=m; ++i) {
		scanf("%lld%lld",&f[i],&h[i]);
		vec[f[i]].push_back(h[i]);
	}
	for(int i=1; i<=n; ++i)
		sort(vec[i].begin(),vec[i].end());
	for(int i=0; i<=n; ++i) {
		int cnt_l[N]= {0},cnt_r[N]= {0};
		for(int j=1; j<=i; ++j)++cnt_l[s[j]];
		for(int j=i+1; j<=n; ++j)++cnt_r[s[j]];
		int res=1,f1=!i,f2=i?1:0;
		for(int j=0;j<vec[s[i]].size();++j)
			if(vec[s[i]][j]==cnt_l[s[i]]) {
				f1=1;
				break;
			}
		if(!f1)continue;
		for(int j=1; j<=n; ++j) {
			int l=0,r=0;
			while(l<vec[j].size()&&cnt_l[j]>=vec[j][l])++l;
			while(r<vec[j].size()&&cnt_r[j]>=vec[j][r])++r;
			if(j==s[i])l=0,r-=cnt_r[j]>=cnt_l[j];
			if(l>r)swap(l,r);
			if(!(l+r))continue;
			else if(!l)res=res*r%mod,++f2;
			else if(r^1)res=res*l*(r-1)%mod,f2+=2;
			else res=(res<<1)%mod,++f2;
		}
		if(f2==mx)sum=(sum+res)%mod;
		else if(f2>mx)mx=f2,sum=res;
	}
	printf("%lld %lld\n",mx,sum);
	return 0;
}