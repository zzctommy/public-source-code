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
inline char rdopt(){
	char ch=getchar();
	while(ch!='A'&&ch!='Q'&&ch!='X')ch=getchar();
	return ch;
}
const int N=100005;
int n,m,F[N],XOR;
int fa[N],ch[N][2],siz[N],siv[N];
bool fl[N];
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+siv[x]+1;
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;fa[y]=x,fa[x]=z;
	pushup(y);
}
void pushdown(int x){
	if(fl[x]){
		fl[x]=0,fl[ch[x][0]]^=1,fl[ch[x][1]]^=1;
		swap(ch[x][0],ch[x][1]);
	}
}
void splay(int x){
	static int stk[N],top;
	int y=x,z;stk[top=1]=y;
	while(nroot(y))stk[++top]=y=fa[y];
	while(top)pushdown(stk[top--]);
	while(nroot(x)){
		y=fa[x],z=fa[y];
		if(nroot(y))rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
		rotate(x);
	}
	pushup(x);
}
void access(int x){
	for(int y=0;x;x=fa[y=x])
		splay(x),siv[x]+=siz[ch[x][1]]-siz[y],ch[x][1]=y,pushup(x);
}
void makeroot(int x){access(x),splay(x),fl[x]^=1;}
void split(int x,int y){makeroot(x),access(y),splay(y);}
void link(int x,int y){split(x,y),fa[x]=y,siv[y]+=siz[x],pushup(y);}
int getrt(int x){
	int res=N,lsum=0,rsum=0,aim=siz[x]>>1;
	while(x){
		pushdown(x);
		int sl=siz[ch[x][0]],sr=siz[ch[x][1]];
		if(sl+lsum<=aim&&sr+rsum<=aim)ckmin(res,x);
		if(sl+lsum<=sr+rsum)lsum+=sl+siv[x]+1,x=ch[x][1];
		else rsum+=sr+siv[x]+1,x=ch[x][0];
	}
	return splay(res),res;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)F[i]=i,XOR^=i,siz[i]=1;
	while(m--){
		char opt=rdopt();int x,y;
		if(opt=='A'){
			y=read(),x=read();int z,rx=find(x),ry=find(y);
			link(x,y),split(rx,ry),z=getrt(ry),XOR^=rx^ry^z,F[rx]=F[ry]=F[z]=z;
		}else if(opt=='Q')x=read(),printf("%d\n",find(x));
		else printf("%d\n",XOR);
	}
	return 0;
}