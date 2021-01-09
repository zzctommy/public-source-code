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
int T,a,b,c;
signed main() {
	T=rd();
	while(T--) {
		a=rd(),b=rd(),c=rd();
		for(rint i=1;i<=b;++i) {
			int t=a/2+10;
			if(t>a)break;
			a=t;
		} 
		a-=c*10;
		if(a<=0)puts("YES");
		else puts("NO");
	}
	return 0;
}