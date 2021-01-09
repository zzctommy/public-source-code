#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=5009;
int n,sum;
char s[N],t[N];
#define sz(s) ((int)s.size())
vector<int>g[3];
signed main() {
    scanf("%d%s%s",&n,s+1,t+1);
    for(int i=1;i<=n;++i) {
        int x=s[i]-'0',y=t[i]-'0';
        sum+=y,g[x+y].push_back(i);
    }
    for(int t2=0;t2<=sz(g[2]);++t2) {
        int t1=sum-t2*2,t0=n/2-t2-t1;
        if(t0<0||t1<0||t0>sz(g[0])||t1>sz(g[1]))continue;
        for(int j=0;j<t0;++j)printf("%d ",g[0][j]);
        for(int j=0;j<t1;++j)printf("%d ",g[1][j]);
        for(int j=0;j<t2;++j)printf("%d ",g[2][j]);
        return 0;
    }
    puts("-1");
}