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

const int N=1005;
bitset<N>bs[N],nr[N],nw[N];
int n,m,rt,id[N],sz[N];
bool vis[N],used[N];
vector<int>e[N];
signed main(){
	n=read();
	if(n==2)return puts("1 2"),0;
	rep(i,1,n){
		sz[i]=read();
		rep(t,1,sz[i])bs[i][read()]=1;
	}
	rep(i,1,n)rep(j,i+1,n){
		bitset<N>tmp=bs[i]&bs[j];
		if(tmp.count()==2){
			int x=tmp._Find_first(),y=tmp._Find_next(x);
			if(!nr[x][y])e[x].pb(y),e[y].pb(x),nr[x][y]=1,nr[y][x]=1,cerr<<"edge:"<<x<<' '<<y<<'\n';
			if(!vis[x])++m,vis[x]=1,nr[x][x]=1;
			if(!vis[y])++m,vis[y]=1,nr[y][y]=1;
		}
	}
	cerr<<"m="<<m<<'\n';
	if(m==0){
		rep(i,2,n)printf("%d %d\n",i,1);
		return 0;
	}
	if(m==2){
		int r1=0,r2=0;
		for(int i=1;i<=n;++i)if(vis[i]){
			if(!r1)r1=i;else r2=i;
		}
		rep(i,1,n)if(sz[i]!=n){
			rep(j,1,n)if(j!=r1){
				if(bs[i][j])printf("%d %d\n",j,r1);
				else printf("%d %d\n",j,r2);
			}
			break;
		}
		return 0;
	}
	// cerr<<"vis:";rep(i,1,n)cerr<<vis[i];cerr<<'\n';
	rep(i,1,n){
		nw[i]=bs[i];
		rep(j,1,n)if(!vis[j])nw[i][j]=0;
	}
	// cerr<<"nr:\n";
	// rep(i,1,n){
	// 	if(!vis[i])continue;
	// 	cerr<<i<<":";rep(j,1,n)cerr<<nr[i][j];cerr<<'\n';
	// }
	// cerr<<"nw:\n";
	// rep(i,1,n){
	// 	cerr<<i<<":";rep(j,1,n)cerr<<nw[i][j];cerr<<'\n';
	// }
	// cerr<<"bs:\n";
	// rep(i,1,n){
	// 	cerr<<i<<":";rep(j,1,n)cerr<<bs[i][j];cerr<<'\n';
	// }
	for(int i=1;i<=n;++i){
		if(vis[i])continue;
		int id=-1;
		for(int j=1;j<=n;++j)
			if(!used[j]&&bs[j][i]&&(!~id||sz[j]<sz[id]))id=j;
		used[id]=1;
		for(int j=1;j<=n;++j)
			if(vis[j]&&nr[j]==nw[id]){e[i].pb(j),e[j].pb(i);break;}
	}
	rep(u,1,n)for(int v:e[u])
		if(u<v)printf("%d %d\n",u,v);
	return 0;
}
/*
12
7 1 2 3 4 5 6 7
8 1 2 7 8 9 10 11 12
6 1 2 3 4 5 6
4 2 3 4 5
4 1 2 3 6
7 1 2 3 6 7 8 9
5 7 8 10 11 12
4 2 3 4 5
7 1 7 8 9 10 11 12
5 7 8 10 11 12
5 7 8 10 11 12
4 1 7 8 9

*/