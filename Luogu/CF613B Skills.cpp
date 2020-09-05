#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100005;
int n,A,cf,cm,m,sum[N],ans=-1,rk,v,b[N];
struct node{
	int val,id;
}a[N];
bool cmp(const node &a,const node &b) {
	return a.val<b.val;
}
int find(int sum,int x) {
	int l=0,r=x,res;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(a[mid].val<sum)res=mid,l=mid+1;
		else r=mid-1;
	} 
	return res;
}
signed main() {
	scanf("%lld%lld%lld%lld%lld",&n,&A,&cf,&cm,&m);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i].val),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i].val;
	m+=sum[n];
	for(int i=1;i<=n+1;++i) {
		if(A*(n-i+1)+sum[i-1]>m)continue;
		int l=a[1].val,r=A,res;
		while(l<=r) {
			int mid=(l+r)>>1;
			int t=find(mid,i-1);
			if(A*(n-i+1)+mid*t+sum[i-1]-sum[t]<=m)res=mid,l=mid+1;
			else r=mid-1;
		}
		if(ans<res*cm+(n-i+1)*cf) {
			ans=res*cm+(n-i+1)*cf;
			rk=i,v=res;
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<rk;++i)a[i].val=max(a[i].val,v);
	for(int i=rk;i<=n;++i)a[i].val=A;
	for(int i=1;i<=n;++i)b[a[i].id]=a[i].val;
	for(int i=1;i<=n;++i)printf("%lld ",b[i]);
	return 0;
 } 