template<int N,int T>
struct Merge_Segment_Tree{

int ls[T],rs[T],sum[T],mx[T],id[T],tot;

Merge_Segment_Tree(){
    tot=0;
    memset(mx,0,sizeof(mx));
    memset(sum,0,sizeof(sum));
    memset(id,0,sizeof(id));
    memset(ls,0,sizeof(ls));
    memset(rs,0,sizeof(rs));
}

void pushup(int p){
    sum[p]=sum[ls[p]]+sum[rs[p]];
    if(mx[ls[p]]>=mx[rs[p]])mx[p]=mx[ls[p]],id[p]=id[ls[p]];
    else mx[p]=mx[rs[p]],id[p]=id[rs[p]];
}
void update(int&p,int pos,int k,int l=1,int r=N){
    if(!p)p=++tot;
    if(l==r){
        mx[p]+=k,sum[p]+=k,id[p]=pos;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)update(ls[p],pos,k,l,mid);
    else update(rs[p],pos,k,mid+1,r);
    pushup(p);
}
pair<int,int>query_max(int p,int ql,int qr,int l=1,int r=N){
    if(!p)return mkp(0,0);
    if(ql<=l&&r<=qr)return mkp(mx[p],id[p]);
    int mid=(l+r)>>1;pair<int,int>res=mkp(0,0);
    if(ql<=mid)res=max(res,query_max(ls[p],ql,qr,l,mid));
    if(mid<qr)res=max(res,query_max(rs[p],ql,qr,mid+1,r));
    return res;
}
int query_sum(int p,int ql,int qr,int l=1,int r=N){
    if(!p)return 0;
    if(ql<=l&&r<=qr)return sum[p];
    int mid=(l+r)>>1,res=0;
    if(ql<=mid)res+=query_sum(ls[p],ql,qr,l,mid);
    if(mid<qr)res+=query_sum(rs[p],ql,qr,mid+1,r);
    return res;
}
int merge(int x,int y,int l=1,int r=N){
    if(!x||!y)return x|y;
    if(l==r){
        sum[x]+=sum[y];
        mx[x]+=mx[y];
        return x;
    }
    int mid=(l+r)>>1;
    ls[x]=merge(ls[x],ls[y],l,mid);
    rs[x]=merge(rs[x],rs[y],mid+1,r);
    return pushup(x),x;
}

};