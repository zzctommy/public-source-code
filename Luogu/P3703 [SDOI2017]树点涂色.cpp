#include<bits/stdc++.h>
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100005;
int n,m;
int num_edge,head[N];
struct edge{
    int nxt,to;
}e[N<<1];
void addedge(int fr,int to){
    ++num_edge;
    e[num_edge].nxt=head[fr];
    e[num_edge].to=to;
    head[fr]=num_edge;
}
namespace Tree{

int rev[N],dfn[N],tmr,siz[N],fa[N],top[N],son[N],dep[N],ed[N];
const int T=N<<2;
void dfs1(int u,int ft){
    siz[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==ft)continue;
        fa[v]=u,dep[v]=dep[u]+1,dfs1(v,u),siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
void dfs2(int u,int tp){
    top[u]=tp,rev[dfn[u]=++tmr]=u;
    if(son[u])dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
    ed[u]=tmr;
}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}
#define lc (p<<1)
#define rc (p<<1|1)
int tag[T],val[T];
void pushup(int p){val[p]=std::max(val[lc],val[rc]);}
void build(int l,int r,int p=1){
    if(l==r)return val[p]=dep[rev[l]],void();
    int mid=(l+r)>>1;
    build(l,mid,lc),build(mid+1,r,rc);
    pushup(p);
}
void pushdown(int p){
    if(tag[p]){
        val[lc]+=tag[p];
        val[rc]+=tag[p];
        tag[lc]+=tag[p];
        tag[rc]+=tag[p];
        tag[p]=0;
    }
}
void update(int ql,int qr,int k,int l=1,int r=n,int p=1){
    if(ql<=l&&r<=qr)return val[p]+=k,tag[p]+=k,void();
    int mid=(l+r)>>1;
    pushdown(p);
    if(ql<=mid)update(ql,qr,k,l,mid,lc);
    if(mid<qr)update(ql,qr,k,mid+1,r,rc);
    pushup(p);
}
int query(int ql,int qr,int l=1,int r=n,int p=1){
    if(ql<=l&&r<=qr)return val[p];
    pushdown(p);
    int mid=(l+r)>>1,res=0;
    if(ql<=mid)res=std::max(res,query(ql,qr,l,mid,lc));
    if(mid<qr)res=std::max(res,query(ql,qr,mid+1,r,rc));
    return res;
}

}
namespace LCT{

int fa[N],ch[N][2];

bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void rotate(int x){
    int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
    if(nroot(y))ch[z][ch[z][1]==y]=x;
    ch[x][!k]=y,ch[y][k]=w;
    if(w)fa[w]=y;fa[y]=x,fa[x]=z;
}
void splay(int x){
    int y=x,z;
    while(nroot(x)){
        y=fa[x],z=fa[y];
        if(nroot(y))rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
        rotate(x);
    }
}
int findroot(int x){
    while(ch[x][0])x=ch[x][0];
    return x;
}
void access(int x){
    for(int y=0,s;x;x=fa[y=x]){
        splay(x);
        if(ch[x][1])s=findroot(ch[x][1]),Tree::update(Tree::dfn[s],Tree::ed[s],1);
        if(y)s=findroot(y),Tree::update(Tree::dfn[s],Tree::ed[s],-1);
        ch[x][1]=y;
    }
}

}
signed main(){
    n=read(),m=read();
    for(int i=1;i<n;++i){
        int x=read(),y=read();
        addedge(x,y),addedge(y,x);
    }
    Tree::dep[1]=1,Tree::dfs1(1,0),Tree::dfs2(1,1),Tree::build(1,n);
    for(int i=1;i<=n;++i)LCT::fa[i]=Tree::fa[i];
    while(m--){
        int op=read(),x=read(),y,lca;
        if(op==1)LCT::access(x);
        else if(op==2){
            y=read(),lca=Tree::LCA(x,y);
            printf("%d\n",Tree::query(Tree::dfn[x],Tree::dfn[x])+Tree::query(Tree::dfn[y],Tree::dfn[y])-2*Tree::query(Tree::dfn[lca],Tree::dfn[lca])+1);
        }
        else printf("%d\n",Tree::query(Tree::dfn[x],Tree::ed[x]));
    }
    return 0;
}