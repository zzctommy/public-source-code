#include <bits/stdc++.h>
using namespace std;
#define rint register int
const int N=100010;
int n,m,a[N];
long long ans,s;
vector<int>v[N];
int main() {
	scanf("%d%d",&n,&m);
	for(rint i=1;i<=m;++i)scanf("%d",&a[i]);
	for(rint i=1;i<m;++i) {
		s+=abs(a[i]-a[i+1]);
		if(a[i]!=a[i+1]) {
			v[a[i]].push_back(a[i+1]);
			v[a[i+1]].push_back(a[i]);
		}
	}
	ans=s;
	long long sum,lst;
	for(rint i=1;i<=n;++i) {
		if(!v[i].size())continue;
		sum=lst=0;
		for(rint j=0;j<v[i].size();++j)
			lst+=abs(i-v[i][j]);
		int mid=v[i].size()/2;
		nth_element(v[i].begin(),v[i].begin()+mid,v[i].end());
		for(rint j=0;j<v[i].size();++j)
			sum+=abs(v[i][mid]-v[i][j]);
		ans=min(ans,s-lst+sum);
	}
	printf("%lld\n",ans);
	return 0;
}