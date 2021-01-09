#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=1010;
int n,m,c,x,a[N];
bool check() {
	for(rint i=1;i<=n;++i)if(!a[i]||a[i]<a[i-1])return 0;
	return 1;
}
signed main() {
	scanf("%d%d%d",&n,&m,&c);
	while(m--) {
		scanf("%d",&x);
		if(x*2<=c){for(rint i=1;i<=n;++i)if(!a[i]||a[i]>x) {printf("%d\n",i),a[i]=x;break;}}
		else      {for(rint i=n;i>=1;--i)if(!a[i]||a[i]<x) {printf("%d\n",i),a[i]=x;break;}}
		fflush(stdout);
		if(check())return 0;
	}
}