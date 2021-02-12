// Problem: E. Minimal Labels
// Contest: Codeforces - Educational Codeforces Round 25
// URL: https://codeforces.com/contest/825/problem/E
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
const int N=100005;
int n,m;
int ans[N],tot,val[N],ind[N];
vector<int>g[N];
void topo(){
	priority_queue<int>pq;
	rep(i,1,n)if(!ind[i])pq.push(i);
	while(!pq.empty()){
		int u=pq.top();pq.pop();
		ans[u]=tot--;
		for(int v:g[u])if(!--ind[v])pq.push(v);
	}
}
signed main(){
	n=read(),m=read();
	rep(i,1,m){
		int x=read(),y=read();
		g[y].pb(x),++ind[x];
	}
	tot=n,topo();
	rep(i,1,n)printf("%d ",ans[i]);
	return 0;
}