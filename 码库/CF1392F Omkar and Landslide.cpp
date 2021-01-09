#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1000009;
int n,a[N],sum;
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)sum+=(a[i]=rd());
	int l=1,r=sum/n,res=sum;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(n*(2*mid+n-1)/2>=sum)res=mid,r=mid-1;
		else l=mid+1;
	}
	--res;
	int k=sum-n*(2*res+n-1)/2;
	for(int i=1;i<=k;++i)printf("%lld ",i+res);
	for(int i=k+1;i<=n;++i)printf("%lld ",i+res-1);
	return 0;
}