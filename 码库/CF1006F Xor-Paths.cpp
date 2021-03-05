#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N=25;
int n,m,b[N][N],tot;
LL k,ans,a[N][N];
map<LL,int>mp[N*N];
void dfs1(int x,int y,LL v){
	if(x==n&&y==m)return ans+=v==k,void();
	if(x<n)dfs1(x+1,y,v^a[x+1][y]);
	if(y<m)dfs1(x,y+1,v^a[x][y+1]);
}
void dfs2(int x,int y,LL v){
	if(b[x][y])return mp[b[x][y]][v]++,void();
	if(x<n)dfs2(x+1,y,v^a[x+1][y]);
	if(y<m)dfs2(x,y+1,v^a[x][y+1]);
}
void dfs3(int x,int y,LL v){
	if(b[x][y])return mp[b[x][y]][v]++,void();
	if(x>1)dfs3(x-1,y,v^a[x-1][y]);
	if(y>1)dfs3(x,y-1,v^a[x][y-1]);
}
signed main(){
	cin>>n>>m>>k;
	rep(i,1,n)rep(j,1,m)cin>>a[i][j];
	if(n<=6&&m<=6){
		dfs1(1,1,a[1][1]);
		cout<<ans;
		return 0;
	}
	rep(i,1,n)rep(j,1,m){
		if(i+j-2==(n+m-2)>>1){
			b[i][j]=++tot;
			if(j<m&&!b[i][j+1])b[i][j+1]=++tot;
			if(i<n&&!b[i+1][j])b[i+1][j]=++tot;
		}
	}
	dfs2(1,1,a[1][1]),dfs3(n,m,a[n][m]);
	rep(i,1,n)rep(j,1,m){
		if(i<n&&b[i][j]&&b[i+1][j]){
			for(auto t:mp[b[i][j]])ans+=1ll*t.se*mp[b[i+1][j]][k^t.fi];
		}
		if(j<m&&b[i][j]&&b[i][j+1]){
			for(auto t:mp[b[i][j]])ans+=1ll*t.se*mp[b[i][j+1]][k^t.fi];
		}
	}
	cout<<ans<<'\n';
}
/*
7 7 6
1 1 4 5 6 1 4
2 3 5 6 8 9 0
1 6 3 4 7 8 9
2 4 3 6 5 7 1
2 4 3 6 7 3 9
1 4 2 8 4 6 9
1 5 3 4 7 5 3

*/