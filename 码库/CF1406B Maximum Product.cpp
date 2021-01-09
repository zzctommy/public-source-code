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
const int N=100005;
int n,a[N];
vector<int>f,g;
LL ans;
void Main() {
	n=rd(),ans=-1e18,f.clear(),g.clear();
	for(int i=1;i<=n;++i)a[i]=rd(),a[i]>0?f.push_back(a[i]):g.push_back(a[i]);
	sort(f.begin(),f.end()),reverse(f.begin(),f.end()),sort(g.begin(),g.end());
	if(!f.size()) {
		reverse(g.begin(),g.end()),ans=1;
		for(int i=0;i<5;++i)ans*=g[i];
		printf("%lld\n",ans);
	} else {
		for(int i=0;i<=5;++i) {
			int j=5-i;
			if(f.size()>=i&&g.size()>=j) {
				LL t=1;
				for(int k=0;k<i;++k)t*=f[k];
				for(int k=0;k<j;++k)t*=g[k];
				ans=max(ans,t);
			}
		}
		printf("%lld\n",ans);	
	}
}
signed main() {
	for(int T=rd();T;--T)Main();
}
