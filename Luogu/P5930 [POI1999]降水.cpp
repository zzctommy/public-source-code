#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 105
int n,m,a[N][N],now,ans,H;
int F[N*N],siz[N*N];
#define id(x,y) ((x-1)*m+y)
vector<pair<int,int> >v[10005];
#define pb push_back
#define x first
#define y second
#define mkp make_pair
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(siz[x]<siz[y])F[x]=y,siz[y]+=siz[x];
	else F[y]=x,siz[x]+=siz[y];
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			v[a[i][j]=read()].pb(mkp(i,j)),H=max(H,a[i][j]);
	for(int i=1,mx=n*m;i<=mx;++i)F[i]=i,siz[i]=1;
	for(int i=1;i<=H;++i){
		for(pair<int,int> j:v[i]){
			int x=j.x,y=j.y;++now;
			if(x==1||x==n||y==1||y==m)merge(id(x,y),0);
			if(y>1&&a[x][y-1]<=a[x][y])merge(id(x,y),id(x,y-1));
			if(x>1&&a[x-1][y]<=a[x][y])merge(id(x,y),id(x-1,y));
			if(y<m&&a[x][y+1]<=a[x][y])merge(id(x,y),id(x,y+1));
			if(x<n&&a[x+1][y]<=a[x][y])merge(id(x+1,y),id(x,y));
		}
		ans+=now-siz[find(0)];
	}
	printf("%d\n",ans);
	return 0;
}