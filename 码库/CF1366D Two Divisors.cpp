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
const int N=10000005;
const int M=500005;
int n,a[M],ansa[N],ansb[N];
int pri[N/10],pct,low[N];
bool vis[N];
void Sieve(const int&n=N-1){
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++pct]=i;
		for(int j=1;j<=pct&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1,low[i*pri[j]]=pri[j];
			if(i%pri[j]==0)break;
		}
	}
}
signed main(){
	Sieve();
	n=read();
	rep(i,1,n)a[i]=read();
	rep(i,1,n){
		if(!vis[a[i]]){
			ansa[i]=ansb[i]=-1;
			continue;
		}
		int x=low[a[i]],r1=1,r2=a[i];
		while(r2%x==0)r1*=x,r2/=x;
		if(r2!=1)ansa[i]=r1,ansb[i]=r2;
		else ansa[i]=ansb[i]=-1;
	}
	rep(i,1,n)printf("%d ",ansa[i]);puts("");
	rep(i,1,n)printf("%d ",ansb[i]);puts("");
	return 0;
}