#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}

template<int N>
struct Link_Cut_Tree{

static const int O=N+5;
int ch[O][2],fa[O],sum[O],val[O],id[O];
bool fl[O];
Link_Cut_Tree(){
	memset(ch,0,sizeof(ch));
	memset(fa,0,sizeof(fa));
	memset(val,0,sizeof(val));
	memset(sum,0,sizeof(sum));
	memset(id,0,sizeof(id));
	memset(fl,0,sizeof(fl));
}
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){
	sum[x]=sum[ch[x][0]]+val[x]+sum[ch[x][1]];
	id[x]=x;
	if(ch[x][0]&&val[id[ch[x][0]]]>val[id[x]])id[x]=id[ch[x][0]];
	if(ch[x][1]&&val[id[ch[x][1]]]>val[id[x]])id[x]=id[ch[x][1]];
}
void pushdown(int x){
	if(fl[x]){
		fl[x]^=1,fl[ch[x][0]]^=1,fl[ch[x][1]]^=1;
		swap(ch[x][0],ch[x][1]);
	}
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;
	fa[y]=x,fa[x]=z;
	pushup(y);
}
void splay(int x){
	static int stk[O],top;
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
		splay(x),ch[x][1]=y,pushup(x);
}
void makeroot(int x){access(x),splay(x),fl[x]^=1;}
int findroot(int x){
	access(x),splay(x);
	while(ch[x][0])pushdown(x),x=ch[x][0];
	return splay(x),x;
}
void split(int x,int y){
	makeroot(x),access(y),splay(y);
}
void link(int x,int y,int op=0){
	if(op){
		makeroot(x);
		if(findroot(y)!=x)splay(y),fa[x]=y;
	}else makeroot(x),fa[x]=y;
}
void cut(int x,int y,int op=0){
	if(op){
		makeroot(x);
		if(findroot(y)==x&&fa[y]==x&&!ch[y][0])
			fa[y]=ch[x][1]=0;
	}else split(x,y),fa[x]=ch[y][0]=0,pushup(y);
}
int ask_sum(int x,int y){return split(x,y),sum[y];}
pair<int,int>ask_max(int x,int y){return split(x,y),mkp(val[id[y]],id[y]);}

};

Link_Cut_Tree<200000>lct;
map<pair<int,int>,int>H;
const int N=100005;
int n,m,q,ans[N];
int F[N];
int broken[N];
struct edge {
	int u,v,d;
}a[N];
struct node {
	int opt,x,y;
}qu[N];
int find(int x) {
	return F[x]==x?x:F[x]=find(F[x]);
}
bool cmp(const edge &a,const edge &b) {
	return a.d<b.d;
}
signed main() {
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;++i) {
		a[i].u=read(),a[i].v=read(),a[i].d=read(),F[i]=i;
		if(a[i].u>a[i].v)swap(a[i].u,a[i].v);
	}
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;++i)H[mkp(a[i].u,a[i].v)]=i;
	for(int i=1;i<=q;++i) {
		qu[i].opt=read(),qu[i].x=read(),qu[i].y=read();
		if(qu[i].x>qu[i].y)swap(qu[i].x,qu[i].y);
		if(qu[i].opt==2)broken[H[mkp(qu[i].x,qu[i].y)]]=1;
	}
	for(int i=n+1;i<=n+m;++i)lct.val[i]=a[i-n].d;
	for(int i=1;i<=m;++i) {
		if(broken[i])continue;
		int u=a[i].u,v=a[i].v;
		int fx=find(u),fy=find(v);
		if(fx!=fy)F[fx]=fy,lct.link(u,i+n),lct.link(i+n,v);
	}
	for(int i=q;i;--i) {
		int x=qu[i].x,y=qu[i].y;
		if(qu[i].opt==1)ans[i]=lct.ask_max(x,y).fi;
		else {
			lct.split(x,y);int ID=H[mkp(x,y)],tmp=lct.id[y];
			if(lct.val[tmp]>a[ID].d) {
				lct.cut(a[tmp-n].u,tmp),lct.cut(tmp,a[tmp-n].v);
				lct.link(x,ID+n),lct.link(ID+n,y);
			}
		}
	}
	for(int i=1;i<=q;++i)if(qu[i].opt==1)printf("%d\n",ans[i]);
	return 0;
} 