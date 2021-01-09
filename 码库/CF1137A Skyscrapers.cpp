#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=1009;
int n,m,a[N][N],h[N][N],l[N][N];
signed main(){
    n=rd(),m=rd();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            a[i][j]=h[i][j]=l[j][i]=rd();
    for(int i=1;i<=n;++i)sort(h[i]+1,h[i]+m+1),h[i][0]=unique(h[i]+1,h[i]+m+1)-h[i]-1;
    for(int i=1;i<=m;++i)sort(l[i]+1,l[i]+n+1),l[i][0]=unique(l[i]+1,l[i]+n+1)-l[i]-1;
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=m;++j) {
            int x=lower_bound(h[i]+1,h[i]+h[i][0]+1,a[i][j])-h[i];
            int y=lower_bound(l[j]+1,l[j]+l[j][0]+1,a[i][j])-l[j];
            printf("%d ",max(x,y)+max(h[i][0]-x,l[j][0]-y));
        }
        puts("");
    }
    return 0;
}