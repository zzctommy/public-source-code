// Problem: C. Rumor
// Contest: Codeforces - Educational Codeforces Round 33 (Rated for Div. 2)
// URL: https://codeforces.com/contest/893/problem/C
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
int n,m,a[N],val[N],F[N],ans;
int anc(int x){return x==F[x]?x:F[x]=anc(F[x]);}
signed main(){
	n=read(),m=read();
	rep(i,1,n)a[i]=read(),val[i]=a[i],F[i]=i;
	rep(i,1,m){
		int x=read(),y=read();
		ckmin(val[anc(y)],val[anc(x)]);
		F[anc(x)]=anc(y);
	}
	rep(i,1,n)if(anc(i)==i)ans+=val[i];
	cout<<ans<<'\n';
}