#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 305
#define mod 1000000007
int n,q,ans[N][N];
LL a[N],b[N],s[N];
LL mul(LL a,LL b,LL P){
	// return (__int128)(a*b%P);
	LL res=a*b-(LL)((long double)a/P*b+0.5)*P;
	return res<0?res+P:res;
}
void init(){
	for(int i=1;i<=n;++i){
		b[i]=a[i],s[i]=1;
		for(int j=i-1;j>=1;--j)s[j]=mul(s[j+1],b[j],a[i]);
		LL t=__gcd(s[1],a[i]);
		for(int j=1;j<i;++j){
			if(s[j+1]%t){
				LL gcd=__gcd(t,s[j+1]);
				b[j]/=t/gcd,t=gcd;
			}
		}
		ans[i][i]=a[i]%mod;
		for(int j=i-1;j>=1;--j)ans[j][i]=1ll*ans[j+1][i]*(b[j]%mod)%mod;
	}
}
void Main(){
	// std::cerr<<mul(1e17,1e18+1,1e18)<<'\n';
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	init();
	while(q--){int l,r;scanf("%d%d",&l,&r);printf("%d\n",ans[l][r]);}
}
signed main(){for(int T=read();T;--T)Main();}