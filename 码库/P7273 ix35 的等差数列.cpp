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

const int N=300005;
int n,w,a[N],cnt[N],ans;
signed main(){
	n=read(),w=read();
	rep(i,1,n)a[i]=read();
	if(n==1)return puts("0"),0;
	rep(d,0,w/(n-1)){
		int fyyak;
		rep(i,1,n)if((fyyak=a[i]-d*(i-1))>0&&a[i]+(n-i)*d<=w)ckmax(ans,++cnt[fyyak]);
		rep(i,1,n)if((fyyak=a[i]-d*(i-1))>0&&a[i]+(n-i)*d<=w)--cnt[fyyak];
	}
	printf("%d\n",n-ans);
	return 0;
}