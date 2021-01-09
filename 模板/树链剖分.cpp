template<int N>
struct Tree{

static const int O=N+5;

Tree(){ecnt=0;memset(head,0,sizeof(head));}

int ecnt,head[O];
struct edge{int nxt,to;}e[O<<1];
int siz[O],fa[O],top[O],son[O],dep[O],rev[O],dfn[O],tmr;
void addedge(int fr,int to){++ecnt,e[ecnt].nxt=head[fr],e[ecnt].to=to,head[fr]=ecnt;}
void dfs1(int u,int ft){
    siz[u]=1,dep[u]=dep[ft]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==ft)continue;
        fa[v]=u,dfs1(v,u),siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
}
void dfs2(int u,int tp){
    rev[dfn[u]=++tmr]=u,top[u]=tp;
    if(son[u])dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
}
void init(){dfs1(1,0),dfs2(1,1);}
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

};