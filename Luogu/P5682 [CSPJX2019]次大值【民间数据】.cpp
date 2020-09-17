#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200005;
int n,a[N],flg;
signed main() {
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	sort(a+1,a+n+1),n=unique(a+1,a+n+1)-a-1;
	if(n<2)puts("-1");
	else printf("%d\n",max(a[n]%a[n-1],a[n-2]));
	return 0;
}
