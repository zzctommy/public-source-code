#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
const int N=50005;
const int M=1000005;
int n,m,a[N],nq,nu,S,bel[N],ans[N],cnt[M],now;
struct que{
	int l,r,id,pre;
	inline bool operator < (const que&t)const{return bel[l]!=bel[t.l]?l<t.l:bel[r]!=bel[t.r]?r<t.r:pre<t.pre;}
}q[N];
struct upd{int x,y,id;}u[N];
void add(int x){if(!cnt[x]++)++now;}
void pop(int x){if(!--cnt[x])--now;}
void modify(int x,int l,int r){
	if(u[x].x>=l&&u[x].x<=r)pop(a[u[x].x]),add(u[x].y);
	swap(a[u[x].x],u[x].y);
}
signed main(){
	n=read(),m=read(),S=pow(n,0.666);
	rep(i,1,n)a[i]=read(),bel[i]=(i-1)/S+1;
	rep(i,1,m){
		char ch=getchar();
		while(ch!='M'&&ch!='Q')ch=getchar();
		if(ch=='M')++nu,u[nu].x=read()+1,u[nu].y=read(),u[nu].id=nu;
		else ++nq,q[nq].l=read()+1,q[nq].r=read(),q[nq].id=nq,q[nq].pre=nu;
	}
	sort(q+1,q+nq+1);
	for(int i=1,l=1,r=0,ud=0;i<=m;++i){
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)pop(a[l++]);
		while(r>q[i].r)pop(a[r--]);
		while(ud<q[i].pre)modify(++ud,q[i].l,q[i].r);
		while(ud>q[i].pre)modify(ud--,q[i].l,q[i].r);
		ans[q[i].id]=now;
	}
	rep(i,1,nq)printf("%d\n",ans[i]);
	return 0;
}