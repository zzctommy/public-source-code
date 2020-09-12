#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200005;
int T,n,l,r,sum[N];
char s[N]; 
int f(char c)
{
	if(c=='L')return -1;
	if(c=='R')return 1;
	if(c=='U')return N;
	if(c=='D')return -N;
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%s",&n,s+1);
		for(int i=1;i<=n;++i)
			sum[i]=sum[i-1]+f(s[i]);
		//for(int i=1;i<=n;++i)cout<<sum[i]<<" ";puts("");
		unordered_map<int,int>mp;
		l=-1,r=n+1;
		for(int i=0;i<=n;++i)
		{
			if(mp.count(sum[i])&&i-mp[sum[i]]+1<r-l+1)
				l=mp[sum[i]]+1,r=i;
			mp[sum[i]]=i;
		}
		if(l==-1)puts("-1");
		else printf("%lld %lld\n",l,r);
	}
	return 0;
 } 