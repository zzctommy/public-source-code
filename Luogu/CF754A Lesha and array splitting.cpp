#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,a[1005],sum;
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),sum+=a[i];
	if(sum) return printf("YES\n1\n1 %d\n",n),0;
	for(int i=1;i<=n;++i)
		if(a[i])return printf("YES\n2\n1 %d\n%d %d\n",i,i+1,n),0;
	puts("NO");
}