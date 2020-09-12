#include<bits/stdc++.h>
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
typedef long long LL;
#define int long long
#define rint register int
inline int rd() {
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod=1e9+7;
int qpow(int n,int k,int p) {
	int res=1;
	while(k) {
		if(k&1)res=res*n%p;
		n=n*n%p,k>>=1;
	} 
	return res;
}
signed main() {
	int n=rd(),m=rd();
	printf("%lld\n",qpow(qpow(2,m,mod)-1,n,mod));
	return 0;
}