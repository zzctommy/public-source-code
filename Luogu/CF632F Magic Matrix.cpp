//Orz cyn2006
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
const int N=2505;
int n,a[N][N],tot;
pair<int,pair<int,int> >b[N*N];
bitset<2505>bs[2505];
signed main(){
	n=read();
	rep(i,1,n)rep(j,1,n)a[i][j]=read(),b[++tot]=mkp(a[i][j],mkp(i,j));
	rep(i,1,n)if(a[i][i])return puts("NOT MAGIC"),0;
	rep(i,1,n)rep(j,1,n)if(a[i][j]!=a[j][i])return puts("NOT MAGIC"),0;
	sort(b+1,b+tot+1);
	for(int i=1;i<=tot;){
		int j=i;
		while(b[j+1].fi==b[i].fi)++j;
		rep(k,i,j){
			int x=b[k].se.fi,y=b[k].se.se;
			if((bs[x]&bs[y]).any())return puts("NOT MAGIC"),0;
		}
		rep(k,i,j){
			int x=b[k].se.fi,y=b[k].se.se;
			bs[x][y]=1;
		}
		i=j+1;
	}
	puts("MAGIC");
}