#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=12;
const int inf=0x3f3f3f3f;
int n,m,dis[N][N],dp[N][N][1<<N],ans=inf,rev[1<<N];
signed main(){
	n=read(),m=read();
	memset(dp,0x3f,sizeof(dp));
	memset(dis,0x3f,sizeof(dis));
	for(register int i=1;i<=m;++i){
	    int x=read()-1,y=read()-1,z=read();
	    if(dis[x][y]>z)dis[x][y]=dis[y][x]=z;
	}
	for(register int i=0;i<n;++i)
		for(register int j=0;j<n;++j)
			dp[i][j][1<<i]=0;
	for(register int i=0;i<n;++i)rev[1<<i]=i;
	for(register int j=n-2;j>=0;--j){
		for(register int msk=0;msk<1<<n;++msk){
			register int t1=msk,i;
			for(;t1;t1^=t1&-t1){
				i=rev[t1&-t1];
				for(register int mk=msk;mk;mk=(mk-1)&msk){
					if(dp[i][j][msk^mk]>=dp[i][j][msk])continue;
					register int t2=mk,k;
					for(;t2;t2^=t2&-t2){
						k=rev[t2&-t2];
						if(dis[i][k]!=inf)dp[i][j][msk]=min(dp[i][j][msk],dp[k][j+1][mk]+dp[i][j][msk^mk]+dis[i][k]*(j+1));
					}
				}
			}
		}
	}
	for(int i=0;i<n;++i)
		ans=min(ans,dp[i][0][(1<<n)-1]);
	printf("%d\n",ans);
	return 0;
}