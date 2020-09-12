#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cmath>
#include<unordered_set>
#include<cassert>
using std::cout;
using std::endl;
using std::vector;
using std::lower_bound;
using std::unique;
using std::sort;
using std::max;
using std::min;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 100009
#define S 230
#define B 500
int n,m,a[N],ans[N];
int bel[N];
int cnt[N];
long long sum[S+5];
struct ASK {
	int l,r,p,id;
	inline bool operator<(const ASK&rhs)const{
		return bel[l]!=bel[rhs.l]?l<rhs.l:bel[l]&1?r<rhs.r:r>rhs.r;
	}
}q[N];
namespace FPOW{
	#define C 256//1<<8
	#define D 255//(1<<8)-1
	#define M 261//C+5
	#define K 395//N/M+5
	int p1[M],p2[K],mod;
	void FastMod(int&x,const int&p) {(x>=p)&&(x-=p);}
	void init(int p) {
		p1[0]=p2[0]=1,mod=p;
		for(int i=1;i<M;++i)p1[i]=(p1[i-1]<<1)%p;
		for(int i=1;i<K;++i)p2[i]=1ll*p2[i-1]*p1[C]%p;
	}
	int qpow(int k) {
		return 1ll*p1[k&D]*p2[k>>8]%mod;
	}
}
namespace List {
	int pre[N],suf[N],head;
	bool vis[N];
	void insert(int x) {
		if(vis[x])return;
		pre[head]=x,suf[x]=head;
		head=x,vis[x]=1;
	}
	void erase(int x) {
		if(!vis[x])return;
		if(x==head)head=suf[x];
		pre[suf[x]]=pre[x],suf[pre[x]]=suf[x];
		pre[x]=suf[x]=0,vis[x]=0;
	}
}
void add(int x){
	if(cnt[x]<S)sum[cnt[x]]-=x;
	++cnt[x];
	if(cnt[x]==S)List::insert(x);
	if(cnt[x]<S)sum[cnt[x]]+=x;
}
void pop(int x){
	if(cnt[x]<S)sum[cnt[x]]-=x;
	if(cnt[x]==S)List::erase(x);
	--cnt[x];
	if(cnt[x]<S)sum[cnt[x]]+=x;
}
int query(int len,int mod){
	FPOW::init(mod);
	int res=0,tmp=FPOW::qpow(len);
	for(int i=1,mx=min(len,S);i<=mx;++i)res=(res+1ll*(sum[i]%mod)*(tmp-FPOW::qpow(len-i)+mod)%mod)%mod;
	for(int i=List::head;i;i=List::suf[i])res=(res+1ll*i*(tmp-FPOW::qpow(len-cnt[i])+mod)%mod)%mod;
	return res;
}
signed main(){
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),bel[i]=(i-1)/B+1;
	for(int i=1;i<=m;++i)q[i].l=rd(),q[i].r=rd(),q[i].p=rd(),q[i].id=i;
	sort(q+1,q+m+1);
	for(int i=1,l=1,r=0;i<=m;++i) {
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)pop(a[l++]);
		while(r>q[i].r)pop(a[r--]);
		ans[q[i].id]=query(q[i].r-q[i].l+1,q[i].p);
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}