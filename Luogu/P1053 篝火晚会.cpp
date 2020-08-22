#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=50009;
int n,a[N][2],cnt[N];
int x[N],vis[N],ans=0x3f3f3f3f;
int solve() {
	memset(vis,0,sizeof(vis));
	int res=0;
	for(int i=1;i<=n;++i)
		++vis[(i-x[i]+n)%n],res=max(res,vis[(i-x[i]+n)%n]);
	return n-res;
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i) {
		a[i][0]=rd(),a[i][1]=rd();
		++cnt[a[i][0]],++cnt[a[i][1]];
	}
	x[1]=1,x[0]=a[1][0];
	for(int i=1;i<=n;++i)x[i+1]=a[x[i]][0]==x[i-1]?a[x[i]][1]:a[x[i]][0];
	if((a[x[n]][0]==x[n-1]?a[x[n]][1]:a[x[n]][0])!=x[1])return puts("-1"),0;
	ans=min(ans,solve());
	x[1]=1,x[0]=a[1][1];
	for(int i=1;i<=n;++i)x[i+1]=a[x[i]][0]==x[i-1]?a[x[i]][1]:a[x[i]][0];
	ans=min(ans,solve());
	printf("%d\n",ans);
	return 0;
}
