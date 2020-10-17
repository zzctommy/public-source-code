#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
int rdc(){
	char ch=getchar();
	while(ch!='#'&&ch!='.')ch=getchar();
	return ch=='.';
}
const int N=1005;
const int M=N*N;
const int mod=1e9+7;
int n,m,a[N][N],fa[M],cnt,ans=1,val[M];
unordered_map<int,bool>vis;
int id(int x,int y){return (x-1)*m+y;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)fa[fx]=fy,val[fy]=1ll*val[fx]*val[fy]%mod;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n*m;++i)fa[i]=i,val[i]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=rdc();
	for(int i=n;i>=1;--i){
		for(int j=2;j<=m;++j){
			if(!a[i][j])continue;
			if(a[i+1][j])merge(id(i+1,j),id(i,j));
			if(a[i][j-1])merge(id(i,j-1),id(i,j));
			if(a[i][j+1])merge(id(i,j+1),id(i,j));
		}
		vis.clear();
		for(int j=1;j<=m;++j){
			if(!a[i][j])continue;
			if(!vis[find(id(i,j))])vis[find(id(i,j))]=1,++val[find(id(i,j))];
		}
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]&&find(id(i,j))==id(i,j))ans=1ll*ans*val[id(i,j)]%mod;
	return std::cout<<ans<<'\n',0;
}