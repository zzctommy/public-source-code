#include<bits/stdc++.h>
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
typedef long long LL;
#define rint register int
inline int rd() {
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int n,m,a[N],l[N],r[N],tmp[N];
LL ans;
map<int,int>mp;
signed main() {
	n=rd(),m=rd();
	if(n==1)return puts("0"),0;
	for(rint i=1;i<=m;++i)a[i]=rd();
	for(rint i=m;i>=1;--i)
		tmp[i]=a[i]+i,mp[tmp[i]]=mp[tmp[i]+1]+1;
	for(rint i=1;i<=n;++i)
		l[i]=max(i-m-1+mp[i],1);
	mp.clear();
	for(rint i=m;i>=1;--i)
		tmp[i]=a[i]-i,mp[tmp[i]]=mp[tmp[i]-1]+1;
	for(rint i=1;i<=n;++i)
		r[i]=min(m+i+1-mp[i],n);
	for(rint i=1;i<=n;++i)
		ans+=r[i]-l[i]+1;
	printf("%lld\n",ans);
	return 0;
}