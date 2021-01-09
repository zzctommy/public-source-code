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
const int N=100005;
const int M=200005;
int n,m,cnt[M],ans[M],now,sum[M],S,a[N];
struct que{
	int l,r,id;
	que(){l=r=id=0;}
	inline bool operator < (const que&t)const{return l/S!=t.l/S?l<t.l:(l/S)&1?r<t.r:r>t.r;}
}q[M];
void add(int x){
	++cnt[x];
	if(!sum[cnt[x]]++)++now;
}
void pop(int x){
	if(!--sum[cnt[x]])--now;
	--cnt[x];
}
signed main(){
	n=read(),m=read(),S=(n-1)/sqrt(m)+1;
	rep(i,1,n)a[i]=read()+100000;
	rep(i,1,m)q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+m+1);
	for(int i=1,l=1,r=0;i<=m;++i){
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)pop(a[l++]);
		while(r>q[i].r)pop(a[r--]);
		ans[q[i].id]=now;
	}
	rep(i,1,m)printf("%d\n",ans[i]);
	return 0;
}