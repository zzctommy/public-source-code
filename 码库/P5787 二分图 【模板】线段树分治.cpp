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
const int N=200005;
const int M=N<<1;
const int T=N<<2;
int n,m,k,ans[N];
vector<pair<int,int> >upd[T];
namespace dsu{
int F[M],siz[M];
vector<int>stk;
void init(const int&n){
	rep(i,1,n)F[i]=i,siz[i]=1;
}
int anc(int x){while(x!=F[x])x=F[x];return x;}
void merge(int x,int y){
	x=anc(x),y=anc(y);
	if(x==y)return;
	if(siz[x]<siz[y])swap(x,y);
	F[y]=x,siz[x]+=siz[y],stk.pb(y);
}
void undo(){
	assert(stk.size());
	int x=stk.back();stk.pop_back();
	siz[F[x]]-=siz[x],F[x]=x;
}

}
#define lc (p<<1)
#define rc (p<<1|1)
void update(int ql,int qr,int x,int y,int l=1,int r=k,int p=1){
	if(ql<=l&&r<=qr)return upd[p].pb(mkp(x,y)),void();
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,x,y,l,mid,lc);
	if(mid<qr)update(ql,qr,x,y,mid+1,r,rc);
}
void solve(int l,int r,int p){
	int tmp=sz(dsu::stk),flg=1;
	for(int i=0,up=sz(upd[p]);i<up;++i){
		int x=upd[p][i].fi,y=upd[p][i].se;
		if(dsu::anc(x)==dsu::anc(y)){flg=0;rep(i,l,r)ans[i]=0;;break;}
		dsu::merge(x+n,y),dsu::merge(y+n,x);
	}
	if(l==r)ans[l]=flg;
	else if(flg){int mid=(l+r)>>1;solve(l,mid,lc),solve(mid+1,r,rc);}
	while(sz(dsu::stk)>tmp)dsu::undo();
}
signed main(){
	n=read(),m=read(),k=read();
	rep(i,1,m){
		int x=read(),y=read(),l=read(),r=read();
		if(l==r)continue;update(l+1,r,x,y);
	}
	dsu::init(n<<1),solve(1,k,1);
	rep(i,1,k)puts(ans[i]?"Yes":"No");
	return 0;
}