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
int n,m;
LL ans;
const int N=502;
bitset<N>bz[N][61][2],nw;
signed main(){
	n=read(),m=read();
	rep(i,1,m){
		int x=read(),y=read(),z=read();
		bz[x][0][z].set(y);
	}
	rep(i,1,60){
		static bitset<N>bt0,bt1;
		rep(j,1,n){
			bt0.reset(),bt1.reset();
			rep(k,1,n){
				if(bz[j][i-1][0][k])bt0|=bz[k][i-1][1];
				if(bz[j][i-1][1][k])bt1|=bz[k][i-1][0];
			}
			bz[j][i][0]=bt0,bz[j][i][1]=bt1;
		}
	}
	rep(i,1,n)nw.set(i);
	int t=0;
	per(i,60,0){
		static bitset<N>nx;
		nx.reset();
		for(int j=1;j<=n;++j)if(nw[j])nx|=bz[j][i][t];
		if(nx.any())nw=nx,ans|=1ll<<i,t^=1;
	}
	if(ans>1e18)cout<<-1<<'\n';
	else cout<<ans<<'\n';
}