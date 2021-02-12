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
int n,k,a[N],b[N],c[N],col[N],tot,vis[N],ans[N];
vector<int>v[N],p[N];
signed main(){
	n=read(),k=read();
	rep(i,1,k)a[i]=read(),b[i]=read();
	rep(i,1,n)c[i]=i;
	rep(i,1,k)swap(c[a[i]],c[b[i]]);
	rep(i,1,n){
		if(col[i])continue;
		col[i]=++tot,v[tot].pb(i);
		for(int j=c[i];j!=i;j=c[j])col[j]=tot,v[tot].pb(j);
	}
	rep(i,1,n)c[i]=i;
	rep(i,1,k){
		p[col[c[a[i]]]].pb(b[i]),p[col[c[b[i]]]].pb(a[i]);
		swap(c[a[i]],c[b[i]]);
	}
	rep(i,1,tot){
		for(int j:v[i])if(vis[j]!=i)vis[j]=i,++ans[i];
		for(int j:p[i])if(vis[j]!=i)vis[j]=i,++ans[i];
	}
	rep(i,1,n)printf("%d\n",ans[col[i]]);
	return 0;
}