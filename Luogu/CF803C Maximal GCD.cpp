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
LL n,k,ans;
bool check(LL x){
	if(x>n*2/k/(k+1)+5)return 0;
	return x*(k+1)*k/2<=n;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	if(k>sqrt(n*2)+5)return puts("-1"),0;
	cerr<<"Qwq\n";
	for(LL i=1;i*i<=n;++i){
		if(n%i)continue;
		if(check(i))ckmax(ans,i);
		if(check(n/i))ckmax(ans,n/i);
	}
	if(!ans)return puts("-1"),0;
	rep(i,1,k-1)printf("%lld ",ans*i);
	printf("%lld\n",n-ans*k*(k-1)/2);
	return 0;
}