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
int n,a[N];
signed main(){
	n=read();
	int x=sqrt(n),j=n;
	int s1=n%x,s2=(n-s1*(x+1))/x;
	rep(i,1,s1){
		int st=j-(x+1)+1;
		rep(k,(i-1)*(x+1)+1,i*(x+1))a[k]=st++;
		j-=x+1;
	}
	rep(i,1,s2){
		int st=j-x+1;
		rep(k,(i-1)*x+1+s1*(x+1),i*x+s1*(x+1))a[k]=st++;
		j-=x;
	}
	rep(i,1,n)printf("%d ",a[i]);
	return 0;
}