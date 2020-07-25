#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=500010;
int n,k,a[N];
LL ans=-1145141919810,f[N][2],g[N][2],ANS;
int check(int x){
	f[0][0]=f[0][1]=g[0][0]=g[0][1]=0;
	for(int i=1;i<=n;++i)a[i]+=x;
	for(int i=1;i<=n;++i) {
		f[i][1]=f[i-1][0]+a[i],g[i][1]=g[i-1][0]+1;
		f[i][0]=f[i-1][1],g[i][0]=g[i-1][1];
		if(f[i-1][0]>f[i-1][1]||(f[i-1][0]==f[i-1][1]&&g[i-1][0]<g[i-1][1]))
			f[i][0]=f[i-1][0],g[i][0]=g[i-1][0];
	}
	for(int i=1;i<=n;++i)a[i]-=x;
	ANS=max(f[n][0],f[n][1]);
	if(f[n][0]>f[n][1]||(f[n][0]==f[n][1]&&g[n][0]<g[n][1]))return g[n][0];
	else return g[n][1];
}
signed main() {
	n=rd(),k=rd();
	int l=0,r=0;
	for(int i=1;i<=n;++i)a[i]=rd(),r=max(r,abs(a[i])),assert(abs(a[i])<=1000000);
	l=-r,r=0;
	if(check(0)<=k)return printf("%lld\n",ANS),0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid)<=k)ans=ANS-1ll*k*mid,l=mid+1;
		else r=mid-1;
	}
	if(ans==-1145141919810)ans=0;
	printf("%lld\n",ans);
	return 0;
}