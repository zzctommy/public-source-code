namespace goat{
LL val[N];
int ch[N][2],siz[N],tot,rt;
int stk[N],top;
const db alpha=0.83;
void clear(){tot=rt=0;}
int newnode(LL x){
    val[++tot]=x,siz[tot]=1;
    ch[tot][0]=ch[tot][1]=0;
    return tot;
}
void pushup(int x){
    siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
}
void dfs(int u){
    if(!u)return;
    dfs(ch[u][0]),stk[++top]=u,dfs(ch[u][1]);
    ch[u][0]=ch[u][1]=0;
}
int build(int l,int r){
    if(l>r)return 0;
    if(l==r)return siz[stk[l]]=1,stk[l];
    int mid=(l+r)>>1,u=stk[mid];
    ch[u][0]=build(l,mid-1),ch[u][1]=build(mid+1,r);
    return pushup(u),u;
}
void rebuild(int&x){
    top=0,dfs(x),x=build(1,top);
}
void ins(int&x,int nd){
    if(!x)return x=nd,void();
    if(val[nd]<=val[x])ins(ch[x][0],nd);
    else ins(ch[x][1],nd);
    pushup(x);
    if(siz[ch[x][0]]>siz[x]*alpha||siz[ch[x][1]]>siz[x]*alpha)rebuild(x);
}
void insert(LL x){ins(rt,newnode(x));}
LL findkth(int u,int k){
    while("fyy yyds"){
        if(siz[ch[u][1]]+1==k)return val[u];
        if(k>siz[ch[u][1]]+1)k-=siz[ch[u][1]]+1,u=ch[u][0];
        else u=ch[u][1];
    }
}
LL kth(int x){return findkth(rt,x);}
int size(){return siz[rt];}
}