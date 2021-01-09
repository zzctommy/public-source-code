#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,ans1,ans2;
char r[]={'D','A','C','B'};
signed main() {
    cin>>n;
    ans1=n,ans2=r[n%4];
    ++n;
    if(r[n%4]<ans2)ans1=n,ans2=r[n%4];
    ++n;
    if(r[n%4]<ans2)ans1=n,ans2=r[n%4];
    n-=2;
    printf("%lld %c\n",ans1-n,ans2);
    return 0;
}