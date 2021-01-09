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
#define mod 998244353
void fmod(int&x){x-=mod,x+=x>>31&mod;}
const int N=80005;
int n_,n,len,lsh[N],ans2,cnt[N];
LL ans1,val[N];
struct node{
	int a,b,c,d,op,g;
	LL w,f;
	node(){a=b=c=d=w=f=g=op=0;}
	inline bool operator == (const node&t)const{return a==t.a&&b==t.b&&c==t.c&&d==t.d;}
}a[N],b[N];
inline bool cmp1(const node&a,const node&b){return a.a!=b.a?a.a<b.a:a.b!=b.b?a.b<b.b:a.c!=b.c?a.c<b.c:a.d<b.d;}
inline bool cmp2(const node&a,const node&b){return a.b!=b.b?a.b<b.b:a.a!=b.a?a.a<b.a:a.c!=b.c?a.c<b.c:a.d<b.d;}
inline bool cmp3(const node&a,const node&b){return a.c<b.c;}
void add(int x,LL f,int g){
	for(int i=x;i<=n;i+=i&-i)
		if(ckmax(val[i],f))cnt[i]=g;
		else if(val[i]==f)fmod(cnt[i]+=g);
}
pair<LL,int>ask(int x){
	pair<LL,int>res=mkp(0,0);
	for(int i=x;i>0;i-=i&-i)
		if(ckmax(res.fi,val[i]))res.se=cnt[i];
		else if(res.fi==val[i])fmod(res.se+=cnt[i]);
	return res;
}
void clr(int x){for(int i=x;i<=n;i+=i&-i)val[i]=cnt[i]=0;}
void cdq2(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,i,j;
	cdq2(l,mid),sort(a+l,a+mid+1,cmp3),sort(a+mid+1,a+r+1,cmp3);
	for(i=mid+1,j=l;i<=r;++i){
		for(;a[j].c<=a[i].c&&j<=mid;++j)if(a[j].op)add(a[j].d,a[j].f,a[j].g);
		if(!a[i].op){
			pair<LL,int>tmp=ask(a[i].d);tmp.fi+=a[i].w;
			if(!tmp.se)continue;
			if(ckmax(a[i].f,tmp.fi))a[i].g=tmp.se;
			else if(a[i].f==tmp.fi)fmod(a[i].g+=tmp.se);
		}
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
	n_=read(),read();
	for(int i=1;i<=n_;++i)b[i].a=read(),b[i].b=read(),b[i].c=read(),b[i].d=lsh[++len]=read(),b[i].w=read();
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n_;++i)b[i].d=lower_bound(lsh+1,lsh+len+1,b[i].d)-lsh;
	sort(b+1,b+n_+1,cmp1);
	for(int i=1,j=i;i<=n_;i=++j){
		a[++n]=b[i],a[n].g=1;
		while(j<n_&&b[j+1]==b[i])a[n].w+=b[++j].w;
		a[n].f=a[n].w;
	}
	cdq1(1,n);
	for(int i=1;i<=n;++i)
		if(ckmax(ans1,a[i].f))ans2=a[i].g;
		else if(ans1==a[i].f)fmod(ans2+=a[i].g);
	printf("%lld\n%d\n",ans1,ans2);
	return 0;
}