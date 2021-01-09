#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=110;
int T,t[N],l[N],r[N],n,m,L,R;
bool flag;
int main() {
	T=rd();
	while(T--) {
		n=rd(),m=rd();L=R=m;flag=1;
		for(rint i=1;i<=n;++i)t[i]=rd(),l[i]=rd(),r[i]=rd();
		for(rint i=1;i<=n;++i) {
			L-=t[i]-t[i-1],R+=t[i]-t[i-1];
			if(L>r[i]||R<l[i]) {flag=0;break;}
			L=max(L,l[i]),R=min(R,r[i]);
		}
		puts(flag?"YES":"NO");
	}
	return 0;
}