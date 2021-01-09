#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
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
#define N 100009
int n,k,a[N],ans,sum[N];
int solve(int p) {
    map<int,int>mp;
    int res=0;
    mp[0]=1;
    for(int i=1;i<=n;++i)
        res+=mp[sum[i]-p],++mp[sum[i]];
    return res;
}
signed main() {
    n=rd(),k=rd();
    for(int i=1;i<=n;++i)sum[i]=sum[i-1]+(a[i]=rd());
    if(k==-1)return printf("%lld\n",solve(1)+solve(-1)),0;
    if(k==1)return printf("%lld\n",solve(1)),0;
    for(int i=1;i<=1e14;i*=k)ans+=solve(i);
    printf("%lld\n",ans);
    return 0;
}