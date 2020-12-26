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
const int N=55;
const db eps=1e-7;
int n;
db a[N][N],ans=1;
db Gauss(const int&n){
	db res=1;
	rep(i,1,n){
		int mx=i;
		rep(j,i+1,n)if(fabs(a[mx][i])<fabs(a[j][i]))mx=j;
		if(mx!=i){
			res*=-1;
			rep(j,i,n)swap(a[i][j],a[mx][j]);
		}
		if(fabs(a[i][i])<eps)return 0;
		rep(j,i+1,n){
			if(fabs(a[j][i])<eps)continue;
			const db div=a[j][i]/a[i][i];
			rep(k,i,n)a[j][k]-=div*a[i][k];
		}
		res*=a[i][i];
	}
	return res;
}
signed main(){
	n=read();
	rep(i,1,n)rep(j,1,n){
		scanf("%lf",&a[i][j]);
		ckmax(a[i][j],eps),ckmin(a[i][j],1.-eps);
		if(i<j)ans*=1.-a[i][j];
		a[i][j]=a[i][j]/(1.-a[i][j]);
	}
	rep(i,1,n){
		a[i][i]=0;
		rep(j,1,n)if(i!=j)a[i][i]+=a[i][j],a[i][j]*=-1.;
	}
	//cerr<<"ans="<<ans<<'\n';
	//rep(i,1,n)rep(j,1,n)printf("%.5lf%c",a[i][j]," \n"[j==n]);
	printf("%.8lf\n",ans*Gauss(n-1));
	//rep(i,1,n)rep(j,1,n)printf("%.5lf%c",a[i][j]," \n"[j==n]);
	return 0;
}