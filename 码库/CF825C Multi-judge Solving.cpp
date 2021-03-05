// Problem: C. Multi-judge Solving
// Contest: Codeforces - Educational Codeforces Round 25
// URL: https://codeforces.com/contest/825/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms

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
const int N=1005;
int n,k,a[N],ans;
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i]=read();
	sort(a+1,a+n+1);
	int now=k;
	rep(i,1,n){
		while(now<1+(a[i]-1)/2)now*=2,++ans;
		ckmax(now,a[i]);
	}
	cout<<ans<<'\n';
}