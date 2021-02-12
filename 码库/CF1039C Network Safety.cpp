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
const int mod=1000000007;
inline int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
struct mint{
	int x;
	inline void fmod(int&x){x-=mod,x+=x>>31&mod;}
	mint(LL v=0){x=v%mod,x<0?x+=mod:0;}
	mint& operator += (const mint&t){fmod(x=x+t.x);return *this;}
	mint& operator -= (const mint&t){fmod(x=x+mod-t.x);return *this;}
	mint& operator *= (const mint&t){x=1ll*x*t.x%mod;return *this;}
	mint& operator /= (const mint&t){x=1ll*x*qpow(t.x,mod-2)%mod;return *this;}
	friend mint operator + (const mint&a,const mint&b){return mint(a)+=b;}
	friend mint operator - (const mint&a,const mint&b){return mint(a)-=b;}
	friend mint operator * (const mint&a,const mint&b){return mint(a)*=b;}
	friend mint operator / (const mint&a,const mint&b){return mint(a)/=b;}
	mint operator -(){return !x?0:mod-x;}
	mint operator == (const mint&t){return x==t.x;}
	mint operator != (const mint&t){return x!=t.x;}
	mint operator < (const mint&t){return x<t.x;}
	mint operator > (const mint&t){return x>t.x;}
	mint operator <= (const mint&t){return x<=t.x;}
	mint operator >= (const mint&t){return x>=t.x;}
	friend ostream& operator << (ostream&stream,const mint&v){return stream<<v.x;}
	friend istream& operator >> (istream&stream,mint&v){return stream>>v.x;}
	explicit operator int() const{return x;}
};

const int N=500005;

int n,m,k,tot,cnt[N];
LL c[N];
map<LL,int>id;
map<int,int>F[N];
inline int anc(LL t,int x){return F[t][x]==x?x:F[t][x]=anc(t,F[t][x]);}
mint ans;
signed main(){
	n=read(),m=read(),k=read();
	rep(i,1,n)scanf("%lld",&c[i]);
	ans=1ll*qpow(2,k)*qpow(2,n)%mod;
	rep(i,1,m){
		int x=read(),y=read();
		LL t=c[x]^c[y];
		if(!id[t])id[t]=++tot;
		int j=id[t];
		if(!F[j][x])F[j][x]=x;
		if(!F[j][y])F[j][y]=y;
		if(anc(j,x)==anc(j,y))continue;
		F[j][anc(j,x)]=anc(j,y);
		ans-=qpow(2,n-cnt[j]),++cnt[j];
		ans+=qpow(2,n-cnt[j]);
	}
	cout<<ans<<'\n';
}