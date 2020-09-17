#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const int M=50005;
int ans,a[N],n=1,dp1[N],dp2[N];
struct BIT1 {
	int tr[M];
	#define lt(i) (i&(-i))
	void add(int x,int d) {
		if(x<=0)return;
		for(int i=x;i>0;i-=lt(i))
			tr[i]=max(tr[i],d);
	}
	int ask(int x) {
		if(x>=M)x=M-1;
		int res=0;
		for(int i=x;i<M;i+=lt(i))
			res=max(res,tr[i]);
		return res;
	}
}tr1;
struct BIT2 {
	int tr[M];
	#define lt(i) (i&(-i))
	void add(int x,int d) {
		if(x<=0)return;
		for(int i=x;i<M;i+=lt(i))
			tr[i]=max(tr[i],d);
	}
	int ask(int x) {
		if(x>=M)x=M-1;
		int res=0;
		for(int i=x;i>0;i-=lt(i))
			res=max(res,tr[i]);
		return res;
	}
}tr2;
int main() {
	while(scanf("%d",&a[n])!=EOF)++n;
	--n;
	for(int i=1;i<=n;++i) {
		int tmp=tr1.ask(a[i])+1;
		ans=max(ans,tmp);
		tr1.add(a[i],tmp);
	}
	printf("%d\n",ans);
	ans=0;
	for(int i=1;i<=n;++i) {
		int tmp=tr2.ask(a[i])+1;
		dp2[i]=tmp;
		ans=max(ans,tmp);
		tr2.add(a[i]+1,tmp);
	}
	printf("%d\n",ans);
	return 0;
}
