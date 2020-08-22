#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200010;
const int inf=1e9+7;
int n,k,T,a[N];
void Main() {
	n=rd();int f=1;
	for(int i=1;i<=n;++i)a[i]=rd(),f&=a[i]==a[1];
	if(f)printf("%lld\n",n);
	else puts("1");
}
signed main() {
	for(T=rd();T;--T)Main();
}