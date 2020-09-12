#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200010;
int T,n,a[N],p[N];
signed main() {
	T=rd();
	while(T--) {
		n=rd();int mi=n,mx=1;
		for(rint i=1;i<=n;++i)a[i]=rd(),p[a[i]]=i;
		for(rint i=1;i<=n;++i) {
			mi=min(mi,p[i]),mx=max(mx,p[i]);
			if(mx-mi+1==i)putchar('1');
			else putchar('0');
		}
		puts("");
	}
	return 0;
}