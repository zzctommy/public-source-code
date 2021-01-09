#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
typedef long long LL;
#define N 1009
int n,h,r,F[N],x[N],y[N],z[N];
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
LL dis(int i,int j){return 1ll*(x[i]-x[j])*(x[i]-x[j])+1ll*(y[i]-y[j])*(y[i]-y[j])+1ll*(z[i]-z[j])*(z[i]-z[j]);}
void Main() {
    n=rd(),h=rd(),r=rd();
    for(int i=1;i<=n+2;++i)F[i]=i;
    for(int i=1;i<=n;++i) {
        x[i]=rd(),y[i]=rd(),z[i]=rd();
        if(z[i]<=r)F[find(i)]=find(n+1);
        if(h<=z[i]+r)F[find(i)]=find(n+2);
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j)
            if(dis(i,j)<=4ll*r*r)F[find(i)]=find(j);
    puts(find(n+1)==find(n+2)?"Yes":"No");
}
signed main() {
    for(int T=rd();T;--T)Main();
}