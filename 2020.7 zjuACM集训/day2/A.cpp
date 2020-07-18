#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=4e6+10;
const int M=40010;
int n,a[N],m,tot,cnt;
LL ans[M];
int val[N],sum[N];
int gcd(int x,int y) {
	return !y?x:gcd(y,x%y);
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=1;i<=n;++i) {
		cnt=0;
		for(rint j=1;j<=tot;++j)val[j]=gcd(val[j],a[i]);
		for(rint j=1;j<=tot;++j) {
			if(val[j]!=val[cnt])val[++cnt]=val[j],sum[cnt]=sum[j];
			 else sum[cnt]+=sum[j];
		}
		tot=cnt;
		if(a[i]!=val[tot])val[++tot]=a[i],sum[tot]=1;
		else ++sum[tot];
		for(rint j=1;j<=tot;++j)ans[val[j]]+=sum[j];
	}
	m=rd();
	while(m--)printf("%lld\n",ans[rd()]);
	return 0;
}
