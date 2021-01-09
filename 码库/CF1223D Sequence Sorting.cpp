#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=3e5+10;
int T,n,m,a[N],lsh[N],len,fir[N],lst[N],ans,dp[N];
#define lt(i) (i&(-i))
void Main() {
	n=rd(),ans=0;
	for(rint i=1;i<=n;++i)lsh[i]=a[i]=rd(),fir[i]=lst[i]=dp[i]=0;
	for(rint i=1;i<=n;++i) {
		if(!fir[a[i]])fir[a[i]]=i;
		lst[a[i]]=i;
	}
	sort(a+1,a+n+1),len=unique(a+1,a+n+1)-a-1;
	for(rint i=1;i<=len;++i) {
		if(fir[a[i]]>lst[a[i-1]])dp[a[i]]=dp[a[i-1]]+1;
		else dp[a[i]]=1;ans=max(ans,dp[a[i]]);
	}
	printf("%d\n",len-ans);
}
signed main() {
	T=rd();
	while(T--)Main();
	return 0;
}