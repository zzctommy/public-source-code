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
const int N=13;
int n,m;
LL a[N][N];
LL Gauss(const int&n){
	LL res=1;
	rep(i,1,n){
		rep(j,i+1,n){
			while(a[j][i]){
				LL div=a[i][i]/a[j][i];
				rep(k,i,n)a[i][k]-=a[j][k]*div,swap(a[i][k],a[j][k]);
				res*=-1;
			}
		}
		if(!a[i][i])return 0;
		res*=a[i][i];
	}
	return res;
}
void Main(){
	memset(a,0,sizeof(a));
	n=read(),m=read();
	rep(i,1,m){
		int x=read(),y=read();
		++a[x][x],++a[y][y],--a[x][y],--a[y][x];
	}
	printf("%lld\n",Gauss(n-1));
}
signed main(){for(int T=read();T;--T)Main();}