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
const int N=114514;
int n;
db f[N],g[N];
signed main(){
	n=read();
	f[0]=g[0]=1;
	rep(i,1,n-1){
		f[i]=f[i-1]+1.*n/(n-i);
		g[i]=1.*i/(n-i)*(f[i]+1)+f[i-1]+g[i-1]+1;
	}
	printf("%.2lf\n",g[n-1]);
	return 0;
}