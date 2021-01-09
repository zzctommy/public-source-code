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
inline LL readLL(){
	LL x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10ll+ch-'0',ch=getchar();
	return x;
}
const int N=2003;
LL a[N][N];
int n,m,x,y,ans;
vector<LL>b[N<<1];
signed main(){
	n=read(),m=read();
	rep(i,1,n)rep(j,1,m)a[i][j]=readLL();
	x=read(),y=read();
	rep(i,1,n)rep(j,1,m)b[abs(i-x)+abs(j-y)].pb(a[i][j]);
	LL now=a[x][y];
	while(now>1){
		++ans;
		if(!sz(b[ans])){ans=-1;break;}
		for(int j=0,up=sz(b[ans]);now>1&&j<up;++j)now=__gcd(b[ans][j],now);
	}
	cout<<ans<<'\n';
}