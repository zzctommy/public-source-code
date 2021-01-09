#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x;
}
const int N=4005;
int n,x,a[N];
LL ans=1e18;
signed main(){
	n=read(),x=read();
	rep(i,1,n)a[i]=a[i+n]=read();
	rep(i,0,n){
		static int b[N],q[N],H,T;
		memset(b,0x3f,sizeof(b));
		LL res=1ll*x*i;
		H=1,T=0;
		for(int j=1;j<=n<<1;++j){
			while(H<=T&&q[H]<j-i)++H;
			while(H<=T&&a[q[T]]>=a[j])--T;
			q[++T]=j;
			ckmin(b[(j-1)%n+1],a[q[H]]);
		}
		rep(j,1,n)res+=b[j];
		ckmin(ans,res);
	}
	printf("%lld\n",ans);
	return 0;
}