#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100009;
int n,a[N],nxt[N][2],ans;
signed main() {
    n=rd();
    for(int i=1;i<=n;++i)a[i]=rd()-1;
    nxt[n][0]=n+1,nxt[n][1]=n+1;
    for(int i=n;i>=1;--i)
        nxt[i-1][0]=nxt[i][0],nxt[i-1][1]=nxt[i][1],nxt[i-1][a[i]]=i;
    for(int i=1;i<=n;++i) {
        int x=nxt[i][!a[i]],y=nxt[x][a[i]];
        ans=max(ans,2*min(x-i,y-x));
    }
    printf("%lld\n",ans);
    return 0;
}