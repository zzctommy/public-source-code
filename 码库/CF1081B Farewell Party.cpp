// Problem: B. Farewell Party
// Contest: Codeforces - Avito Cool Challenge 2018
// URL: https://codeforces.com/contest/1081/problem/B
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
int n,a[N],b[N],col,ans[N];
vector<int>v[N];
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=n-read(),v[a[i]].pb(i);
	for(int i=1;i<=n;++i){
		if(!v[i].size())continue;
		if(v[i].size()%i)return puts("Impossible"),0;
		for(int j=0,up=sz(v[i]);j<up;j+=i){
			++col;
			for(int k=j;k<j+i;++k)ans[v[i][k]]=col;
		}
	}
	puts("Possible");
	rep(i,1,n)printf("%d ",ans[i]);
	return 0;
}