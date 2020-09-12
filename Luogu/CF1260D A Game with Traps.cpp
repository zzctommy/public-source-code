#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int m,n,k,t,a[N];
struct node{
	int l,r,d;
}s[N];
bool cmp1(const int &a,const int &b) {
	return a>b;
}
bool pd(int x) {
	int dif[N]={0},sum=0;
	for(int i=1;i<=k;++i)
		if(s[i].d>a[x])++dif[s[i].l],--dif[s[i].r+1];
	for(int i=1;i<=n;++i) {
		dif[i]+=dif[i-1];
		if(dif[i])sum+=3;
		else ++sum;
	}
	return sum<=t;
}
int main() {
	scanf("%d%d%d%d",&m,&n,&k,&t);++n;
	for(int i=1;i<=m;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=k;++i)
		scanf("%d%d%d",&s[i].l,&s[i].r,&s[i].d);
	a[0]=100000007;
	sort(a+1,a+m+1,cmp1);
	int l=0,r=m,res;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(pd(mid))l=mid+1,res=mid;
		else r=mid-1;
	}
	printf("%d\n",res);
	return 0;
}