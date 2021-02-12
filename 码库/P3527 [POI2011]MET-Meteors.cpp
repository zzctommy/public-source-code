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
int n,m,p[N],k,ans[N],L[N],R[N],D[N],o[N];
struct node{
	int p,id;
}q[N],q1[N],q2[N];
LL tr[N];
void add(int x,int d){for(int i=x;i<=m;i+=i&-i)tr[i]+=d;}
void add(int l,int r,int d){add(l,d),add(r+1,-d);}
LL ask(int x){LL res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
vector<int>vc[N];
void solve(int x,int y,int l,int r){
	if(l>r)return;
	if(x==y){
		rep(i,l,r)ans[q[i].id]=x;
		return;
	}
	int mid=(x+y)>>1,ii=0,jj=0,kk=l;
	rep(i,x,mid){
		if(L[i]<=R[i])add(L[i],R[i],D[i]);
		else add(1,R[i],D[i]),add(L[i],m,D[i]);
	}
	rep(i,l,r){
		LL res=0;
		for(int j:vc[q[i].id]){
			res+=ask(j);
			if(res>=q[i].p)break;
		}
		if(q[i].p<=res)q1[++ii]=q[i];
		else q2[++jj]=q[i],q2[jj].p-=res;
	}
	rep(i,x,mid){
		if(L[i]<=R[i])add(L[i],R[i],-D[i]);
		else add(1,R[i],-D[i]),add(L[i],m,-D[i]);
	}
	rep(i,1,ii)q[kk++]=q1[i];
	rep(i,1,jj)q[kk++]=q2[i];
	solve(x,mid,l,l+ii-1),solve(mid+1,y,l+ii,r);
}
signed main(){
	n=read(),m=read();
	rep(i,1,m)o[i]=read(),vc[o[i]].pb(i);
	rep(i,1,n)q[i].p=read(),q[i].id=i;
	k=read();
	rep(i,1,k)L[i]=read(),R[i]=read(),D[i]=read();
	solve(1,k+1,1,n);
	rep(i,1,n){
		if(ans[i]==k+1)puts("NIE");
		else printf("%d\n",ans[i]);
	}
	return 0;
}