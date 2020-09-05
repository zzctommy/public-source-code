#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
#define int long long
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=100010;
int n,p,l,r,ans;
int pri[15],cnt,jc[N],jv[N],t[N][15];
int phi(int x) {
	int res=x;
	for(rint i=2;i*i<=x;++i) {
		if(x%i)continue;
		res-=res/i;
		while(x%i==0)x/=i;
	}
	if(x>1)res-=res/x;
	return res;
}
int qpow(int n,int k) {
	int res=1;
	while(k) {
		if(k&1)res=res*n%p;
		n=n*n%p,k>>=1;
	}
	return res;
}
void init() {
	int tmp=p;
	for(rint i=2;i*i<=tmp;++i) {
		if(tmp%i)continue;
		pri[++cnt]=i;
		while(tmp%i==0)tmp/=i;
	}
	if(tmp>1)pri[++cnt]=tmp;
	jc[0]=jv[0]=jc[1]=jv[1]=1;
	int P=phi(p);
	for(rint i=2;i<=n;++i) {
		int x=i;
		for(rint j=1;j<=cnt;++j) {
			t[i][j]=t[i-1][j];
			while(x%pri[j]==0)++t[i][j],x/=pri[j];
		}
		jc[i]=jc[i-1]*x%p,jv[i]=qpow(jc[i],P-1);
	}
}
int C(int n,int m) {
	if(m>n||m<0)return 0;
	if(m==0)return 1;
	int res=jc[n]*jv[m]%p*jv[n-m]%p;
	for(rint i=1;i<=cnt;++i)
		res=res*qpow(pri[i],t[n][i]-t[m][i]-t[n-m][i])%p;
	return res;
}
signed main() {
	n=rd(),p=rd(),l=rd(),r=rd();
	init();
	for(rint i=0;i<=n-l;++i)
		ans=(ans+C(n,i)*(C(n-i,(n-i-l)>>1)-C(n-i,(n-i-r-1)>>1)+p)%p)%p;
	printf("%lld\n",ans);
	return 0;
}