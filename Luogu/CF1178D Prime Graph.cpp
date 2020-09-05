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
int n,m;
bool isp(int x) {
	for(rint i=2;i*i<=x;++i)
		if(x%i==0)return 0;
	return 1;
}
signed main() {
	n=rd();
	for(m=n;;++m)if(isp(m))break;
	printf("%d\n",m);
	for(rint i=1;i<=n;++i)printf("%d %d\n",i,i%n+1);
	for(rint i=1;i<=m-n;++i)printf("%d %d\n",i,(i+n/2-1)%n+1);
	return 0;
}