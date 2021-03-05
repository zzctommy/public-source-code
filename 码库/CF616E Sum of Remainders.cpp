#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
#define mod 1000000007
const int iv2=(mod+1)>>1;
int n,m,ans;
inline int calc(int l,int r){
	return 1ll*((l+r)%mod)*((r-l+1)%mod)%mod*iv2%mod;
}
signed main(){
	cin>>n>>m;
	ans=1ll*(n%mod)*(min(n,m)%mod)%mod;
	for(int l=1,r;l<=min(n,m);l=r+1){
		r=min(m,n/(n/l)),ans=(ans-1ll*calc(l,r)*((n/l)%mod)%mod+mod)%mod;
	}
	if(n<m){
		ans=(ans+1ll*((m-n)%mod)*(n%mod)%mod+mod)%mod;
	}
	cout<<ans<<'\n';
}