//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 20005
#define K 105
#define T (N<<2)
#define inf 1000000005
int n,k,D[N],C[N],S[N],W[N],dp[N],ans,L[N],R[N],pre[N],suf[N];
vector<pair<int,int> >v1[N],v2[N];
int val[T],tag[T];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){val[p]=min(val[lc],val[rc]);}
void build(int l=1,int r=n,int p=1){
	tag[p]=0;
	if(l==r)return val[p]=min(dp[l],inf),void();
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	pushup(p);
}
void pushdown(int p){
	if(tag[p]){
		val[lc]+=tag[p],val[rc]+=tag[p];
		tag[lc]+=tag[p],tag[rc]+=tag[p];
		tag[p]=0;
	}
}
void update(int ql,int qr,int k,int l=1,int r=n,int p=1){
	if(ql>qr)return;
	if(ql<=l&&r<=qr)return val[p]+=k,tag[p]+=k,void();
	pushdown(p);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,k,l,mid,lc);
	if(mid<qr)update(ql,qr,k,mid+1,r,rc);
	pushup(p);
}
int query(int ql,int qr,int l=1,int r=n,int p=1){
	if(ql>qr)return inf;
	if(ql<=l&&r<=qr)return val[p];
	pushdown(p);
	int mid=(l+r)>>1;
	if(qr<=mid)return query(ql,qr,l,mid,lc);
	if(mid<ql)return query(ql,qr,mid+1,r,rc);
	return min(query(ql,qr,l,mid,lc),query(ql,qr,mid+1,r,rc));
}
signed main(){
	n=read(),k=read();
	for(int i=2;i<=n;++i)D[i]=read();
	for(int i=1;i<=n;++i)C[i]=read();
	for(int i=1;i<=n;++i)S[i]=read();
	for(int i=1;i<=n;++i)W[i]=read();
	for(int i=1;i<=n;++i){
		L[i]=lower_bound(D+1,D+n+1,D[i]-S[i])-D;
		R[i]=upper_bound(D+1,D+n+1,D[i]+S[i])-D-1;
		v1[R[i]].pb(mkp(L[i],i)),v2[L[i]].pb(mkp(R[i],i));
	}
	for(int i=1;i<=n;++i){
		pre[i]+=pre[i-1];
		for(int j=0,sz=v1[i].size();j<sz;++j)pre[i+1]+=W[v1[i][j].se];
	}
	for(int i=n;i>=1;--i){
		suf[i]+=suf[i+1];
		for(int j=0,sz=v2[i].size();j<sz;++j)suf[i-1]+=W[v2[i][j].se];
	}
	// for(int i=1;i<=n;++i)cerr<<L[i]<<' ';cerr<<'\n';
	// for(int i=1;i<=n;++i)cerr<<R[i]<<' ';cerr<<'\n';
	// for(int i=1;i<=n;++i)cerr<<pre[i]<<' ';cerr<<'\n';
	// for(int i=1;i<=n;++i)cerr<<suf[i]<<' ';cerr<<'\n';
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;++i)ans+=W[i];
	if(!k)return printf("%d\n",ans),0;
	for(int i=1;i<=n;++i)dp[i]=pre[i]+C[i],ans=min(ans,dp[i]+suf[i]);
	// for(int j=1;j<=n;++j)cerr<<dp[j]<<' ';cerr<<'\n';
	// cerr<<ans<<'\n';
	for(int t=2;t<=k;++t){
		build();
		for(int i=1;i<=n;++i){
			dp[i]=query(1,i-1)+C[i],ans=min(ans,dp[i]+suf[i]);
			for(int j=0,sz=v1[i].size();j<sz;++j)update(1,v1[i][j].fi-1,W[v1[i][j].se]);
			// for(int j=1;j<=i;++j)cerr<<query(j,j)<<' ';cerr<<'\n';
		}
		// for(int j=1;j<=n;++j)cerr<<dp[j]<<' ';cerr<<'\n';
	}
	printf("%d\n",ans);
	return 0;
}
/*
5 3
10 14 22 26 
13 16 14 19 16 
2 5 4 3 3 
2 7 4 11 13 


*/
