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
const int N=50005;
int n,n_,len,lsh[N<<2],dp[N],ans,tr[N];
struct node{
	int a,b,c,d,s,op,id;
	node(){a=b=c=d=0;}
	inline bool operator == (const node&t)const{return a==t.a&&b==t.b&&c==t.c&&d==t.d;}
}a[N],b[N];
inline bool cmp1(const node&a,const node&b){return a.a!=b.a?a.a<b.a:a.b!=b.b?a.b<b.b:a.c!=b.c?a.c<b.c:a.d<b.d;}
inline bool cmp2(const node&a,const node&b){return a.b!=b.b?a.b<b.b:a.a!=b.a?a.a<b.a:a.c!=b.c?a.c<b.c:a.d<b.d;}
inline bool cmp3(const node&a,const node&b){return a.c<b.c;}
void upd(int x,int d){for(int i=x;i<=len;i+=i&-i)ckmax(tr[i],d);}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)ckmax(res,tr[i]);return res;}
void clr(int x){for(int i=x;i<=len;i+=i&-i)tr[i]=0;}
void cdq2(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,i,j;
	cdq2(l,mid),sort(a+l,a+mid+1,cmp3),sort(a+mid+1,a+r+1,cmp3);
	for(i=mid+1,j=l;i<=r;++i){
		for(;a[j].c<=a[i].c&&j<=mid;++j)if(a[j].op)upd(a[j].d,dp[a[j].id]);
		if(!a[i].op)ckmax(dp[a[i].id],ask(a[i].d)+a[i].s);
	}
	for(--j;j>=l;--j)clr(a[j].d);
	sort(a+mid+1,a+r+1,cmp2);
	cdq2(mid+1,r);
}
void cdq1(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq1(l,mid);
	for(int i=l;i<=r;++i)a[i].op=i<=mid;
	sort(a+l,a+r+1,cmp2);
	cdq2(l,r);
	sort(a+l,a+r+1,cmp1);
	cdq1(mid+1,r);
}
signed main(){
	n_=read();assert(n_<=50000);
	rep(i,1,n_)b[i].a=read(),b[i].b=read(),b[i].c=read(),b[i].d=lsh[++len]=read();
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	rep(i,1,n_)b[i].d=lower_bound(lsh+1,lsh+len+1,b[i].d)-lsh;
	sort(b+1,b+n_+1,cmp1);
	for(int i=1,j=1;i<=n_;i=++j){
		while(j<n_&&b[j+1]==b[i])++j;
		a[++n]=b[i],a[n].s=j-i+1,a[n].id=n,dp[n]=a[n].s;
	}
	cdq1(1,n);
	for(int i=1;i<=n;++i)ckmax(ans,dp[i]);
	printf("%d\n",ans);return 0;
}