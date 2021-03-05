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
int n,num[N],m,a[N],mi[N],F[N],flg=1,ans,sum[N];
vector<pair<int,int> >e[N];
multiset<int>vc[N];
inline int anc(int x){return x==F[x]?x:F[x]=anc(F[x]);}
void merge(int x,int y,int lim){
	static vector<int>tmp;
	x=anc(x),y=anc(y);
	if(sz(vc[x])<sz(vc[y]))x^=y^=x^=y;
	F[y]=x;
	// cerr<<"merge:"<<x<<' '<<y<<' '<<lim<<'\n';
	// for(int i:vc[x])cerr<<i<<' ';cerr<<'\n';
	// for(int i:vc[y])cerr<<i<<' ';cerr<<'\n';
	for(int i:vc[y])vc[x].insert(i);
	while(sz(vc[x])>lim)vc[x].erase(vc[x].begin());
	// for(int i:vc[x])cerr<<i<<' ';cerr<<'\n';
}
void dfs1(int u,int ft){
	if(sz(e[u])>1&&a[u])num[u]=1,sum[u]=sz(e[u])-1;
	for(pair<int,int>i:e[u]){
		int w=i.fi,v=i.se;
		if(v==ft)continue;
		a[v]|=a[u],mi[v]=min(w,mi[u]);
		dfs1(v,u);
		num[u]+=num[v],sum[u]+=sum[v];
	}
//	cerr<<u<<' '<<mi[u]<<' '<<num[u]<<' '<<sum[u]<<'\n';
	if(num[u]>mi[u])flg=0;
}
void dfs2(int u,int ft){
	if(u!=1&&sz(e[u])==1)return;
	if(u!=1&&a[u])vc[u].insert(sz(e[u])-1);
	for(pair<int,int>i:e[u]){
		int w=i.fi,v=i.se;
		if(v==ft)continue;
		dfs2(v,u);
		if(u!=1){
			merge(u,v,mi[u]);
		}else{
			for(int j:vc[anc(v)])ans-=j;
		}
	}
	// cerr<<u<<":";for(int i:vc[u])cerr<<i<<' ';cerr<<'\n';
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)F[i]=i;
	rep(i,2,n){
		int x=read(),y=read(),z=read();
		e[x].pb(mkp(z,y)),e[y].pb(mkp(z,x));
	}
	rep(i,1,m)a[read()]=1;
	mi[1]=n-1;
	dfs1(1,0);
	// rep(i,1,n)cerr<<mi[i]<<' ';cerr<<'\n';
	if(flg)return cout<<"Yes\n"<<num[1]<<'\n',0;
	ans=sum[1];
	dfs2(1,0);
	cout<<"No\n"<<ans<<'\n';
}
/*
14 2
1 2 1
2 3 1
2 6 1
3 4 1
3 5 1
1 7 1
7 8 1
7 9 1
8 10 1
8 11 1
9 12 1
9 13 1
3 14 1
2 8

*/
