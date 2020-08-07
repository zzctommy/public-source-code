#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=50010;
const int M=200010;
const int T=N+M;
const int inf=2e9+10;
int n,m,ans=inf;
int cnt;
struct edge {int u,v,d;}e[M];
bool cmp(const edge &a,const edge &b) {return a.d<b.d;}
int ch[T][2],fa[T],val[T],id[T],rev[T],st[T];
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x) {
    id[x]=x;
    if(ch[x][0]&&val[id[ch[x][0]]]<val[id[x]])id[x]=id[ch[x][0]];
    if(ch[x][1]&&val[id[ch[x][1]]]<val[id[x]])id[x]=id[ch[x][1]];
}
void pushdown(int x) {
    if(!rev[x])return;
    swap(ch[x][0],ch[x][1]),rev[x]^=1,rev[ch[x][0]]^=1,rev[ch[x][1]]^=1;
}
void rotate(int x) {
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;fa[y]=x,fa[x]=z;
	pushup(y);
}
void splay(int x) {
	int y=x,z,top=0;st[++top]=x;
	while(nroot(y))st[++top]=y=fa[y];
	while(top)pushdown(st[top--]);
	while(nroot(x)) {
		y=fa[x],z=fa[y];
		if(nroot(y))rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
		rotate(x);
	}
	pushup(x);
}
void access(int x) {
    for(int y=0;x;x=fa[y=x])
        splay(x),ch[x][1]=y,pushup(x);
}
void makeroot(int x){access(x),splay(x),rev[x]^=1;}
void split(int x,int y){makeroot(x),access(y),splay(y);}
void link(int x,int y){makeroot(x),fa[x]=y;}
void cut(int x,int y){split(x,y),fa[x]=ch[y][0]=0,pushup(y);}
multiset<int>s;
int F[N];
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
signed main() {
    n=rd(),m=rd();
    for(int i=1;i<=m;++i)e[i].u=rd(),e[i].v=rd(),e[i].d=rd();
    sort(e+1,e+m+1,cmp);
    for(int i=0;i<=n;++i)val[i]=inf,F[i]=i;
    for(int i=1;i<=m;++i)val[i+n]=e[i].d;
    for(int i=1;i<=m;++i) {
        int u=e[i].u,v=e[i].v;
        if(u==v)continue;
        s.insert(e[i].d);
        if(find(u)!=find(v))link(u,i+n),link(i+n,v),++cnt,F[find(u)]=find(v);
        else {
            split(u,v);int t=id[v],k=val[t];
            cut(e[t-n].u,t),cut(e[t-n].v,t),s.erase(s.find(k));
            link(u,i+n),link(i+n,v);
        }
        if(cnt==n-1)ans=min(ans,e[i].d-*s.begin());
    }
    printf("%d\n",ans);
    return 0;
}