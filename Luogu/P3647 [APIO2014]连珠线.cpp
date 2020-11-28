#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 200005
#define inf (0x3f3f3f3f)
int n,ans,fa[N],f[N][2],rlen[N];
vector<int>e[N],q[N],w[N],h[N][2];
void dfs1(int u,int ft){
	int Mx=-inf,mx=-inf,flg=0;
	for(int i=0;i<sz(e[u]);++i)
		if(e[u][i]==ft){swap(e[u][i],e[u][sz(e[u])-1]),swap(w[u][i],w[u][sz(w[u])-1]),flg=1;break;}
	if(flg)e[u].pop_back();
	for(int i=0;i<sz(e[u]);++i){
		int v=e[u][i];
		dfs1(v,u),fa[v]=u,rlen[v]=w[u][i];
		f[u][0]+=max(f[v][0],f[v][1]+w[u][i]);
		int tmp=f[v][0]+w[u][i]-max(f[v][0],f[v][1]+w[u][i]);
		if(tmp>Mx)mx=Mx,Mx=tmp;
		else if(tmp>mx)mx=tmp;
	}
	f[u][1]=f[u][0]+Mx;
	for(int i=0;i<sz(e[u]);++i){
		int v=e[u][i];
		h[u][0].pb(f[u][0]-max(f[v][0],f[v][1]+w[u][i]));
		int tmp=f[v][0]+w[u][i]-max(f[v][0],f[v][1]+w[u][i]);
		if(tmp==Mx)q[u].pb(mx),h[u][1].pb(h[u][0][i]+mx);
		else q[u].pb(Mx),h[u][1].pb(h[u][0][i]+Mx);
	}
}
void dfs2(int u,int ft){
	for(int i=0;i<sz(e[u]);++i){
		int v=e[u][i];if(v==ft)continue;
		f[u][0]=h[u][0][i],f[u][1]=h[u][1][i];
		if(fa[u]){
			f[u][0]+=max(f[fa[u]][0],f[fa[u]][1]+rlen[u]);
			f[u][1]=f[u][0]+max(q[u][i],f[fa[u]][0]+rlen[u]-max(f[fa[u]][0],f[fa[u]][1]+rlen[u]));
		}
		ans=max(ans,f[v][0]+max(f[u][0],f[u][1]+w[u][i]));
		dfs2(v,u);
	}
}
signed main(){
	n=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		e[x].pb(y),w[x].pb(z);
		e[y].pb(x),w[y].pb(z);
	}
	dfs1(1,0),dfs2(1,0);
	printf("%d\n",ans);
	return 0;
}