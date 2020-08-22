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
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300009;
int n,a[N],cnt[2];
LL ans;
signed main() {
	n=rd();
	for(int i=1;i<=n;++i) {
		a[i]=rd();
		if(a[i]&1)++cnt[i&1];
		ans+=a[i]/2;
	}
	ans+=min(cnt[0],cnt[1]);
	printf("%lld\n",ans);
	return 0;
}