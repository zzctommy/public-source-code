#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=18;
db a[N][N],dp[1<<N];
int n;
signed main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			scanf("%lf",&a[i][j]);
	dp[(1<<n)-1]=1;
	for(int msk=(1<<n)-1;msk;--msk){
		db d=__builtin_popcount(msk);
		d=d*(d-1)/2;
		for(int i=0;i<n;++i){
			if(!(msk>>i&1))continue;
			for(int j=0;j<n;++j){
				if(!(msk>>j&1))continue;
				dp[msk-(1<<j)]+=dp[msk]*a[i][j]/d;
			}
		}
	}
	for(int i=0;i<n;++i)printf("%.6lf ",dp[1<<i]);
	return 0;
} 