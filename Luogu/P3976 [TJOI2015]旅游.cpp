#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=50009;
const int inf=1000000007;
int n;
int mxv[N],miv[N],val[N],tag[N],lvl[N],rvl[N];
int fa[N],ch[N][2],fl[N],stk[N];
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x) {
	#define lc ch[x][0]
	#define rc ch[x][1]
	miv[x]=min(val[x],min(miv[lc],miv[rc]));
	mxv[x]=max(val[x],max(mxv[lc],mxv[rc]));
	lvl[x]=max(max(lvl[lc],lvl[rc]),max(mxv[lc],val[x])-min(miv[rc],val[x]));
	rvl[x]=max(max(rvl[lc],rvl[rc]),max(mxv[rc],val[x])-min(miv[lc],val[x]));
	#undef lc
	#undef rc
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	fa[w]=y,fa[y]=x,fa[x]=z;
	pushup(y);
}
void addtag(int x,int d) {val[x]+=d,mxv[x]+=d,miv[x]+=d,tag[x]+=d;}
void rev(int x){swap(lvl[x],rvl[x]),swap(ch[x][0],ch[x][1]),fl[x]^=1;}
void pushdown(int x) {
	if(fl[x]) {
		if(ch[x][0])rev(ch[x][0]);
		if(ch[x][1])rev(ch[x][1]);
		fl[x]=0;
	}
	if(tag[x]) {
		if(ch[x][0])addtag(ch[x][0],tag[x]);
		if(ch[x][1])addtag(ch[x][1],tag[x]);
		tag[x]=0;
	}
}
void splay(int x) {
	int y=x,z,top=0;stk[++top]=x;
	while(nroot(y))stk[++top]=y=fa[y];
	while(top)pushdown(stk[top--]);
	while(nroot(x)) {
		y=fa[x],z=fa[y];
		if(nroot(y))rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
		rotate(x);
	}
	pushup(x);
}
void access(int x){
	for(int y=0;x;x=fa[y=x])
		splay(x),ch[x][1]=y,pushup(x);
}
void makeroot(int x){access(x),splay(x),rev(x);}
void split(int x,int y){makeroot(x),access(y),splay(y);}
void link(int x,int y){makeroot(x),fa[x]=y;}
void print(int x) {
	if(!x)return;
	pushdown(x);
	print(ch[x][0]),print(ch[x][1]);
}
signed main() {
	miv[0]=inf,mxv[0]=-inf;
	n=rd();
	for(int i=1;i<=n;++i)val[i]=miv[i]=mxv[i]=rd();		
	for(int i=1;i<n;++i)link(rd(),rd());
	for(int q=rd();q;--q) {
		int x=rd(),y=rd(),z=rd();
		split(x,y),printf("%d\n",rvl[y]),addtag(y,z);
	}
	return 0;
}