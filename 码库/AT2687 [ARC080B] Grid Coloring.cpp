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
const int N=105;
int w,h,n,tot,ans[N][N];
pair<int,int>p[N*N];
signed main(){
	w=read(),h=read(),n=read();
	rep(i,1,w){
		if(i&1)rep(j,1,h)p[++tot]=mkp(i,j);
		else per(j,h,1)p[++tot]=mkp(i,j);
	}
	rep(i,1,n){
		int x=read();
		while(x--)ans[p[tot].fi][p[tot].se]=i,--tot;
	}
	rep(i,1,w)rep(j,1,h)printf("%d%c",ans[i][j]," \n"[j==h]);
	return 0;
}