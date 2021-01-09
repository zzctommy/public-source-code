#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rint register int
#define il inline
il int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
   return x*f;
}
const int N=100005;
map<int,ll>mp[3];
#define IT map<int,ll>::iterator
int n,a[N],u;
int gcd(const int &x,const int &y) {
	return y?gcd(y,x%y):x;
}
int main() {
	n=rd();
	for(rint i=1,x;i<=n;++i) {
		x=rd();u^=1;
		mp[u].clear();
		++mp[u][x];
		for(IT it=mp[u^1].begin();it!=mp[u^1].end();++it)
			mp[u][gcd(it->first,x)]+=it->second;
		for(IT it=mp[u].begin();it!=mp[u].end();++it)
			mp[2][it->first]+=it->second;
	}
	for(rint i=rd();i>=1;--i)
		printf("%lld\n",mp[2][rd()]);
	return 0;
} 