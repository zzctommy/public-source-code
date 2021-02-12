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
#define int long long
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=210005;
#define mod 998244353
const int M=N*22;
const int inf=0x3f3f3f3f3f3f3f3f;
vector<pair<int,int> >g1[M],g2[M];
int n,m,pw2[N],ds1[M],ds2[N<<1],ans=inf;
bool vs1[M],vs2[N<<1];
int id(int dep,int x){return dep*n+x;}
void Dij1(){
	priority_queue<pair<int,int> >pq;
	memset(ds1,0x3f,sizeof(ds1));
	pq.push(mkp(ds1[id(0,1)]=0,id(0,1)));
	while(!pq.empty()){
		int u=pq.top().se;pq.pop();
		if(vs1[u])continue;vs1[u]=1;
		for(auto [w,v]:g1[u]){
			if(ckmin(ds1[v],ds1[u]+w)&&!vs1[v])pq.push(mkp(-ds1[v],v));
		}
	}
}
void Dij2(){
	priority_queue<pair<int,int> >pq;
	memset(ds2,0x3f,sizeof(ds2));
	pq.push(mkp(ds2[id(0,n)]=0,id(0,n)));
	pq.push(mkp(ds2[id(1,n)]=0,id(1,n)));
	while(!pq.empty()){
		int u=pq.top().se;pq.pop();
		if(vs2[u])continue;vs2[u]=1;
		for(auto [w,v]:g2[u])
			if(ckmin(ds2[v],ds2[u]+w)&&!vs2[v])pq.push(mkp(-ds2[v],v));
	}
}
signed main(){
	n=read(),m=read();
	pw2[0]=1;rep(i,1,N-1)pw2[i]=(pw2[i-1]<<1)%mod;
	rep(i,1,m){
		int x=read(),y=read();
		rep(j,0,19)
			if(j&1)g1[id(j,y)].pb(mkp(1,id(j,x)));
			else g1[id(j,x)].pb(mkp(1,id(j,y)));
		g2[id(0,x)].pb(mkp(1,id(0,y))),g2[id(1,y)].pb(mkp(1,id(1,x)));
	}
	rep(i,0,18)rep(j,1,n)g1[id(i,j)].pb(mkp(pw2[i],id(i+1,j)));
	Dij1();
	rep(i,0,19)ckmin(ans,ds1[id(i,n)]);
	if(ans!=inf)return cout<<ans<<'\n',0;
	rep(i,1,n)g2[id(0,i)].pb(mkp(pw2[20],id(1,i))),g2[id(1,i)].pb(mkp(pw2[20],id(0,i)));
	Dij2();
	int mi=inf,tmp=inf;
	rep(i,1,n){
		if(ds1[id(19,i)]<inf){
			int t1=19+(ds2[id(0,i)]>>20),t2=(ds2[id(0,i)]&(pw2[20]-1))+ds1[id(19,i)];
			if(ckmin(mi,t1))tmp=t2;
			else if(mi==t1)ckmin(tmp,t2);
		}
	}
	ans=(pw2[mi]-1+tmp)%mod;
	ans=(ans+mod-pw2[19]+1)%mod;
	cout<<ans<<'\n';
}