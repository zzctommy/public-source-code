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
const int N=505;
const int M=60005;
int n,m,a[N][N],lsh[N*N],b[N][N],len,ans[M];
vector<pair<int,int> >vc[N*N];
struct node{
	int a1,b1,a2,b2,k,id;
}q[M],q1[M],q2[M];
int tr[N][N];
void add(int x,int y,int d){
	for(int i=x;i<=n;i+=i&-i)
		for(int j=y;j<=n;j+=j&-j)
			tr[i][j]+=d;
}
int ask(int x,int y){
	int res=0;
	for(int i=x;i>0;i-=i&-i)
		for(int j=y;j>0;j-=j&-j)
			res+=tr[i][j];
	return res;
}
void solve(int l,int r,int x,int y){
	if(x>y)return;
	if(l==r){
		rep(i,x,y)ans[q[i].id]=lsh[l];
		return;
	}
	int mid=(l+r)>>1,ii=0,jj=0,kk=x;
	rep(i,l,mid)for(pair<int,int>j:vc[i])add(j.fi,j.se,1);
	rep(i,x,y){
		int t=ask(q[i].a2,q[i].b2)+ask(q[i].a1-1,q[i].b1-1)
			-ask(q[i].a2,q[i].b1-1)-ask(q[i].a1-1,q[i].b2);
		if(q[i].k<=t)q1[++ii]=q[i];
		else q2[++jj]=q[i],q2[jj].k-=t;
	}
	rep(i,l,mid)for(pair<int,int>j:vc[i])add(j.fi,j.se,-1);
	rep(i,1,ii)q[kk++]=q1[i];
	rep(i,1,jj)q[kk++]=q2[i];
	solve(l,mid,x,x+ii-1),solve(mid+1,r,x+ii,y);
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)rep(j,1,n)lsh[++len]=a[i][j]=read();
	rep(i,1,m)q[i].id=i,q[i].a1=read(),q[i].b1=read(),
		q[i].a2=read(),q[i].b2=read(),q[i].k=read();
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	rep(i,1,n)rep(j,1,n){
		b[i][j]=lower_bound(lsh+1,lsh+len+1,a[i][j])-lsh;
		vc[b[i][j]].pb(mkp(i,j));
	}
	solve(1,len,1,m);
	rep(i,1,m)printf("%d\n",ans[i]);
	return 0;
}