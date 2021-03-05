#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
int n,m;
int bz[20][N],st[N],dep[N],tmr,ed[N];
int et,hed[N];
struct edge{int nx,to;}e[N<<1];
inline void adde(int u,int v){
	e[++et].nx=hed[u],e[et].to=v,hed[u]=et;
}
void dfs(int u,int ft){
	dep[u]=dep[ft]+1,bz[0][u]=ft,st[u]=++tmr;
	for(int i=1;1<<i<dep[u];++i)bz[i][u]=bz[i-1][bz[i-1][u]];
	for(int i=hed[u];i;i=e[i].nx){
		int v=e[i].to;if(v==ft)continue;
		dfs(v,u);
	}
	ed[u]=tmr;
}
inline int kthanc(int u,int k){
	for(int i=0;i<=19;++i)
		if(k>>i&1)u=bz[i][u];
	return u;
}
namespace arr{
const int T=N*25;
int rt[N],val[T],ls[T],rs[T],tot;
void update(int&p,int pre,int pos,int d,int l=1,int r=m){
	p=++tot;
	ls[p]=ls[pre],rs[p]=rs[pre];
	if(l==r)return val[p]=d,void();
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],pos,d,l,mid);
	else update(rs[p],rs[pre],pos,d,mid+1,r);
}
int query(int p,int pos,int l=1,int r=m){
	if(!p)return 0;
	if(l==r)return val[p];
	int mid=(l+r)>>1;
	if(pos<=mid)return query(ls[p],pos,l,mid);
	else return query(rs[p],pos,mid+1,r);
}
}
namespace seg{
const int T=N*25;
int rt[N],val[T],ls[T],rs[T],tot;
void update(int&p,int pre,int pos,int d,int l=1,int r=n){
	p=++tot;
	val[p]=val[pre]+d,ls[p]=ls[pre],rs[p]=rs[pre];
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],pos,d,l,mid);
	else update(rs[p],rs[pre],pos,d,mid+1,r);
}
int query(int p,int ql,int qr,int l=1,int r=n){
	if(!p||ql>qr)return 0;
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ls[p],ql,qr,l,mid);
	if(mid<qr)res+=query(rs[p],ql,qr,mid+1,r);
	return res;
}

}
signed main(){
	n=read();
	rep(i,2,n){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}
	dfs(1,0);
	m=read();
	for(int i=1;i<=m;++i){
		int opt=read(),x=read(),y;
		if(opt==1){
			int lst=arr::query(arr::rt[i-1],dep[x]);
			int v=seg::query(seg::rt[lst],st[x],st[x]);
			seg::update(seg::rt[i],seg::rt[lst],st[x],v?-1:1);
			arr::update(arr::rt[i],arr::rt[i-1],dep[x],i);
		}else if(opt==2){
			y=read(),arr::rt[i]=arr::rt[i-1];
			if(y&1||y/2>=dep[x]){puts("0");continue;}
			int lst=arr::query(arr::rt[i],dep[x]);
			if(!y){puts(seg::query(seg::rt[lst],st[x],st[x])?"1":"0");continue;}
			int so=kthanc(x,y/2-1),f=bz[0][so];
			printf("%d\n",seg::query(seg::rt[lst],st[f],ed[f])-seg::query(seg::rt[lst],st[so],ed[so]));
		}else arr::rt[i]=arr::rt[x];
	}
}