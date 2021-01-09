#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef long double db;
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
template<int M>struct Bitset{
typedef unsigned long long ull;
static const ull ULL_MAX=-1,N=(M-1)/64+1;
ull a[N],suf[65],pre[65];
unordered_map<ull,int>mp;
Bitset(){
	rep(i,0,63)mp[1ull<<i]=i;
	pre[0]=0;rep(i,1,64)pre[i]=pre[i-1]<<1|1;
	suf[64]=ULL_MAX;per(i,63,0)suf[i]=suf[i+1]<<1;
	memset(a,0,sizeof(a));
}
void reset(){memset(a,0,sizeof(a));}
void set(int x){a[x>>6]|=1ull<<(x&63);}
void flip(int x){a[x>>6]^=1ull<<(x&63);}
void set(int x,int v){if((a[x>>6]>>(x&63))!=v)a[x>>6]^=1ull<<(x&63);}
int mex(int V=M){
	V=(V-1)/64+1;
	for(int i=0;i<V;++i)if(a[i]^ULL_MAX){
		const ull tmp=~a[i];
		return mp[tmp&-tmp]+(i<<6);
	}
	return M;
}
ull get(int l,int r){
	if(l>r)return 0;
	int bl=l>>6,br=r>>6;
	if(bl==br)return (a[br]&(pre[(r&63)+1]^pre[l&63]))>>(l&63);
	else return ((a[bl]&suf[(br<<6)-l])>>(l-(bl<<6)))|((a[br]&pre[r+1-(br<<6)])<<((br<<6)-l));
}
void print(ull x){
	int d[65];d[0]=0;
	while(x)d[++d[0]]=x&1,x>>=1;
	rep(i,1,d[0])putchar('0'+d[i]);
	rep(i,d[0]+1,64)putchar('0');
}
void out(int V=M){
	int i=0,j=0;
	while(i<V)print(a[j]),i+=64,++j;
	puts("");
}
int query(int b,int V=M){
	static ull p[N];int flg;
	int c1=b&63,c2=b>>6,it=0,res=0;
	rep(i,0,c2)p[i]=ULL_MAX;
	for(flg=1;;){
		flg=0;
		p[0]&=get(it,min(V,it+c1-1)),it+=c1,flg|=p[0]>0;
		if(it>V)return res+flg;
		rep(i,1,c2){
			p[i]&=get(it,min(V,it+63)),it+=64,flg|=p[i]>0;
			if(it>V)return res+flg;
		}
		if(!flg)return res;
		++res;
	}
}
};
const int N=100005;
Bitset<N>Bs,bs[64];
int n,a[N],m,ans[N],S,qm,cnt[N],V;
struct preque{
	int l,r,b,id;
	inline bool operator < (const preque&t)const{return b<t.b;}
}prq[N];
struct que{
	int l,r,b,id;
	inline bool operator < (const que&t)const{return l/S!=t.l/S?l<t.l:(l/S)&1?r<t.r:r>t.r;}
}q[N];
void add1(int x,int b){
	int v=a[x]/b,t=a[x]-v*b;
	if(!cnt[a[x]]++)bs[t].flip(v);
}
void pop1(int x,int b){
	int v=a[x]/b,t=a[x]-v*b;
	if(!--cnt[a[x]])bs[t].flip(v);
}
int query1(int b){
	int res=0;
	rep(i,0,b-1)ckmax(res,bs[i].mex(V));
	return res;
}
void solve1(int ll,int rr,int b){
	if(ll>rr)return;
	qm=0;
	rep(i,ll,rr)q[++qm].l=prq[i].l,q[qm].r=prq[i].r,q[qm].b=prq[i].b,q[qm].id=prq[i].id;
	S=n/sqrt(qm)+1,sort(q+1,q+qm+1);
	int l=1,r=0;
	for(int i=1;i<=qm;++i){
		while(l>q[i].l)add1(--l,b);
		while(r<q[i].r)add1(++r,b);
		while(l<q[i].l)pop1(l++,b);
		while(r>q[i].r)pop1(r--,b);
		ans[q[i].id]=query1(b);
	}
	while(l<=r)pop1(l++,b);
}
void add2(int x){if(!cnt[a[x]]++)Bs.flip(a[x]);}
void pop2(int x){if(!--cnt[a[x]])Bs.flip(a[x]);}
void solve2(int ll,int rr){
	if(ll>rr)return;
	qm=0;
	rep(i,ll,rr)q[++qm].l=prq[i].l,q[qm].r=prq[i].r,q[qm].b=prq[i].b,q[qm].id=prq[i].id;
	S=n/sqrt(qm)+1,sort(q+1,q+qm+1);
	for(int i=1,l=1,r=0;i<=qm;++i){
		while(l>q[i].l)add2(--l);
		while(r<q[i].r)add2(++r);
		while(l<q[i].l)pop2(l++);
		while(r>q[i].r)pop2(r--);
		ans[q[i].id]=Bs.query(q[i].b,V);
	}
}
signed main(){
	clock_t st=clock(),ed;
	n=read();rep(i,1,n)ckmax(V,a[i]=read());
	m=read();rep(i,1,m)prq[i].l=read(),prq[i].r=read(),prq[i].b=read(),prq[i].id=i;
	sort(prq+1,prq+m+1);
	int it=1;
	for(int i=1,j=0;i<=64&&it<=m;++i){
		while(prq[j+1].b==i)++j;
		solve1(it,j,i),it=j+1;
	}
	solve2(it,m);
	rep(i,1,m)printf("%d\n",ans[i]);
	ed=clock(),cerr<<1.*(ed-st)/CLOCKS_PER_SEC<<'\n';
	return 0;
}