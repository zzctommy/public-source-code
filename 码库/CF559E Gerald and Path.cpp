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

const int N=105;
int dp[N][N][2],n,ans;
struct line{
	int a,l;
	int calc(int dir){return !dir?a:a+l;} 
}a[N];
int calc(int id,int dir){return a[id].calc(dir);}
inline bool cmp(const line&a,const line&b){
	return a.a<b.a;
}
signed main(){
	n=read();
	rep(i,1,n)a[i].a=read(),a[i].l=read();
	sort(a+1,a+n+1,cmp),a[0].a=-3e8,a[0].l=0;
	rep(i,0,n)rep(j,0,i)rep(d1,0,1){
		int nw1=j,nw2=d1;
		rep(k,i+1,n)rep(d2,0,1){
			if(calc(nw1,nw2)<a[k].calc(d2))nw1=k,nw2=d2;
			ckmax(dp[k][nw1][nw2],dp[i][j][d1]+calc(nw1,nw2)-calc(k,d2)
				+min(calc(k,d2)-calc(j,d1),a[k].l));
		}
	}
	rep(i,1,n)rep(j,1,i)rep(k,0,1)ckmax(ans,dp[i][j][k]);
	cout<<ans<<'\n';
	return 0;
}