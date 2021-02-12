// Problem: D. Credit Card
// Contest: Codeforces - Educational Codeforces Round 33 (Rated for Div. 2)
// URL: https://codeforces.com/contest/893/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms

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
const int inf=0x3f3f3f3f;
int n,a[N],d,s[N],smx[N],ans;
signed main(){
	n=read(),d=read();
	rep(i,1,n)a[i]=read(),s[i]=s[i-1]+a[i];
	smx[n+1]=-inf;
	per(i,n,1)smx[i]=max(smx[i+1],s[i]);
	int now=0;
	rep(i,1,n){
		if(!a[i]){
			if(now<0){
				now=d-(smx[i]-s[i-1]),++ans;
				if(now<0)return puts("-1"),0;
			}
		}else now+=a[i];
		if(now>d)return puts("-1"),0;
	}
	cout<<ans<<'\n';
}