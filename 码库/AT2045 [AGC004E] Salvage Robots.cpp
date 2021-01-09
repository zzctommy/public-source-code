#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
inline char rdc(){
	char ch=getchar();
	while (ch!='.'&&ch!='o'&&ch!='E')ch=getchar();
	return ch;
}
const int N=102;
int n,m,sx,sy;
short s1[N][N],s2[N][N],dp[N][N][N][N],a[N][N],ans;
signed main(){
	n=read(),m=read();
	rep(i,1,n)rep(j,1,m){
		char x=rdc();
		if(x=='E')sx=i,sy=j;
		s1[i][j]=s1[i-1][j]+(x=='o');
		s2[i][j]=s2[i][j-1]+(x=='o');
	}
	for(int l=0;l<=sy-1;++l)
		for(int r=0;r<=m-sy;++r)
			for(int u=0;u<=sx-1;++u)
				for(int d=0;d<=n-sx;++d){
					ckmax(ans,dp[l][r][u][d]);
					if(u+d<sx-1)ckmax(dp[l][r][u+1][d],short(dp[l][r][u][d]+s2[sx-u-1][min(m-l,sy+r)]-s2[sx-u-1][max(r,sy-l-1)]));
					if(u+d<n-sx)ckmax(dp[l][r][u][d+1],short(dp[l][r][u][d]+s2[sx+d+1][min(m-l,sy+r)]-s2[sx+d+1][max(r,sy-l-1)]));
					if(l+r<sy-1)ckmax(dp[l+1][r][u][d],short(dp[l][r][u][d]+s1[min(n-u,sx+d)][sy-l-1]-s1[max(d,sx-u-1)][sy-l-1]));
					if(l+r<m-sy)ckmax(dp[l][r+1][u][d],short(dp[l][r][u][d]+s1[min(n-u,sx+d)][sy+r+1]-s1[max(d,sx-u-1)][sy+r+1]));
				}
	printf("%d\n",ans);
	return 	0;
}