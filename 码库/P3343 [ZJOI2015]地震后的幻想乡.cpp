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
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=10;
const int M=N*(N-1)/2+5;
int n,m,mp[N][N],num[1<<N];
LL f[1<<N][M],g[1<<N][M],C[M][M];
db ans;
void out(int n,int msk){
	for(int i=0;i<n;++i)putchar((msk>>i&1)+'0');
}
signed main(){
	n=read(),m=read();
	rep(i,1,m){
		int x=read()-1,y=read()-1;
		mp[x][y]=mp[y][x]=1;
	}
	C[0][0]=1;
	for(int i=1;i<=m;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(int i=0;i<1<<n;++i){
		for(int j=0;j<n;++j)
			for(int k=j+1;k<n;++k)
				if(i>>j&1&&i>>k&1&&mp[j][k])++num[i];
	}
	for(int i=0;i<n;++i)f[1<<i][0]=1;
	for(int msk=0;msk<1<<n;++msk){
		for(int i=0;i<=num[msk];++i){
			for(int ms=(msk-1)&msk;ms;ms=(ms-1)&msk){
				if(ms&(msk&-msk))
					for(int j=0;j<=num[ms];++j)
						g[msk][i]+=f[ms][j]*C[num[msk^ms]][i-j];
			}
			f[msk][i]=C[num[msk]][i]-g[msk][i];
		}
	}
	/*
	for(int msk=(1<<n)-1;msk<1<<n;++msk){
		cerr<<"msk=";out(n,msk);cerr<<'\n';
		cerr<<"f:";for(int j=0;j<=m;++j)cerr<<f[msk][j]<<' ';cerr<<'\n';
		cerr<<"g:";for(int j=0;j<=m;++j)cerr<<g[msk][j]<<' ';cerr<<'\n';
	}
	*/
	for(int i=0;i<=m;++i)ans+=1.*g[(1<<n)-1][i]/C[m][i];
	printf("%.6lf\n",ans/=(m+1));
	return 0;
}