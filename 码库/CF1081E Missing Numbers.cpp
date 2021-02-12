// Problem: E. Missing Numbers
// Contest: Codeforces - Avito Cool Challenge 2018
// URL: https://codeforces.com/contest/1081/problem/E
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
const int N=200005;
int n,a[N],b[N],now,tot;
bool isrt(int x){
	if(x>1e13)return 0;
	int l=max(1ll,(int)(sqrt(x)-3)),r=sqrt(x)+3;
	rep(i,l,r)if(x%i==0)return 1;
	return 0;
}
signed main(){
	n=read()/2;
	rep(i,1,n)a[i]=read();
	for(int i=1;i<=n;++i){
		bool flg=0;int res;
		for(int j=sqrt(a[i]);j>=1;--j){
			if(a[i]%j)continue;
			int X=a[i]/j,Y=j;
			if((X-Y)%2)continue;
			res=(X-Y)/2,res*=res;
			if(res<=now)continue;
			flg=1;break;
		}
		if(now>=res||!flg)return puts("No"),0;
		b[++tot]=res-now,b[++tot]=a[i];
		now=a[i]+res;
	}
	now=0;
	rep(i,1,n<<1){
		now+=b[i];
		if(!isrt(now))return puts("No"),0;
	}
	puts("Yes");
	rep(i,1,n<<1)printf("%lld ",b[i]);
	puts("");
	return 0;
}