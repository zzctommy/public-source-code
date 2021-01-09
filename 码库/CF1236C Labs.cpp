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
int n,a[305][305],cnt;
signed main() {
	n=rd();
	for(rint j=1;j<=n;++j)
		for(rint i=1;i<=n;++i)a[i][j]=++cnt;
	for(rint i=1;i<=n;i+=2)
		for(rint j=1;j<=n/2;++j)swap(a[n-j+1][i],a[j][i]);
	for(rint i=1;i<=n;++i) {
		for(rint j=1;j<=n;++j)printf("%d ",a[i][j]);
		putchar('\n');
	}
	return 0;
}