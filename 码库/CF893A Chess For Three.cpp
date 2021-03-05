// Problem: A. Chess For Three
// Contest: Codeforces - Educational Codeforces Round 33 (Rated for Div. 2)
// URL: https://codeforces.com/contest/893/problem/A
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
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int n,a[4];
signed main(){
	n=read();
	a[0]=a[1]=1;
	rep(t,1,n){
		int x=read()-1,y;
		if(!a[x])return puts("NO"),0;
		if(0!=x&&a[0])a[0]=0,y=0;
		else if(1!=x&&a[1])a[1]=0,y=1;
		else a[2]=0,y=2;
		if(x!=0&&y!=0)a[0]=1;
		else if(x!=1&&y!=1)a[1]=1;
		else if(x!=2&&y!=2)a[2]=1;
	}
	puts("YES");
}