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
const int N=1005;
int n,a[N][N],ans;
signed main(){
	n=read();
	rep(i,1,n)rep(j,1,n)a[i][j]=read();
	int sum=0;
	rep(j,1,n){
		int s[2];s[0]=s[1]=0;
		rep(i,1,n)s[i&1]+=a[i][j];
		sum+=max(s[0],s[1]);
	}
	ckmax(ans,sum),sum=0;
	rep(i,1,n){
		int s[2];s[0]=s[1]=0;
		rep(j,1,n)s[j&1]+=a[i][j];
		sum+=max(s[0],s[1]);
	}
	ckmax(ans,sum),sum=0;
	cout<<ans<<'\n';
}