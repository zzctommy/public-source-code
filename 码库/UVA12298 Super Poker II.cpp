//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
const int N=200005;
const int M=N<<2;

namespace math{

int pri[N],pct;
bool vis[N];
void initmath(const int&n=N-5){
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++pct]=i;
		for(int j=1;j<=pct&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}

}

namespace poly{

const db PI=acos(-1);
int rev[M],lg,lim;
void init_poly(const int&n){
	for(lim=1,lg=0;lim<n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
struct cp{
	db x,y;
	cp(){x=y=0;}
	cp(db x_,db y_){x=x_,y=y_;}
	cp operator + (const cp&t)const{return cp(x+t.x,y+t.y);}
	cp operator - (const cp&t)const{return cp(x-t.x,y-t.y);}
	cp operator * (const cp&t)const{return cp(x*t.x-y*t.y,x*t.y+y*t.x);}
};
db round(const db&x){return x>0?floor(x+0.5):ceil(x-0.5);}
void FFT(cp*a,int op){
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		const cp wn(cos(PI/i),sin(PI/i)*(op?1:-1));
		for(int j=0;j<lim;j+=i<<1){
			cp w0(1,0);
			for(int k=0;k<i;++k,w0=w0*wn){
				const cp X=a[j+k],Y=a[i+j+k]*w0;
				a[j+k]=X+Y,a[i+j+k]=X-Y;
			}
		}
	}
	if(op)return;
	for(int i=0;i<lim;++i)a[i].x/=lim;
}
void solve(LL*E,LL*F,LL*G,LL*H,LL*ans,int n){
	static cp A[M],B[M],C[M],D[M];init_poly(n<<2);
	for(int i=0;i<n;++i)A[i]=cp(E[i],0);for(int i=n;i<lim;++i)A[i]=cp(0,0);FFT(A,1);
	for(int i=0;i<n;++i)B[i]=cp(F[i],0);for(int i=n;i<lim;++i)B[i]=cp(0,0);FFT(B,1);
	for(int i=0;i<n;++i)C[i]=cp(G[i],0);for(int i=n;i<lim;++i)C[i]=cp(0,0);FFT(C,1);
	for(int i=0;i<n;++i)D[i]=cp(H[i],0);for(int i=n;i<lim;++i)D[i]=cp(0,0);FFT(D,1);
	for(int i=0;i<lim;++i)A[i]=A[i]*B[i]*C[i]*D[i];FFT(A,0);
	for(int i=0;i<lim;++i)ans[i]=round(A[i].x);
}

}

pair<int,char>exread(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return mkp(x,ch);
}

int a,b,c;
LL S[M],H[M],C[M],D[M];
void Main(){
	a=read(),b=read(),c=read();
	if(!a&&!b&&!c)exit(0);++b;
	for(int i=1;i<b;++i)S[i]=H[i]=C[i]=D[i]=math::vis[i];
	for(int i=1;i<=c;++i){
		pair<int,char>x=exread();
		if(x.se=='S')S[x.fi]=0;
		if(x.se=='H')H[x.fi]=0;
		if(x.se=='C')C[x.fi]=0;
		if(x.se=='D')D[x.fi]=0;
	}
	poly::solve(S,H,C,D,S,b);
	for(int i=a;i<b;++i)printf("%lld\n",S[i]);
	puts("");
}

signed main(){
	math::initmath();
	while("fyy AK IOI")Main();
}