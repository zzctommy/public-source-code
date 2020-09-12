#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200005;
const int inf=1e15;
int T,n,s,l,r,ans;
inline int max(const int &a,const int &b) {
	return a>b?a:b;
}
inline int min(const int &a,const int &b) {
	return a<b?a:b;
}
struct node {
	int l,r;
}a[N];
bool cmp(const node &a,const node &b) {
	return a.l<b.l;
}
bool check(int x) {
	int sum=n/2+1,total=s;
	for(int i=n;i>=1;--i) {
		if(a[i].r>=x&&sum) {
			total-=max(x,a[i].l);
			--sum;
		} else {
			total-=a[i].l;
		}
	}
	return (!sum)&&(total>=0);
}
signed main() {
	scanf("%lld",&T);
	while(T--) {
		l=inf,r=0;
		scanf("%lld%lld",&n,&s);
		for(int i=1;i<=n;++i)
			scanf("%lld%lld",&a[i].l,&a[i].r),l=min(l,a[i].l),r=max(r,a[i].r);
		sort(a+1,a+n+1,cmp);
		while(l<=r) {
			int mid=(l+r)>>1;
			if(check(mid))ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}