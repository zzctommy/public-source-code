#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=105;
int n,m,a[N][N],ans,id;
pair<int,int> b[N][N];
signed main(){
    n=read(),m=read(),ans=m+1;
    for(int i=1;i<=m;++i)
        for(int j=1;j<=n;++j)
            a[i][j]=read(),b[j][i].first=a[i][j];
    for(int i=1;i<n;++i){
        for(int j=1;j<=m;++j)
            b[i][j].first=b[i][j].first-b[n][j].first,b[i][j].second=j;
        sort(b[i]+1,b[i]+m+1);
        // rep(j,1,m)printf("%d%c",b[i][j].second," \n"[j==m]);
        int now=m,sum=0;
        for(int j=m;j>=1;--j){
            sum+=b[i][j].first;
            if(sum<0)break;
            --now;
        }
        if(now<ans)id=i,ans=now;
    }
    printf("%d\n",ans);
    for(int j=1;j<=ans;++j)printf("%d ",b[id][j].second);
    return 0;
}