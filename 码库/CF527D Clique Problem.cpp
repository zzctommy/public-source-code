#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,las=-1e9-7,ans;
struct node{
	int l,r;
}a[N];
bool cmp(const node &a,const node &b) {
	return a.r^b.r?a.r<b.r:a.l<b.l;
}
int main() {
	scanf("%d",&n);
	for(int i=1,x,w;i<=n;++i)
		scanf("%d%d",&x,&w),a[i].l=x-w,a[i].r=x+w;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
		if(las<=a[i].l)++ans,las=a[i].r;
	printf("%d\n",ans);
	return 0;
}