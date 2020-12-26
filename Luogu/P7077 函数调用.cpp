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
const int M=1000005;
#define mod 998244353
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,a[N],m,q,T[N],p[N],v[N],f[N];
int tpn[N],ind[N],mul[N],sum[N];
int et,hed[N];
struct edge{int nx,to;}e[M];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void topo(){
	queue<int>q; 
	rep(i,1,m)if(!ind[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop(),tpn[++tpn[0]]=u;
		for(int i=hed[u];i;i=e[i].nx)if(!--ind[e[i].to])q.push(e[i].to);
	}
}
signed main(){
	n=read();
	rep(i,1,n)a[i]=read();
	m=read();
	rep(i,1,m){
		T[i]=read();
		if(T[i]==1)p[i]=read(),v[i]=read(),mul[i]=1;
		else if(T[i]==2)v[i]=read(),mul[i]=v[i];
		else{
			int c=read(),x;mul[i]=1;
			rep(j,1,c)adde(i,x=read()),++ind[x];
		}
	}
	topo();
	per(i,m,1){
		int u=tpn[i];
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;mul[u]=1ll*mul[u]*mul[v]%mod;
		}
	}
	q=read();
	rep(i,1,q)f[i]=read();
	int tmp=1;
	per(i,q,1)fmod(sum[f[i]]+=tmp),tmp=1ll*tmp*mul[f[i]]%mod;
	rep(i,1,n)a[i]=1ll*a[i]*tmp%mod;
	rep(i,1,m){
		int u=tpn[i],now=1;
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;fmod(sum[v]+=1ll*sum[u]*now%mod),now=1ll*now*mul[v]%mod;
		}
	}
	rep(i,1,m)if(T[i]==1)fmod(a[p[i]]+=1ll*sum[i]*v[i]%mod);
	rep(i,1,n)printf("%d ",a[i]);
	return 0;
}