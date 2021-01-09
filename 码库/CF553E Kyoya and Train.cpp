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
const int V=55;
const int E=105;
const int N=20005;
const int M=N<<2;
const db inf=1e15;
int n,m,t,X,a[E],b[E],c[E];
db p[E][N<<1],dis[V][V],f[E][N<<1];

namespace poly{

const db PI=acos(-1.0);

int rev[M],lg,lim;
db g[E][N<<1];
void init(const int&n){
	for(lg=0,lim=1;lim<=n;++lg,lim<<=1);
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
void FFT(cp*a,int op){
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		cp wn=cp(cos(PI/i),sin(PI/i)*(op?1:-1));
		for(int j=0;j<lim;j+=i<<1){
			cp w0=cp(1,0);
			for(int k=0;k<i;++k,w0=w0*wn){
				const cp X=a[j+k],Y=w0*a[i+j+k];
				a[j+k]=X+Y,a[i+j+k]=X-Y;
			}
		}
	}
	if(op)return;
	for(int i=0;i<lim;++i)a[i].x/=lim;
}
void CDQ_FFT(int l,int r){
	if(l==t&&r==2*t-1)return;
	static cp A[M],B[M];
	if(l==r){
		rep(i,1,n-1)f[i][l]=inf;
		for(int i=1;i<=m;++i)if(a[i]!=n)ckmin(f[a[i]][l],g[i][l]+c[i]);
		return;
	}
	int mid=(l+r)>>1;
	CDQ_FFT(mid+1,r);
	init(r-l+r-mid);
	for(int i=1;i<=m;++i){
		if(a[i]==n)continue;
		for(int j=0;j<lim;++j)A[j]=B[j]=cp(0,0);
		for(int j=0;j<=r-l;++j)A[j].x=p[i][j];
		for(int j=mid+1;j<=r;++j)B[j-mid-1].x=f[b[i]][r-j+mid+1];
		FFT(A,1),FFT(B,1);
		for(int j=0;j<lim;++j)A[j]=A[j]*B[j];
		FFT(A,0);
		for(int j=l;j<=mid;++j)g[i][j]+=A[r-j].x;
	}
	CDQ_FFT(l,mid);
}
}
signed main(){
	n=read(),m=read(),t=read(),X=read();
	rep(i,1,n)rep(j,1,n)dis[i][j]=i==j?0:inf;
	for(int i=1;i<=m;++i){
		a[i]=read(),b[i]=read(),c[i]=dis[a[i]][b[i]]=read();
		rep(j,1,t)p[i][j]=1.*read()/100000;
	}
	rep(k,1,n)rep(i,1,n)rep(j,1,n)ckmin(dis[i][j],dis[i][k]+dis[k][j]);
	rep(i,1,n-1)rep(j,t,t*2-1)f[i][j]=dis[i][n]+X;
	rep(i,0,t*2-1)f[n][i]=i<=t?0:X;
	poly::CDQ_FFT(0,t*2-1);
	printf("%.9lf\n",f[1][0]);
	return 0;
}
