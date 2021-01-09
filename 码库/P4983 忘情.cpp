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
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=100010;
const int inf=1e9;
int n,m,a[N],s[N];
int dp[N],cnt[N],ANS,ans,q[N],H,T;
int X(int i){return s[i];}
int Y(int i){return dp[i]+s[i]*s[i]-2*s[i];}
double slope(int i,int j) {
    return 1.0*(Y(i)-Y(j))/(X(i)-X(j));
}
int val(int l,int r) {
    return (s[r]-s[l-1]+1)*(s[r]-s[l-1]+1);
}
int check(int x) {
    q[H=T=1]=0;
    for(int i=1;i<=n;++i) {
        while(H<T&&slope(q[H],q[H+1])<=2*s[i])++H;
        int j=q[H];cnt[i]=cnt[j]+1,dp[i]=dp[j]+val(j+1,i)+x;
        while(H<T&&slope(q[T-1],q[T])>=slope(q[T],i))--T;
        q[++T]=i;
    }
    ANS=dp[n];return cnt[n];
}
signed main() {
    n=rd(),m=rd();
    for(int i=1;i<=n;++i)a[i]=rd(),s[i]=s[i-1]+a[i];
    int l=0,r=1e15;
    while(l<=r) {
        int mid=(l+r)>>1,k=check(mid);
        if(k>=m)ans=ANS-m*mid,l=mid+1;
        else r=mid-1;
    }
    printf("%lld\n",ans);
    return 0;
}