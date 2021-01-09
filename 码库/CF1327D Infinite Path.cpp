#include<bits/stdc++.h>
using namespace std;
#define rint register int
const int inf=1000000007;
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=200010;
int T,n,p[N],c[N],ans;
vector<int>fac,a;
bool vis[N];
void getfac(int x) {
	fac.clear();
	for(rint i=1,mx=sqrt(x);i<=mx;++i) {
		if(x%i==0) {
			fac.push_back(i);
			if(i*i!=x)fac.push_back(x/i);
		}
	}
	sort(fac.begin(),fac.end());
}
void calc() {
	getfac(a.size());
	for(rint i=0;i<fac.size();++i) {
		int k=fac[i];
		for(rint j=0;j<k;++j) {
			int flg=1;
			for(rint l=j;l<a.size();l+=k)flg&=(a[j]==a[l]);
			if(flg){ans=min(ans,k);return;}
		}
	}
}
signed main() {
	T=rd();
	while(T--) {
		n=rd();ans=inf;
		for(rint i=1;i<=n;++i)p[i]=rd();
		for(rint i=1;i<=n;++i)c[i]=rd();
		for(rint i=1;i<=n;++i)vis[i]=0;
		for(rint i=1;i<=n;++i) {
			if(!vis[i]) {
				a.clear();
				a.push_back(c[i]);vis[i]=1;
				for(rint j=p[i];j!=i;j=p[j])
					a.push_back(c[j]),vis[j]=1;
				calc();
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}