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
const int N=100005;
#define FAIL return puts("NO"),void()
int n,a[N],b[N],c[N],m,cnt[N],ned[N];
vector<int>v[N];
void Main(){
	n=read(),m=read();
	rep(i,1,n)a[i]=read(),cnt[i]=ned[i]=0,v[i].clear();
	rep(i,1,n){
		b[i]=read();
		if(a[i]!=b[i])++ned[b[i]],v[b[i]].pb(i);
	}
	rep(i,1,m)c[i]=read(),++cnt[c[i]];
	int id=0;
	rep(i,1,n)if(c[m]==b[i]){id=i;break;}
	if(ned[c[m]])id=v[c[m]][0];
	if(!id)FAIL;
	rep(i,1,n)if(cnt[i]<ned[i])FAIL;
	puts("YES");
	rep(i,1,m){
		if(ned[c[i]])printf("%d ",v[c[i]][--ned[c[i]]]);
		else printf("%d ",id);
	}
	puts("");
}
signed main(){for(int T=read();T;--T)Main();}