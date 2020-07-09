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
double a;
double f(double x) {return pow(x,a/x-x);}
double simpson(double l,double r) {return (f(l)+4*f((l+r)/2)+f(r))*(r-l)/6;}
double work(double l,double r,double eps,double val) {
	double mid=(l+r)/2,lv=simpson(l,mid),rv=simpson(mid,r);
	if(abs(lv+rv-val)<15*eps)return lv+rv+(lv+rv-val)/15;
	return work(l,mid,eps/2,lv)+work(mid,r,eps/2,rv);
}
signed main() {
	double eps=1e-6;
	scanf("%lf",&a);if(a<0)return puts("orz"),0;
	printf("%.5lf\n",work(eps,15,eps,simpson(eps,15)));
	return 0;
}
