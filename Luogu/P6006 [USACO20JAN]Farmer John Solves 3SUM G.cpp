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
const int N=6009;
const int M=2000000;
int n,q,a[N],g[N][N],mp[M*2+114514];
LL f[N][N];
signed main() {
	n=rd(),q=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=n;++i) {
		for(int j=i+1;j<=n;++j) {
			int t=a[i]+a[j]+M;
			if(0<=t&&t<=M*2)g[i][j]=mp[t];
			++mp[M-a[j]];
		}
		for(int j=i+1;j<=n;++j)mp[M-a[j]]=0;
	}
	for(int len=3;len<=n;++len) {
		for(int i=1;i<=n;++i) {
			int j=i+len-1;
			if(j>n)break;
			f[i][j]=f[i+1][j]+f[i][j-1]-f[i+1][j-1]+g[i][j];
		}
	}
	while(q--) {
		int x=rd(),y=rd();
		printf("%lld\n",f[x][y]);
	}
}
