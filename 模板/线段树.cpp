template<int N,class typ>
struct SegmentTree{

static const int O=N+5;
#define T (O<<2)
typ sum[T],mx[T],tag[T];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){sum[p]=sum[lc]+sum[rc],mx[p]=max(mx[lc],mx[rc]);}
void clear(int p=1,int l=1,int r=N){
    sum[p]=mx[p]=tag[p]=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    clear(lc,l,mid),clear(rc,mid+1,r);
}
void build(typ*a,int p=1,int l=1,int r=N){
    sum[p]=mx[p]=tag[p]=0;
    if(l==r){
        sum[p]=mx[p]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(a,lc,l,mid),build(a,rc,mid+1,r);
    pushup(p);
}
void pushdown(int p,int l,int r){
    if(tag[p]){
        int mid=(l+r)>>1;
        tag[lc]+=tag[p],tag[rc]+=tag[p];
        sum[lc]+=tag[p]*(mid-l+1),sum[rc]+=tag[p]*(r-mid);
        mx[lc]+=tag[p],mx[rc]+=tag[p];
        tag[p]=0;
    }
}
void update(int ql,int qr,typ k,int p=1,int l=1,int r=N){
    if(ql<=l&&r<=qr){
        sum[p]+=k*(r-l+1),mx[p]+=k,tag[p]+=k;
        return;
    }
    pushdown(p,l,r);
    int mid=(l+r)>>1;
    if(ql<=mid)update(ql,qr,k,lc,l,mid);
    if(mid<qr)update(ql,qr,k,rc,mid+1,r);
    pushup(p);
}
typ query_sum(int ql,int qr,int p=1,int l=1,int r=N){
    if(ql<=l&&r<=qr)return sum[p];
    pushdown(p,l,r);
    int mid=(l+r)>>1;
    if(qr<=mid)return query_sum(ql,qr,lc,l,mid);
    if(mid<ql)return query_sum(ql,qr,rc,mid+1,r);
    return query_sum(ql,qr,lc,l,mid)+query_sum(ql,qr,rc,mid+1,r);
}
typ query_max(int ql,int qr,int p=1,int l=1,int r=N){
    if(ql<=l&&r<=qr)return mx[p];
    pushdown(p,l,r);
    int mid=(l+r)>>1;
    if(qr<=mid)return query_max(ql,qr,lc,l,mid);
    if(mid<ql)return query_max(ql,qr,rc,mid+1,r);
    return max(query_max(ql,qr,lc,l,mid),query_max(ql,qr,rc,mid+1,r));
}

#undef lc
#undef rc
#undef T

};