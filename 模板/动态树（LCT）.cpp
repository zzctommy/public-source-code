struct Link_Cut_Tree{

static const int O=N+5;
int ch[O][2],fa[O],sum[O],val[O],id[O],tag[O];
bool fl[O];
Link_Cut_Tree(){
    memset(ch,0,sizeof(ch));
    memset(fa,0,sizeof(fa));
    memset(val,0,sizeof(val));
    memset(sum,0,sizeof(sum));
    memset(id,0,sizeof(id));
    memset(fl,0,sizeof(fl));
    memset(tag,0,sizeof(tag));
}
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){
    sum[x]=sum[ch[x][0]]+val[x]+sum[ch[x][1]];
    id[x]=x;
    if(ch[x][0]&&val[id[ch[x][0]]]>val[id[x]])id[x]=id[ch[x][0]];
    if(ch[x][1]&&val[id[ch[x][1]]]>val[id[x]])id[x]=id[ch[x][1]];
}
void addtag(int x,int d){
    val[x]+=d,tag[x]+=d,sum[x]+=d;
}
void pushdown(int x){
    if(fl[x]){
        fl[x]^=1,fl[ch[x][0]]^=1,fl[ch[x][1]]^=1;
        swap(ch[x][0],ch[x][1]);
    }
    if(tag[x]){
        if(ch[x][0])addtag(ch[x][0],tag[x]);
        if(ch[x][1])addtag(ch[x][1],tag[x]);
        tag[x]=0;
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
void makeroot(int x){
    access(x),splay(x),fl[x]^=1;
}
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
    }else split(x,y),fa[x]=y;
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
void add(int x,int y,int d){split(x,y),addtag(y,d);}
};