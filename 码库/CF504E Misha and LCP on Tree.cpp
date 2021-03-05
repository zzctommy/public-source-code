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

const int N=300005;
#define mod1 998244353
#define mod2 1004535809
#define base1 31
#define base2 37
inline int qpow(int n,int k,int mod){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
int n,m,h[N];
char str[N];
struct edge{int nx,to;}e[N<<1];
int hed[N],et;
inline void adde(int u,int v){e[++et].nx=hed[u],e[et].to=v,hed[u]=et;}
int dep[N],son[N],top[N],len[N],fa[N],lg[N<<1],bz[20][N];
int pool[N<<2],*up[N],*dw[N],*mem=pool;
LL d1[N],d2[N],u1[N],u2[N],pw1[N],pw2[N],ipw1[N],ipw2[N];
int ST[20][N<<1],dfn[N],tmr;

void dfs1(int u,int ft){
	dep[u]=dep[ft]+1,bz[0][u]=fa[u]=ft,ST[0][dfn[u]=++tmr]=u;
	for(int i=1;1<<i<dep[u];++i)bz[i][u]=bz[i-1][bz[i-1][u]];
	u1[u]=(u1[ft]*base1+h[u])%mod1;
	u2[u]=(u2[ft]*base2+h[u])%mod2;
	d1[u]=(d1[ft]+pw1[dep[u]-1]*h[u])%mod1;
	d2[u]=(d2[ft]+pw2[dep[u]-1]*h[u])%mod2;
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs1(v,u),ST[0][++tmr]=u;
		if(len[v]>len[son[u]])son[u]=v;
	}
	len[u]=len[son[u]]+1;
}
void dfs2(int u,int tp){
	top[u]=tp;
	if(son[u])dfs2(son[u],tp);
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
	if(top[u]==u){
		up[u]=mem;
		for(int i=0,j=u;i<=len[u]&&j;j=fa[j],++i)*mem++=j;
		dw[u]=mem;
		for(int j=u;j;j=son[j])*mem++=j;
	}
}
inline int kthanc(int x,int k){
	if(!k)return x;
	int y=top[bz[lg[k]][x]];
	if(dep[x]-dep[y]>=k)return dw[y][dep[x]-dep[y]-k];
	else return up[y][k-dep[x]+dep[y]];
}
inline int LCA(int x,int y){
	if(dfn[x]>dfn[y])x^=y^=x^=y;
	int t=lg[dfn[y]-dfn[x]+1],t1=ST[t][dfn[x]],t2=ST[t][dfn[y]-(1<<t)+1];
	return dep[t1]<dep[t2]?t1:t2;
}
inline LL calc1(LL*h,int v,int u){//u is anc of v
	return (h[v]-h[fa[u]]*pw1[dep[v]-dep[fa[u]]]%mod1+mod1)%mod1;
}
inline LL calc2(LL*h,int v,int u){//u is anc of v
	return (h[v]-h[fa[u]]*pw2[dep[v]-dep[fa[u]]]%mod2+mod2)%mod2;
}
inline LL calc3(LL*h,int v,int u){//u is anc of v
	return (h[v]-h[u]+mod1)%mod1*ipw1[dep[u]]%mod1;
}
inline LL calc4(LL*h,int v,int u){//u is anc of v
	return (h[v]-h[u]+mod2)%mod2*ipw2[dep[u]]%mod2;
}

signed main(){
	scanf("%d%s",&n,str+1);
	rep(i,1,n)h[i]=str[i]-'a'+1;
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	lg[0]=-1;rep(i,1,n<<1)lg[i]=lg[i>>1]+1;
	pw1[0]=1;rep(i,1,n)pw1[i]=1ll*pw1[i-1]*base1%mod1;
	pw2[0]=1;rep(i,1,n)pw2[i]=1ll*pw2[i-1]*base2%mod2;
	ipw1[n]=qpow(pw1[n],mod1-2,mod1);per(i,n-1,0)ipw1[i]=1ll*ipw1[i+1]*base1%mod1;
	ipw2[n]=qpow(pw2[n],mod2-2,mod2);per(i,n-1,0)ipw2[i]=1ll*ipw2[i+1]*base2%mod2;
	dfs1(1,0),dfs2(1,1);
	rep(i,1,lg[tmr])rep(j,1,tmr){
		int x=ST[i-1][j],y=ST[i-1][j+(1<<(i-1))];
		ST[i][j]=dep[x]<dep[y]?x:y;
	}
//	rep(i,1,n)cerr<<d1[i]<<' ';cerr<<'\n';
//	rep(i,1,n)cerr<<d2[i]<<' ';cerr<<'\n';
//	rep(i,1,n)cerr<<u1[i]<<' ';cerr<<'\n';
//	rep(i,1,n)cerr<<u2[i]<<' ';cerr<<'\n';
//	rep(i,1,n)cerr<<pw1[i]<<' ';cerr<<'\n';
//	rep(i,1,n)cerr<<pw2[i]<<' ';cerr<<'\n';
	for(m=read();m;--m){
		int a=read(),b=read(),c=read(),d=read();
		int lca1=LCA(a,b),lca2=LCA(c,d);
		int dis1=dep[a]+dep[b]-2*dep[lca1],dis2=dep[c]+dep[d]-2*dep[lca2];
		int l=0,r=min(dis1,dis2),res=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			LL H1=dep[a]-dep[lca1]>=mid?calc1(u1,a,kthanc(a,mid)):
				(calc1(u1,a,lca1)+calc3(d1,kthanc(b,dis1-mid),lca1)*pw1[dep[a]-dep[lca1]+1])%mod1;
			LL H2=dep[c]-dep[lca2]>=mid?calc1(u1,c,kthanc(c,mid)):
				(calc1(u1,c,lca2)+calc3(d1,kthanc(d,dis2-mid),lca2)*pw1[dep[c]-dep[lca2]+1])%mod1;
			LL H3=dep[a]-dep[lca1]>=mid?calc2(u2,a,kthanc(a,mid)):
				(calc2(u2,a,lca1)+calc4(d2,kthanc(b,dis1-mid),lca1)*pw2[dep[a]-dep[lca1]+1])%mod2;
			LL H4=dep[c]-dep[lca2]>=mid?calc2(u2,c,kthanc(c,mid)):
				(calc2(u2,c,lca2)+calc4(d2,kthanc(d,dis2-mid),lca2)*pw2[dep[c]-dep[lca2]+1])%mod2;
//			cerr<<mid<<":"<<H1<<' '<<H2<<' '<<H3<<' '<<H4<<'\n';
			if(H1==H2&&H3==H4)l=mid+1,res=mid;
			else r=mid-1;
		}
		printf("%d\n",++res);
	}
}
/*
5
abcac
1 2
2 3
2 4
1 5
10
2 1 2 4
1 3 4 5
*/ 