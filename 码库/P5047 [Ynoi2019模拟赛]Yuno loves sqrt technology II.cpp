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
const int N=100005;
const int S=320;
const int B=N/S+5;
int n,m,num,a[N],pre[N],suf[N],L[B],R[B],bel[N];
LL sp[N],ss[N],res[N<<1];
LL ans[N];
int lsh[N],len;
int tr[N];
int tol,tor;
struct QUE{
	int l,r,id;
	inline bool operator< (const QUE&t)const{return bel[l]!=bel[t.l]?l<t.l:bel[l]&1?r<t.r:r>t.r;}
}q[N];
struct ASK{
	int pos,l,r,id;
	inline bool operator < (const ASK&t)const{return pos<t.pos;}
}ql[N],qr[N];
namespace BLOCK1{
int sum[N],tag[B];
void update(int x,int d){
	for(int i=1;i<bel[x];++i)tag[i]+=d;
	for(int i=L[bel[x]];i<=x;++i)sum[i]+=d;
}
int query(int x){
	return sum[x]+tag[bel[x]];
}
}
namespace BLOCK2{
int sum[N],tag[B];
void update(int x,int d){
	for(int i=num;i>bel[x];--i)tag[i]+=d;
	for(int i=x;i<=R[bel[x]];++i)sum[i]+=d;
}
int query(int x){
	return sum[x]+tag[bel[x]];
}
}

signed main(){
	n=read(),m=read(),num=(n-1)/S+1;
	rep(i,1,num)L[i]=R[i-1]+1,R[i]=i*S;R[num]=n;
	rep(i,1,num)rep(j,L[i],R[i])bel[j]=i;
	rep(i,1,n)a[i]=lsh[i]=read();
	sort(lsh+1,lsh+n+1),len=unique(lsh+1,lsh+n+1)-lsh-1;
	rep(i,1,n)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	rep(i,1,n){
		int res=0;
		for(int j=a[i]+1;j<=n;j+=j&-j)res+=tr[j];
		pre[i]=res;
		for(int j=a[i];j>0;j-=j&-j)++tr[j];
	}
	fill(tr,tr+n+1,0);
	per(i,n,1){
		int res=0;
		for(int j=a[i]-1;j>0;j-=j&-j)res+=tr[j];
		suf[i]=res;
		for(int j=a[i];j<=n;j+=j&-j)++tr[j];
	}
	rep(i,1,m)q[i].id=i,q[i].l=read(),q[i].r=read();
	sort(q+1,q+m+1);
	for(int i=1,l=1,r=0;i<=m;++i){
		if(l>q[i].l)ql[++tol].pos=r+1,ql[tol].l=q[i].l,ql[tol].r=l-1,ql[tol].id=q[i].id<<1,l=q[i].l;
		if(r<q[i].r)qr[++tor].pos=l-1,qr[tor].l=r+1,qr[tor].r=q[i].r,qr[tor].id=q[i].id<<1|1,r=q[i].r;
		if(l<q[i].l)ql[++tol].pos=r+1,ql[tol].l=l,ql[tol].r=q[i].l-1,ql[tol].id=q[i].id<<1,l=q[i].l;
		if(r>q[i].r)qr[++tor].pos=l-1,qr[tor].l=q[i].r+1,qr[tor].r=r,qr[tor].id=q[i].id<<1|1,r=q[i].r;
	}
	sort(ql+1,ql+tol+1),sort(qr+1,qr+tor+1);
	for(int i=1,j=1;i<=n;++i){
		while(j<=tor&&qr[j].pos<i)++j;
		BLOCK1::update(a[i],1),sp[i]=sp[i-1]+pre[i];
		for(;j<=tor&&qr[j].pos==i;++j){
			for(int k=qr[j].l;k<=qr[j].r;++k)
				res[qr[j].id]+=BLOCK1::query(a[k]+1);
		}
	}
	for(int i=n,j=tol;i>=1;--i){
		while(j>=1&&ql[j].pos>i)--j;
		BLOCK2::update(a[i],1),ss[i]=ss[i+1]+suf[i];
		for(;j>=1&&ql[j].pos==i;--j){
			for(int k=ql[j].l;k<=ql[j].r;++k)
				res[ql[j].id]+=BLOCK2::query(a[k]-1);
		}
	}
	LL now=0;
	for(int i=1,l=1,r=0;i<=m;++i){
		if(l>q[i].l)now+=ss[q[i].l]-ss[l]-res[q[i].id<<1],l=q[i].l;
		if(r<q[i].r)now+=sp[q[i].r]-sp[r]-res[q[i].id<<1|1],r=q[i].r;
		if(l<q[i].l)now-=ss[l]-ss[q[i].l]-res[q[i].id<<1],l=q[i].l;
		if(r>q[i].r)now-=sp[r]-sp[q[i].r]-res[q[i].id<<1|1],r=q[i].r;
		ans[q[i].id]=now;
	}
	rep(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}