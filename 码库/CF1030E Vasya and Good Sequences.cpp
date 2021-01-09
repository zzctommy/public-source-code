//Orz cyn2006
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
int n,c[N],cnt[2],s[N];
LL ans;
signed main(){
	scanf("%d",&n);
	rep(i,1,n){
		LL x;scanf("%lld",&x);
		while(x)x^=x&-x,++c[i];
		s[i]=s[i-1]^(c[i]&1);
	}
	rep(i,1,n){
		int mx=0,sum=0;
		per(j,i,max(i-63,1)){
			ckmax(mx,c[j]),sum+=c[j];
			if(mx*2<=sum&&s[j-1]==s[i])++ans;
		}
		if(i>=64)ans+=cnt[s[i]],++cnt[s[i-64]];
	}
	printf("%lld\n",ans);
	return 0;
}