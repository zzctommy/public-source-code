#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=300005;
struct node {
	int t,w;
	friend bool operator < (const node &a,const node &b) {
		return a.w-a.t>b.w-b.t;
	}
} a[N];
bool cmp(const node &a,const node &b) {
	return a.t>b.t;
}
int n,ans;
priority_queue<node>q;
signed main() {
	scanf("%lld",&n);
	for(int i=1; i<=n; ++i)
		scanf("%lld%lld",&a[i].t,&a[i].w);
	sort(a+2,a+n+1,cmp);
	int it=2,sum=0;
	while("fyy ak ioi") {
		while(a[it].t>a[1].t&&it<=n)q.push(a[it++]);
		ans=max(ans,n-it+1+sum);
		if(!q.empty()&&q.top().w-q.top().t+1<=a[1].t)
			a[1].t-=q.top().w-q.top().t+1,q.pop(),++sum;
		else break;
	}
	printf("%lld\n",n-ans);
	return 0;
}