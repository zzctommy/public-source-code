#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
const int N=505;
int n,m;
char a[N][N],b[N][N],c[N][N];
signed main(){
	n=read(),m=read();
	rep(i,1,n)scanf("%s",a[i]+1);
	rep(i,1,n)rep(j,1,m)b[i][j]=c[i][j]='.';
	rep(j,1,m)b[1][j]='#',c[n][j]='#';
	for(int j=1;j<=m;j+=2)rep(i,1,n-1)b[i][j]='#';
	for(int j=2;j<=m;j+=2)per(i,n,2)c[i][j]='#';
	rep(i,1,n)rep(j,1,m)if(a[i][j]=='#')b[i][j]=c[i][j]='#';
	rep(i,1,n){rep(j,1,m)putchar(b[i][j]);puts("");}
	puts("");
	rep(i,1,n){rep(j,1,m)putchar(c[i][j]);puts("");}
	return 0;
}