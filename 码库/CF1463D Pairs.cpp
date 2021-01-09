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
const int N=400005;
int n,a[N],b[N];
void Main(){
	n=read(),fill(b,b+n*2+1,0);
	int L=2*n,R=-1;
	rep(i,1,n)b[a[i]=read()]=1;
	for(int i=1,now=0;i<=n<<1;++i){
		if(b[i])++now;else --now;
		ckmin(L,now),ckmax(R,now);
	}
	printf("%d\n",n+1-(R-L));
}
signed main(){for(int T=read();T;--T)Main();}