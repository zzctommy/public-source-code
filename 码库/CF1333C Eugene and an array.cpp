#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline LL rd(){
   LL x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=200010;
LL n,a[N],ans;
map<LL,int>mp;
signed main() {
	n=rd();mp[0]=0;
	for(rint i=1;i<=n;++i) a[i]=rd()+a[i-1];
	for(rint i=1,pos=0;i<=n;++i) {
		if(mp.count(a[i]))pos=max(pos,mp[a[i]]+1);
		ans+=i-pos;
		mp[a[i]]=i;
	}
	printf("%lld\n",ans);
	return 0;
}