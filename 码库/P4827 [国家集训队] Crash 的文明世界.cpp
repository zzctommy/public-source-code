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
const int N=50005;
const int K=152;
#define mod 10007
void fmod(int&x){x-=mod,x+=x>>31&mod;}
int n,k,f[N][K],g[N][K],S[K][K];
int hed[N],et;
struct edge{int nx,to;}e[N<<1];
void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
void dfs1(int u,int ft){
	f[u][0]=1;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u);
		rep(j,0,k){
			if(j>0)fmod(f[u][j]+=f[v][j-1]);
			fmod(f[u][j]+=f[v][j]);
		}
	}
}
void dfs2(int u,int ft){
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		rep(j,0,k){
			g[v][j]=f[v][j];
			g[v][j]=(g[v][j]+g[u][j]-f[v][j])%mod;
			if(j>0){
				g[v][j]=(g[v][j]+mod-f[v][j-1])%mod;
				g[v][j]=(g[v][j]+g[u][j-1]-f[v][j-1]+mod)%mod;
				if(j>1)g[v][j]=(g[v][j]+mod-f[v][j-2])%mod;
			}
		}
		dfs2(v,u);
	}
}
signed main(){
	n=read(),k=read();
	rep(i,2,n){int x=read(),y=read();adde(x,y),adde(y,x);}
	S[1][1]=1;
	rep(i,2,k)rep(j,1,k)S[i][j]=(S[i-1][j-1]+j*S[i-1][j])%mod;
	dfs1(1,0);
	rep(i,0,k)g[1][i]=f[1][i];
	dfs2(1,0);
	for(int i=1;i<=n;++i){
		int res=0;
		for(int j=0,fac=1;j<=k;++j,fac=1ll*fac*j%mod)fmod(res+=1ll*S[k][j]*fac%mod*g[i][j]%mod);
		printf("%d\n",res);
	}
	return 0;
}