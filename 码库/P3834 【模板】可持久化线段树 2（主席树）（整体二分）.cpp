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
int n,m,a[N],lsh[N],b[N],len,ans[N];
struct node{int l,r,k,id;}q[N],q1[N],q2[N];
int tr[N];
inline void add(int x,int d){for(int i=x;i<=n;i+=i&-i)tr[i]+=d;}
inline int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
vector<int>vc[N];
void solve(int l,int r,int x,int y){
	if(x>y)return;
	if(l==r){
		rep(i,x,y)ans[q[i].id]=lsh[l];
		return;
	}
	int mid=(l+r)>>1,ii=0,jj=0,kk=x;
	rep(i,l,mid)for(int j:vc[i])add(j,1);
	rep(i,x,y){
		int t=ask(q[i].r)-ask(q[i].l-1);
		if(q[i].k<=t)q1[++ii]=q[i];
		else q2[++jj]=q[i],q2[jj].k-=t;
	}
	rep(i,l,mid)for(int j:vc[i])add(j,-1);
	rep(i,1,ii)q[kk++]=q1[i];
	rep(i,1,jj)q[kk++]=q2[i];
	solve(l,mid,x,x+ii-1),solve(mid+1,r,x+ii,y);
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)lsh[++len]=a[i]=read();
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	rep(i,1,n)b[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh,vc[b[i]].pb(i);
	rep(i,1,m)q[i].id=i,q[i].l=read(),q[i].r=read(),q[i].k=read();
	solve(1,len,1,m);
	rep(i,1,m)printf("%d\n",ans[i]);
	return 0;
}