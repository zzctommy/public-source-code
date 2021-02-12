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
const int N=600005;
int ch[N][26],n,cnt[N],tot,ans,id;
int merge(int x,int y){
	if(!x||!y)return x|y;
	int u=++tot;
	rep(i,0,25)ch[u][i]=merge(ch[x][i],ch[y][i]);
	return u;
}
void dfs(int u,int dep){
	if(!u)return;
	tot=n;int x=++tot;
	rep(i,0,25)x=merge(x,ch[u][i]);
	cnt[dep]+=tot-n-1;
	rep(i,0,25)dfs(ch[u][i],dep+1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,2,n){
		char c;int x,y;
		cin>>x>>y>>c,ch[x][c-'a']=y;
	}
	dfs(1,1),ans=N;
	rep(i,1,n)if(ckmin(ans,n-cnt[i]))id=i;
	cout<<ans<<'\n'<<id<<'\n';
}