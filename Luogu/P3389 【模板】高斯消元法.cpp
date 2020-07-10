#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=110;
const double eps=1e-7;
int n;
double a[N][N],ans[N];
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)
		for(rint j=1;j<=n+1;++j)
			scanf("%lf",&a[i][j]);
	for(rint i=1;i<=n;++i) {
		int mx=i;
		for(rint j=i;j<=n;++j)
			if(fabs(a[mx][i])<fabs(a[j][i]))mx=j;
		for(rint j=1;j<=n+1;++j)swap(a[mx][j],a[i][j]);
		if(fabs(a[i][i])<eps)return puts("No Solution"),0;
		for(rint j=1;j<=n;++j) {
			if(i==j)continue;
			double div=a[j][i]/a[i][i];
			for(rint k=i+1;k<=n+1;++k) {
				a[j][k]-=div*a[i][k];
			}
		}
	}
	for(rint i=1;i<=n;++i)ans[i]=a[i][n+1]/a[i][i];
	for(rint i=1;i<=n;++i)printf("%.2lf\n",ans[i]);
	return 0;
}
