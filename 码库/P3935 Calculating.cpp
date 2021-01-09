#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
const int mod=998244353;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int sum(int x) {
    int res=0;
    for(int l=1,r;l<=x;l=r+1)
        r=x/(x/l),res=(res+(r-l+1)*(x/l))%mod;
    return res;
}
signed main() {
    int x=rd(),y=rd();
    printf("%lld\n",(sum(y)-sum(x-1)+mod)%mod);
    return 0;
}