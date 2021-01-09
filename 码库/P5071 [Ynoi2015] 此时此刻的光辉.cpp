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
int qpow(int n,int k,int mod){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*res*n%mod;return res;}
int gcd(int x,int y){while(y){int t=x%y;x=y,y=t;}return x;}
namespace MR{
static const int pri[8]={2,3,5,7,13,19,61,233};
bool mr(int x,int p){
	if(x%p==0||qpow(p,x-1,x)!=1)return 0;
	int k=x-1;
	while(!(k&1)){
		int t=qpow(p%x,k>>=1,x);
		if(t!=1&&t!=x-1)return 0;
		if(t==x-1)break;
	}
	return 1;
}
bool test(int x){
	for(int i=0;i<8;++i){
		if(x==pri[i])return 1;
		if(!mr(x,pri[i]))return 0;
	}
	return 1;
}

}

namespace PR{
int ans,d[150],tot;
mt19937 rnd(673);
#define rad(l,r) (rnd()%((r)-(l)+1)+l)
int pr(int x,int c){
	if(x==4)return 2;
	LL v0=c,v1=1ll*v0*v0%x+c,g=1;tot=0;
	while(true){
		g=1ll*g*(v1-v0)%x,d[++tot]=v1-v0;
		if(tot==32){if(gcd(g,x)>1)break;tot=0;}
		v0=1ll*v0*v0%x+c,v1=1ll*v1*v1%x+c,v1=1ll*v1*v1%x+c;
	}
	for(int i=1;i<=tot;++i){g=gcd(d[i],x);if(g>1)return g;}
	return x;
}
void solve(int x){
	if(x<=ans)return;
	if(MR::test(x))return ckmax(ans,x),void();
	int y=x;while(y==x)y=pr(x,rad(1,x-1));
	while(x%y==0)x/=y;solve(x),solve(y);
}
int work(int x){return ans=1,solve(x),ans;}

}

const int N=100005;
const int V=N*2+500;
const int M=30*N;
#define mod 19260817
int n,m,a[N],S,ans[N],now=1;
struct ASK{
	int l,r,id;
	ASK(){l=r=id=0;}
	inline bool operator < (const ASK&t)const{return l/S!=t.l/S?l<t.l:(l/S)&1?r<t.r:r>t.r;}
}q[N];
vector<pair<int,int> >d[N];
int pct,pri[N];
bool vis[N];
int len,lsh[V],cnt[V],inv[M];
void prework(){
	for(int i=2;i<=1000;++i){
		if(!vis[i])pri[++pct]=i;
		for(int j=1;j<=pct&&i*pri[j]<=1000;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	rep(i,1,pct)lsh[++len]=pri[i];
	for(int i=1;i<=n;++i){
		int x=a[i],y;
		for(int j=1;j<=pct;++j){
			if(x%pri[j])continue;
			int num=0;
			while(x%pri[j]==0)x/=pri[j],++num;
			d[i].pb(mkp(pri[j],num));
		}
		if(x==1)continue;
		y=PR::work(x),d[i].pb(mkp(y,1)),lsh[++len]=y,x/=y;
		if(x>1)d[i].pb(mkp(x,1)),lsh[++len]=x;
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;++i)
		for(int j=0,up=sz(d[i]);j<up;++j)
			d[i][j].fi=lower_bound(lsh+1,lsh+len+1,d[i][j].fi)-lsh;
	inv[1]=1;rep(i,2,30*n)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
}
void add(int x){
	for(int i=0,up=sz(d[x]);i<up;++i){
		pair<int,int>t=d[x][i];
		now=1ll*now*inv[cnt[t.fi]+1]%mod;
		cnt[t.fi]+=t.se,now=1ll*now*(cnt[t.fi]+1)%mod;
	}
}
void pop(int x){
	for(int i=0,up=sz(d[x]);i<up;++i){
		pair<int,int>t=d[x][i];
		now=1ll*now*inv[cnt[t.fi]+1]%mod;
		cnt[t.fi]-=t.se,now=1ll*now*(cnt[t.fi]+1)%mod;
	}
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)a[i]=read();
	prework();
	rep(i,1,m)q[i].l=read(),q[i].r=read(),q[i].id=i;
	S=n/sqrt(m)+1,sort(q+1,q+m+1);
	for(int i=1,l=1,r=0;i<=m;++i){
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(l<q[i].l)pop(l++);
		while(r>q[i].r)pop(r--);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}
/*
5 5
64 2 18 9 100
1 5
2 4
2 3
1 4
3 4

*/