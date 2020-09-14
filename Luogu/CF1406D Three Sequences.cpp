#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
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
const int N=100005;
int n,a[N],now;
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=n;i>1;--i)a[i]-=a[i-1],now+=max(0ll,a[i]);
	printf("%lld\n",(now+a[1]+1)>>1);
	for(int q=rd();q;--q) {
		int l=rd(),r=rd(),x=rd();
		if(l>1)now-=max(0ll,a[l]),now+=max(0ll,a[l]+=x);
		else a[1]+=x;
		if(r<n)now-=max(0ll,a[r+1]),now+=max(0ll,a[r+1]-=x);
		printf("%lld\n",(now+a[1]+1)>>1);
	}
	return 0;
}
