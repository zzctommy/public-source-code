#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod=998244353;
int sum(int n) {
	int res=0;
	for(int l=1,r;l<=n;l=r+1)
		r=n/(n/l),res=(res+(r-l+1)*(n/l)%mod)%mod;
	return res;
}
signed main() {
	int l=rd(),r=rd();
	printf("%lld\n",(sum(r)-sum(l-1)+mod)%mod);
}