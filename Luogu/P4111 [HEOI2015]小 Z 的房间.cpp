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
const int N=12;
const int M=N*N;
#define mod 1000000000
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int n,m,a[M][M],mp[N][N],tot,id[N][N];
int Gauss(const int&n){
	if(!n)return 0;
	int res=1;
	rep(i,1,n){
		rep(j,i+1,n){
			while(a[j][i]){
				const int div=a[i][i]/a[j][i];
				rep(k,i,n)fmod(a[i][k]-=1ll*a[j][k]*div%mod),swap(a[i][k],a[j][k]);
				res*=-1;
			}
		}
		if(!a[i][i])return 0;
		res=1ll*res*a[i][i]%mod;
	}
	return fmod(res),res;
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)rep(j,1,m){
		char ch=getchar();
		while(ch!='.'&&ch!='*')ch=getchar();
		mp[i][j]=ch=='.';
		if(mp[i][j])id[i][j]=++tot;
	}
	rep(i,1,n)rep(j,1,m){
		if(!mp[i][j])continue;
		if(mp[i-1][j])++a[id[i][j]][id[i][j]],--a[id[i][j]][id[i-1][j]];
		if(mp[i+1][j])++a[id[i][j]][id[i][j]],--a[id[i][j]][id[i+1][j]];
		if(mp[i][j-1])++a[id[i][j]][id[i][j]],--a[id[i][j]][id[i][j-1]];
		if(mp[i][j+1])++a[id[i][j]][id[i][j]],--a[id[i][j]][id[i][j+1]];
	}
	printf("%d\n",Gauss(tot-1));
	return 0;
}