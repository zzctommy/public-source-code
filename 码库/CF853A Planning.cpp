#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=300005;
struct node{
	int tim,val;
	friend bool operator < (const node &a,const node &b) {
		return a.val<b.val;
	}
	node(int t,int v) : tim(t) ,val(v) {}
};
priority_queue<node>q;
int n,ans,res[N],k;
signed main() {
	scanf("%lld%lld",&n,&k);
	for(int i=1,x;i<=k;++i) {
		scanf("%d",&x);
		q.push(node(i,x));
	} 
	for(int i=k+1,x;i<=n;++i) {
		scanf("%lld",&x);
		q.push(node(i,x));
		ans+=(i-q.top().tim)*q.top().val;
		res[q.top().tim]=i;
		q.pop();
	}
	for(int i=n+1;i<=n+k;++i) {
		ans+=(i-q.top().tim)*q.top().val;
		res[q.top().tim]=i;
		q.pop();
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;++i)
		printf("%lld ",res[i]);
	return 0;
}