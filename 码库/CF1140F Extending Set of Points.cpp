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
const int C=N-5;
int n,x[N],y[N],L[N],R[N],F[N<<1],sx[N<<1],sy[N<<1];
LL now,ans[N];
map<pair<int,int>,int>mp;
#define lc (p<<1)
#define rc (p<<1|1)
vector<pair<int,int> >v[N<<2];
void update(int ql,int qr,pair<int,int>d,int l=1,int r=n,int p=1){
	if(ql<=l&&r<=qr)return v[p].pb(d),void();
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,d,l,mid,lc);
	if(mid<qr)update(ql,qr,d,mid+1,r,rc);
}
vector<int>stk;
int anc(int x){while(x!=F[x])x=F[x];return x;}
void merge(int x,int y){
	int fx=anc(x),fy=anc(y);
	if(fx==fy)return;
	now-=1ll*sx[fx]*sy[fx];
	now-=1ll*sx[fy]*sy[fy];
	if(sx[fx]+sy[fx]<sx[fy]+sy[fy])swap(fx,fy);
	stk.pb(fy),F[fy]=fx,sx[fx]+=sx[fy],sy[fx]+=sy[fy];
	now+=1ll*sx[fx]*sy[fx];
}
void undo(){
	int x=stk.back(),y=F[x];stk.pop_back();
	now-=1ll*sx[y]*sy[y];
	sx[y]-=sx[x],sy[y]-=sy[x],F[x]=x;
	now+=1ll*sx[x]*sy[x];
	now+=1ll*sx[y]*sy[y];
}
void solve(int l,int r,int p){
	int nowsize=sz(stk);
	for(vector<pair<int,int> >::iterator i=v[p].begin();i!=v[p].end();++i){
		int x=i->fi,y=i->se+C;
		merge(x,y);
	}
	if(l==r)ans[l]=now;
	else{
		int mid=(l+r)>>1;
		solve(l,mid,lc),solve(mid+1,r,rc);
	}
	while(sz(stk)>nowsize)undo();
}
signed main(){
	rep(i,1,C)F[i]=i,sx[i]=1,sy[i]=0;
	rep(i,C+1,C<<1)F[i]=i,sx[i]=0,sy[i]=1;
	n=read();
	rep(i,1,n){
		x[i]=read(),y[i]=read();
		if(!mp[mkp(x[i],y[i])])L[i]=i,R[i]=n,mp[mkp(x[i],y[i])]=i;
		else R[mp[mkp(x[i],y[i])]]=i-1,mp[mkp(x[i],y[i])]=0;
	}
	rep(i,1,n)if(L[i]==i)update(L[i],R[i],mkp(x[i],y[i]));
	solve(1,n,1);
	rep(i,1,n)printf("%lld ",ans[i]);
	return 0;
}