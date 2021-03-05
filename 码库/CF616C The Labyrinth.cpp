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
const int N=1005;
int F[N*N],siz[N*N],n,m;
char mp[N][N];
inline int id(int x,int y){return (x-1)*m+y;}
inline int anc(int x){return x==F[x]?x:F[x]=anc(F[x]);}
void merge(int x,int y){
	x=anc(x),y=anc(y);
	if(x==y)return;
	F[x]=y,siz[y]+=siz[x];
}
signed main(){
	n=read(),m=read();
	rep(i,1,n)scanf("%s",mp[i]+1);
	rep(i,1,n)rep(j,1,m)
		siz[id(i,j)]=mp[i][j]=='.',F[id(i,j)]=id(i,j);
	rep(i,1,n)rep(j,1,m){
		if(mp[i][j]=='*')continue;
		if(i>1&&mp[i-1][j]=='.')merge(id(i,j),id(i-1,j));
		if(i<n&&mp[i+1][j]=='.')merge(id(i,j),id(i+1,j));
		if(j>1&&mp[i][j-1]=='.')merge(id(i,j),id(i,j-1));
		if(j<m&&mp[i][j+1]=='.')merge(id(i,j),id(i,j+1));
	}
	rep(i,1,n){
		rep(j,1,m){
			if(mp[i][j]=='.'){
				putchar('.');
				continue;
			}
			int ans=0;
			vector<int>vc;
			if(i>1)vc.pb(anc(id(i-1,j)));
			if(i<n)vc.pb(anc(id(i+1,j)));
			if(j>1)vc.pb(anc(id(i,j-1)));
			if(j<m)vc.pb(anc(id(i,j+1)));
			sort(vc.begin(),vc.end());
			vc.resize(unique(vc.begin(),vc.end())-vc.begin());
			for(int k:vc)ans+=siz[k];
			putchar('0'+(ans+1)%10);
		}
		puts("");
	}	
}