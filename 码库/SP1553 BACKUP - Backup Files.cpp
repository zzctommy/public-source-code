#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
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
const int N=100010;
const int inf=1e13;
int n,m,a[N];
LL ans=-1145141919810,f[N],g[N],ANS;
int check(int x){
	for(int i=1;i<=n;++i)a[i]+=x;
	if(a[1]>=0)f[1]=a[1],g[1]=1;
	else f[1]=0,g[1]=0;
	for(int i=2;i<=n;++i) {
		if(f[i-1]>f[i-2]+a[i])f[i]=f[i-1],g[i]=g[i-1];
		else f[i]=f[i-2]+a[i],g[i]=g[i-2]+1;
	}
	for(int i=1;i<=n;++i)a[i]-=x;
	ANS=f[n];return g[n];
}
void Main() {
	n=rd(),m=rd();
	int l=0,r=0;
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<n;++i)a[i]=a[i]-a[i+1];
	--n;
	l=-inf,r=inf;
	while(l<=r) {
		int mid=(l+r)>>1,k=check(mid);
		if(k>=m)ans=ANS-1ll*m*mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",-ans);
}
signed main() {
	for(int T=rd();T;--T)Main();
}