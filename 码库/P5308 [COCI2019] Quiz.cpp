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
const int N=100005;
const db inf=1e14;
const db eps=1e-12;
int n,k,g[N],q[N],H,T;
db f[N],res;
db slope(int i,int j){
	return 1.*(f[i]-f[j])/(i-j);
}
int check(db sl){
	q[H=T=1]=0;
	for(int i=1;i<=n;++i){
		while(H<T&&slope(q[H],q[H+1])>1./i)++H;
		f[i]=f[q[H]]+1.*(i-q[H])/i-sl,g[i]=g[q[H]]+1;
		while(H<T&&slope(q[T-1],q[T])<slope(q[T-1],i))--T;
		q[++T]=i;
	}
	return g[n];
}
signed main(){
	n=read(),k=read();
	db l=0,r=inf;
	while(r-l>eps){
		db mid=(l+r)/2;int tmp=check(mid);
		if(tmp>=k)l=mid,res=1.*k*mid+f[n];
		else r=mid;
	}
	printf("%.9Lf\n",res);
	return 0;
}