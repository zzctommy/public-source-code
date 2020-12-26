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
const int M=821535+5;
#define mod 1000000007
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
int A,B,C,mx,ans;
int mu[N],pri[N],pct,sum[N],tot,tag[N];
bool vis[N];
vector<int>d[N];
int U[M],V[M],ord[N],deg[N],tu[M],tv[M],cnt,LCM[M],id[M];
vector<pair<int,int> >e[N];
pair<int,int>p[N];
void init(const int&N){
	mu[1]=1;
	for(int i=2;i<=N;++i){
		if(!vis[i])pri[++pct]=i,mu[i]=-1;
		for(int j=1;j<=pct&&i*pri[j]<=N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=N;++i){
		if(!mu[i])continue;
		for(int j=1;i*j<=N;++j)if(mu[i*j])d[i].pb(i*j);
	}
	for(int i=1;i<=N;++i)
		for(int j=0,up=sz(d[i]);j<up;++j)
			for(int k=j;k<up&&1ll*d[i][j]*d[i][k]/i<=N;++k)
				if(__gcd(d[i][j],d[i][k])==i)U[++tot]=d[i][j],V[tot]=d[i][k],LCM[tot]=d[i][j]/i*d[i][k];
	for(int i=1;i<=N;++i){
		int res=0;
		for(int l=1,r;l<=i;l=r+1)
			r=i/(i/l),res+=(i/l)*(r-l+1);
		sum[i]=res;
	}
}
int lcm(int x,int y){return x/__gcd(x,y)*y;}
LL f(int x,int y,int z){return 1ll*sum[x]*sum[y]*sum[z];}
void Main(){
	A=read(),B=read(),C=read(),mx=max(A,max(B,C)),fill(deg+1,deg+mx+1,0),fill(tag+1,tag+mx+1,0),ans=0,cnt=0;
	rep(i,1,tot)if(LCM[i]<=mx)++deg[U[i]],++deg[V[i]],++cnt,tu[cnt]=U[i],tv[cnt]=V[i],id[cnt]=i;
	rep(i,1,mx)p[i]=mkp(deg[i],i);
	sort(p+1,p+mx+1);
	rep(i,1,mx)ord[p[i].se]=i,e[i].clear();
	rep(i,1,cnt)
		if(ord[tu[i]]>ord[tv[i]])e[tu[i]].pb(mkp(tv[i],LCM[id[i]]));
		else e[tv[i]].pb(mkp(tu[i],LCM[id[i]]));
	rep(u,1,mx){
		for(int i=0,up=sz(e[u]);i<up;++i)tag[e[u][i].fi]=u;
		for(int i=0,up1=sz(e[u]);i<up1;++i){
			int v=e[u][i].fi;
			for(int j=0,up2=sz(e[v]);j<up2;++j){
				int w=e[v][j].fi;
				if(tag[w]==u){
					int x=e[u][i].se,y=e[v][j].se,z=lcm(w,u);unsigned long long res=0;
					if(u!=v&&u!=w&&v!=w)
						res=f(A/x,B/y,C/z)+f(A/x,B/z,C/y)+f(A/y,B/x,C/z)+f(A/y,B/z,C/x)+f(A/z,B/x,C/y)+f(A/z,B/y,C/x);
					else if(u==v&&u==w&&v==w)res=f(A/x,B/y,C/z);
					else res=f(A/x,B/y,C/z)+f(A/y,B/z,C/x)+f(A/z,B/x,C/y);
					int t=res%mod;
					fmod(ans+=1ll*mu[u]*mu[v]*mu[w]*t);
				}
			}
		}
	}
	printf("%d\n",ans);
}
signed main(){
	init(100000);
	for(int T=read();T;--T)Main();
}
/*
5
10 10 10
100 100 100
1000 1000 1000
10000 10000 10000
100000 100000 100000

2
100000 100000 100000
100000 100000 100000

*/