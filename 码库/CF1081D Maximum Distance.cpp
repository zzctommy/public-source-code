// Problem: D. Maximum Distance
// Contest: Codeforces - Avito Cool Challenge 2018
// URL: https://codeforces.com/contest/1081/problem/D
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
const int N=100005;
int F[N],n,m,k,tag[N],ans,siz[N];
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
struct edge{int x,y,z;}e[N];
inline bool cmp(const edge&a,const edge&b){
	return a.z<b.z;
}
signed main(){
	n=read(),m=read(),k=read();
	rep(i,1,k){int x=read();tag[x]=siz[x]=1;}
	rep(i,1,n)F[i]=i;
	rep(i,1,m){
		int x=read(),y=read(),z=read();	
		e[i].x=x,e[i].y=y,e[i].z=z;
	}
	sort(e+1,e+m+1,cmp);
	rep(i,1,m){
		int x=e[i].x,y=e[i].y,z=e[i].z;
		if(find(x)==find(y))continue;
		if(siz[find(x)]+siz[find(y)]==k){
			rep(i,1,k)printf("%lld ",z);
			return 0;
		}
		siz[find(x)]+=siz[find(y)],F[find(y)]=find(x);
	}
	assert(0);
	return 0;
}