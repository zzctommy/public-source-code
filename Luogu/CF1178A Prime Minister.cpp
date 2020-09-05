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
int n,a[N],sum,num,ans1=1;
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd(),num+=a[i];
	sum=a[1];
	for(rint i=2;i<=n;++i)if(a[i]*2<=a[1])sum+=a[i],++ans1;
	if(sum*2<=num)return puts("0"),0;
	printf("%d\n1",ans1);
	for(rint i=2;i<=n;++i)if(a[i]*2<=a[1])printf(" %d",i);
	return 0;
}