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
LL mul(LL x,LL y,LL zky){
	LL res=x*y-(long long)((long double)x/zky*y+0.5)*zky;
	return res<0?res+zky:res;
}
LL qpow(LL n,LL k,LL zky){
	LL res=1;for(;k;k>>=1,n=mul(n,n,zky))if(k&1)res=mul(res,n,zky);
	return res;
}
LL gcd(LL x,LL y){
	while(y){LL t=x%y;x=y,y=t;}
	return x;
}

namespace MR{
static const int P[8]={2,3,5,7,11,19,61,233};
bool mr(LL x,LL p){
	if(x%p==0||qpow(p,x-1,x)!=1)return 0;
	LL k=x-1;
	while(!(k&1)){
		LL t=qpow(p,k>>=1,x);
		if(t!=1&&t!=x-1)return 0;
		if(t==x-1)break;
	}
	return 1;
}
bool test(LL x){
	for(int i=0;i<8;++i){
		if(x==P[i])return 1;
		if(!mr(x,P[i]))return 0;
	}
	return 1;
}

}
namespace PR{
LL s[150],d[150];
int tot;
mt19937_64 rnd(679);
#define rad(l,r) (rnd()%((r)-(l)+1)+(l))
LL pr(LL x,LL c){
	if(x==4)return 2;
	LL v0=c,v1=mul(v0,v0,x)+c,g=1;int len=0;
	while(1){
		s[++len]=v1-v0,g=mul(g,v1-v0,x);
		if(len==127){if(gcd(g,x)>1)break;len=0;}
		v0=mul(v0,v0,x)+c,v1=mul(v1,v1,x)+c,v1=mul(v1,v1,x)+c;
	}
	for(int i=1;i<=len;++i)if((g=gcd(s[i],x))>1)return g;
	return x;
}
void solve(LL x){
	if(x==1)return;
	if(MR::test(x))return d[++tot]=x,void();
	LL y=x;while(y==x)y=pr(x,rad(1,x-1));
	solve(x/y),solve(y);
}
void work(LL x){tot=0,solve(x),sort(d+1,d+tot+1);}

}

#define zky 1000000007
void fmod(int&x){x-=zky,x+=x>>31&zky;}
inline int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%zky)if(k&1)res=1ll*n*res%zky;return res;}
int B[3005],fac[3005],ifc[3005],a[3005],inv[3005];
int comb(int n,int m){return n<m?0:1ll*fac[n]*ifc[m]%zky*ifc[n-m]%zky;}
LL n;
int x,y,ans;
void Main(){
	ans=0;
	scanf("%lld%d%d",&n,&x,&y);
	rep(i,0,y)a[y-i+1]=1ll*B[i]*comb(y+1,i)%zky*inv[y+1]%zky;
	++a[y];
	PR::work(n);
	rep(t,1,y+1){
		int l=1,r=0,res=1;
		while(l<=PR::tot){
			while(r<PR::tot&&PR::d[r+1]==PR::d[l])++r;
			LL p=PR::d[l];
			int k=r-l+1,tmp=0,iv,now,bs,tem;
			tem=p%zky,now=qpow(tem,t*(k-1)),iv=qpow(qpow(tem,t),zky-2),bs=qpow(tem,x);
			rep(i,0,k-1)fmod(tmp+=now),now=1ll*now*bs%zky*iv%zky;
			tmp=1ll*tmp*(zky-qpow(tem,y))%zky;

			now=qpow(tem,t*k);
			rep(i,0,k)fmod(tmp+=now),now=1ll*now*bs%zky*iv%zky;
			res=1ll*res*tmp%zky,l=r+1;
		}
		fmod(ans+=1ll*a[t]*res%zky);
	}
	ans=1ll*ans*qpow(n%zky,y)%zky;
	printf("%d\n",ans);
}
signed main(){
	B[0]=fac[0]=ifc[0]=inv[1]=1;
	rep(i,1,3003)fac[i]=1ll*fac[i-1]*i%zky,ifc[i]=qpow(fac[i],zky-2);
	rep(i,2,3003)inv[i]=1ll*inv[zky%i]*(zky-zky/i)%zky;
	rep(i,1,3003){
		int res=0;
		rep(j,0,i-1)fmod(res+=1ll*B[j]*comb(i+1,j)%zky);
		B[i]=1ll*(zky-res)*qpow(i+1,zky-2)%zky;
	}
	for(int T=read();T;--T)Main();
}
/*
5
6 0 0
6 0 1
6 1 0
6 1 1
1000000000 50 50

*/