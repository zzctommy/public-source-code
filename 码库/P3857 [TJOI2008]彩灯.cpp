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
const int mod=2008;
int n,m,ele;
char s[70];
LL d[70];
void ins(LL x) {
	for(rint i=50;i>=0;--i) {
		if(x>>i&1) {
			if(d[i])x^=d[i];
			else {d[i]=x,++ele;break;}
		}
	}
} 
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=m;++i) {
		scanf("%s",s);LL x=0;
		for(rint j=0;j<n;++j)if(s[j]=='O')x|=1ll<<j;
		ins(x);
	}
	printf("%lld\n",(1ll<<ele)%mod);
	return 0;
}
