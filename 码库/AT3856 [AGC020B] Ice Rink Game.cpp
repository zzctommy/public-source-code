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
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=100005;
int n,a[N];
signed main(){
	n=read();
	rep(i,1,n)a[i]=read();
	if(a[n]!=2)return puts("-1"),0;
	LL L=2,R=3;
	per(i,n-1,1){
		L=ceil(1.*L/a[i])*a[i];
		R=R/a[i]*a[i]+a[i]-1;
		if(L>R)return puts("-1"),0;
	}
	printf("%lld %lld\n",L,R);
	return 0;
}