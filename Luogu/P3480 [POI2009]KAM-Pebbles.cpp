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
const int N=1010;
int T,n,a[N];
void Main() {
	n=rd();int res=0;
	for(rint i=1;i<=n;++i)a[i]=rd();
	for(rint i=n;i>=1;i-=2)res^=a[i]-a[i-1];
	if(res)puts("TAK");
	else puts("NIE");
}
signed main() {
	T=rd();
	while(T--)Main();
	return 0;
}
