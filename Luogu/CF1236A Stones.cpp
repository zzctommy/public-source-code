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
int T,a,b,c,ans;
signed main() {
	T=rd();
	while(T--) {
		a=rd(),b=rd(),c=rd(),ans=0;
		while(c>=2&&b>=1)c-=2,b-=1,ans+=3;
		while(a>=1&&b>=2)b-=2,a-=1,ans+=3;
		printf("%d\n",ans);
	}
	return 0;
}