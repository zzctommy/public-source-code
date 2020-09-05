#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
#define N (200010)
#define inf (1000000000000000)
int n,k,a[N],b[N],l,r,ans=-1;
struct node{
	int a,b,val;
	node(int a,int b):a(a),b(b),val(a/b){}
	bool operator < (const node &rhs)const{return val>rhs.val;}
};
bool check(int x) {
	priority_queue<node>q;
	for(rint i=1;i<=n;++i)
		if(a[i]/b[i]<k)q.push(node(a[i],b[i]));
	if(q.empty())return 1;
	for(rint i=0;i<k;++i) {
		node tmp=q.top();q.pop();
		if(tmp.a-i*tmp.b<0)return 0;
		tmp.a+=x;
		if(tmp.a/tmp.b<k)q.push(node(tmp.a,tmp.b));
		if(q.empty())return 1;
	}
	return 1;
}
signed main() {
	scanf("%lld%lld",&n,&k);
	for(rint i=1;i<=n;++i)scanf("%lld",&a[i]);
	for(rint i=1;i<=n;++i)scanf("%lld",&b[i]),r=max(r,b[i]*k);
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}