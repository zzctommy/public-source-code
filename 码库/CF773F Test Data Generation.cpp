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
const int N=30005;
const int M=N<<2;
int n,a,mod,f[2][M],ans;
int fmod(int x){return x-=mod,x+=x>>31&mod,x;}

namespace poly{
const db PI=acos(-1);
struct cp{
	db x,y;
	cp(){x=y=0;}
	cp(db x_,db y_){x=x_,y=y_;}
	cp operator + (const cp&t)const{return cp(x+t.x,y+t.y);}
	cp operator - (const cp&t)const{return cp(x-t.x,y-t.y);}
	cp operator * (const cp&t)const{return cp(x*t.x-y*t.y,x*t.y+y*t.x);}
}w[M];
int rev[M],lim,lg;
void init(const int&n){
	for(lg=0,lim=1;lim<n;++lg,lim<<=1);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1)),w[i]=cp(cos(2*PI*i/lim),sin(2*PI*i/lim));
}
void FFT(cp*a,int op){
	for(int i=0;i<lim;++i)if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1,t=lim>>1;i<lim;i<<=1,t>>=1){
		for(int j=0;j<lim;j+=i<<1){
			for(int k=0;k<i;++k){
				const cp X=a[j+k],Y=w[k*t]*a[i+j+k];
				a[j+k]=X+Y,a[i+j+k]=X-Y;
			}
		}
	}
	if(op)return;
	for(int i=0;i<lim;++i)a[i].x/=lim;
}
void mul(int*f,int*g,int*ans){
	static cp A[M],B[M];
	for(int i=0;i<lim;++i)A[i]=cp(f[i],0),B[i]=cp(g[i],0);
	FFT(A,1),FFT(B,1);
	for(int i=0;i<lim;++i)A[i]=A[i]*B[i],w[i].y*=-1;
	FFT(A,0);
	for(int i=0;i<lim;++i)ans[i]=LL(A[i].x+0.5)%mod;
	for(int i=0;i<lim;++i)w[i].y*=-1;
}
#define clr(a,n) memset(a,0,sizeof(int)*(n))
void shift(const int&n,const int&a){
	static int g[M],h[M],q[M];
	clr(g,lim),clr(h,lim),clr(q,lim),g[0]=1;
	for(int i=1;i<=n;++i)g[i]=fmod(f[0][i]+f[1][i]);
	mul(g,f[a&1],h),mul(g,f[(a&1)^1],q);
	for(int i=1;i<=n;++i)f[0][i]=fmod(f[0][i]+h[i]),f[1][i]=fmod(f[1][i]+q[i]);
}
void setbit(const int&n,const int&a){
	static int g[N];g[0]=1;
	for(int i=1;i<=n;++i)g[i]=fmod(f[0][i]+f[1][i]),f[1][i]=fmod(f[1][i]+g[i-1]);
}
}
signed main(){
	n=read(),a=read()>>1,mod=read();
	if(!a)return puts("0"),0;
	f[1][1]=ans=1,poly::init(n<<1);
	for(int i=log2(a)-1,len=1;i>=0;--i){
		poly::shift(n,len),len<<=1;
		if(a>>i&1)poly::setbit(n,len),++len;
		for(int j=1;j<=n;j+=2)ans=fmod(ans+f[1][j]);
	}
	printf("%d\n",ans);
	return 0;
}