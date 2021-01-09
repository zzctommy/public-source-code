#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define F(i,l,r) for(int i=l;i<=r;++i)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,a,b,sa,sb;
signed main() {
	n=rd();
	for(int i=1;i<=2*n;++i) {
		a=rd(),b=rd();
		sa+=a,sb+=b;
	}
	printf("%lld %lld\n",sa/n,sb/n);
	return 0;
}