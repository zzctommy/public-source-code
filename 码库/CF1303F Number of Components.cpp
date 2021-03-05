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
const int N=305;
const int M=2000005;
int n,m,q,F[N*N],a[N][N],tot,ans[M],tag[M],siz[N*N],stk[N*N],top;
bool chg[M];
struct edge{
	int x,y,c,l,r;
}e[N*N*2+M*4];
inline int anc(int x){while(x!=F[x])x=F[x];return x;}
inline void merge(int x,int y){
	x=anc(x),y=anc(y);
	if(x==y)return;
	if(siz[x]>siz[y])x^=y^=x^=y;
	F[x]=y,siz[y]+=siz[x],stk[++top]=x;
}
inline void undo(){
	int x=stk[top--];
	siz[F[x]]-=siz[x],F[x]=x;
}
map<pair<int,int>,int>mp;
inline int id(int x,int y){return (x-1)*m+y;}
inline bool cmp(const edge&a,const edge&b){
	return a.r>b.r;
}
signed main(){
	n=read(),m=read(),q=read();
	rep(i,1,n)rep(j,1,m){
		if(i<n){
			mp[mkp(id(i+1,j),id(i,j))]=mp[mkp(id(i,j),id(i+1,j))]=++tot;
			e[tot].l=0,e[tot].r=q+1,e[tot].x=id(i+1,j),e[tot].y=id(i,j),e[tot].c=0;
		}
		if(j<m){
			mp[mkp(id(i,j+1),id(i,j))]=mp[mkp(id(i,j),id(i,j+1))]=++tot;
			e[tot].l=0,e[tot].r=q+1,e[tot].x=id(i,j+1),e[tot].y=id(i,j),e[tot].c=0;
		}
	}
	rep(i,1,q){
		static int lst=0;
		int x=read(),y=read(),c=read();
		if(c!=lst)chg[i]=1,lst=c;
		if(a[x][y]==c)continue;
		if(x>1&&a[x-1][y]==a[x][y]){
			int j=mp[mkp(id(x-1,y),id(x,y))]; e[j].r=i;
		}
		if(y>1&&a[x][y-1]==a[x][y]){
			int j=mp[mkp(id(x,y-1),id(x,y))]; e[j].r=i;
		}
		if(x<n&&a[x+1][y]==a[x][y]){
			int j=mp[mkp(id(x,y),id(x+1,y))]; e[j].r=i;
		}
		if(y<m&&a[x][y+1]==a[x][y]){
			int j=mp[mkp(id(x,y),id(x,y+1))]; e[j].r=i;
		}
		a[x][y]=c;
		if(x>1&&a[x-1][y]==c){
			mp[mkp(id(x-1,y),id(x,y))]=++tot;
			e[tot].l=i,e[tot].r=q+1,e[tot].x=id(x-1,y),e[tot].y=id(x,y),e[tot].c=c;
		}
		if(y>1&&a[x][y-1]==c){
			mp[mkp(id(x,y-1),id(x,y))]=++tot;
			e[tot].l=i,e[tot].r=q+1,e[tot].x=id(x,y-1),e[tot].y=id(x,y),e[tot].c=c;
		}
		if(x<n&&a[x+1][y]==c){
			mp[mkp(id(x,y),id(x+1,y))]=++tot;
			e[tot].l=i,e[tot].r=q+1,e[tot].x=id(x+1,y),e[tot].y=id(x,y),e[tot].c=c;
		}
		if(y<m&&a[x][y+1]==c){
			mp[mkp(id(x,y),id(x,y+1))]=++tot;
			e[tot].l=i,e[tot].r=q+1,e[tot].x=id(x,y+1),e[tot].y=id(x,y),e[tot].c=c;
		}
	}
	int j=1;
	rep(i,1,n*m)F[i]=i,siz[i]=1;
	for(int i=0,now=0,lst=1;i<=q;++i){
		if(i==1)now=1;
		now+=tag[i];
		while(j<=tot&&e[j].l==i){
			int x=e[j].x,y=e[j].y;
			if(anc(x)!=anc(y))merge(x,y),--now;
			++j;
		}
		if(chg[i+1]){
			while(top)undo();
			sort(e+lst,e+j,cmp);
			for(int k=lst;k<j;++k){
				int x=e[k].x,y=e[k].y;
				if(anc(x)!=anc(y)){
					merge(x,y),++tag[e[k].r];
				}
			}
			while(top)undo();
			lst=j;
		}
		ans[i]=now;
	}
	rep(i,1,q)printf("%d\n",ans[i]);
}