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
int n;
vector<int>ans;
int f(int a1,int n,int d) {
	return (a1+a1+d*(n-1))*n/2;
}
signed main() {
	n=rd();
	for(int i=1;i*i<=n;++i) {
		if(n%i)continue;
		ans.pb(f(1,n/i,i));
		if(i*i!=n)ans.pb(f(1,i,n/i));
	}
	sort(ans.begin(),ans.end());
	for(int i:ans)printf("%lld ",i);
	return 0;
}