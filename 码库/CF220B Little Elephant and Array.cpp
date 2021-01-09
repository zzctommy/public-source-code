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
const int N=1000005;
int n,m,a[N],num[N],lst[N],tr[N],nxt[N],ans[N],pre[N];
struct QUE{int l,r,id;}q[N];
inline bool cmp(const QUE&a,const QUE&b){return a.r!=b.r?a.r<b.r:a.l<b.l;}
void add(int x,int d){if(!x)return;for(int i=x;i<=n;i+=i&-i)tr[i]+=d;}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
signed main(){
	n=read(),m=read();
	rep(i,1,n){
		a[i]=read();
		if(a[i]>n)a[i]=0;
	}
	rep(i,1,m)q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	rep(i,1,n)lst[i]=n+1;
	per(i,n,1)nxt[i]=lst[a[i]],lst[a[i]]=i;
	rep(i,1,n)lst[i]=0;
	rep(i,1,n)pre[i]=lst[a[i]],lst[a[i]]=i;
	memset(lst,0,sizeof(lst));
	int it=1;
	rep(i,1,m){
		for(;it<=q[i].r;++it){
			if(!a[it])continue;
			if(!lst[a[it]])lst[a[it]]=it;
			++num[a[it]];
			if(num[a[it]]>=a[it]){
				add(lst[a[it]],1);
				add(pre[lst[a[it]]],-2);
				add(pre[pre[lst[a[it]]]],1);
				// cerr<<lst[a[it]]<<' '<<pre[lst[a[it]]]<<' '<<pre[pre[lst[a[it]]]]<<'\n';
				lst[a[it]]=nxt[lst[a[it]]];
			}
			// cerr<<"it="<<it<<'\n';
			// cerr<<"num:";rep(j,1,5)cerr<<num[j]<<' ';cerr<<'\n';
			// cerr<<"lst:";rep(j,1,5)cerr<<lst[j]<<' ';cerr<<'\n';
			// cerr<<"tr:";rep(j,1,n)cerr<<ask(j)-ask(j-1)<<' ';cerr<<'\n';
		}
		ans[q[i].id]=ask(q[i].r)-ask(q[i].l-1);
		// cerr<<"calc:"<<q[i].id<<' '<<ans[q[i].id]<<'\n';
	}
	rep(i,1,m)printf("%d\n",ans[i]);
	return 0;
}