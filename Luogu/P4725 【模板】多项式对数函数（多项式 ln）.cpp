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
const int N=100005;
const int M=N*3;

#define mod 998244353
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int rev[M],LOG,lim;
int h[M];
void init(const int&n){//卷积预处理
	static int lastinit=0;
	if(lastinit==n)return;
	lastinit=n;
	for(LOG=0,lim=1;lim<=n;++LOG,lim<<=1);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(LOG-1));
}
void NTT(int*a,int op){//卷积
	const int g=op?qpow(3,mod-2):3;
	for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1){
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod){
				const int X=a[j+k],Y=1ll*a[i+j+k]*w0%mod;
				fmod(a[j+k]=X+Y),fmod(a[i+j+k]=X-Y);
			}
		}
	}
	if(!op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*ilim*a[i]%mod;
}
void poly_inv(int*f,int*g,int pw){//求逆
	if(pw==1)return g[0]=qpow(f[0],mod-2),void();
	poly_inv(f,g,(pw+1)>>1),init(pw<<1);
	memcpy(h,f,pw<<2),fill(h+pw,h+lim,0);
	NTT(g,0),NTT(h,0);
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*(2-1ll*g[i]*h[i]%mod+mod)%mod;
	NTT(g,1),fill(g+pw,g+lim,0);
}
void dao(int*f,int*g,const int&n){//求导
	for(int i=1;i<n;++i)g[i-1]=1ll*i*f[i]%mod;g[n-1]=0;
}
void jif(int*f,int*g,const int&n){//积分
	static int last_init=0,inv[M];
	if(last_init!=n){
		inv[1]=1;for(int i=2;i<=n;++i)inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
		last_init=n;
	}
	for(int i=1;i<n;++i)g[i]=1ll*f[i-1]*inv[i]%mod;g[0]=0;
}
void poly_ln(int*f,int*g,const int&n){
	poly_inv(f,g,n),dao(f,h,n),init(n<<1);
	fill(h+n,h+lim,0),NTT(g,0),NTT(h,0);
	for(int i=0;i<lim;++i)g[i]=1ll*g[i]*h[i]%mod;
	NTT(g,1),jif(g,h,n),memcpy(g,h,n<<2);
}

int n,a[M],b[M];
signed main(){
	n=read();for(int i=0;i<n;++i)a[i]=read();
	poly_ln(a,b,n);
	for(int i=0;i<n;++i)printf("%d ",b[i]);
	return 0;
}