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
int n,a[N],tot,b[N],c[N];
vector<pair<int,int> >ans;
void Main(){
	n=read(),tot=0;
	ans.clear();
	fill(b+1,b+n+1,0);
	int x=n;
	a[++tot]=n,c[tot]=n,b[n]=1;
	while(1){
		x=ceil(sqrt(x));
		a[++tot]=x,c[tot]=x,b[x]=1;
		if(x==2)break;
	}
	for(int i=2;i<n;++i)if(!b[i])ans.pb(mkp(i,n));
	for(int i=2;i<=tot;++i){
		while(a[i-1]>1)ans.pb(mkp(c[i-1],c[i])),a[i-1]=ceil(1.*a[i-1]/a[i]);
	}
	printf("%d\n",sz(ans));
	for(int i=0;i<sz(ans);++i)printf("%d %d\n",ans[i].fi,ans[i].se);
}
signed main(){for(int T=read();T;--T)Main();}