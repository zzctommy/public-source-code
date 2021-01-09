
#include<bits/stdc++.h>
using namespace std;
#define N 300005
int n,a[N];
long long ans;
priority_queue<int,vector<int>,greater<int> >q;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		q.push(a[i]),q.push(a[i]);
		ans+=a[i]-q.top(),q.pop();
	}
	printf("%lld\n",ans);
	return 0;
}