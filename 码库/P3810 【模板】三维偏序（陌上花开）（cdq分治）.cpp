//Orz cyn2006
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
const int N=200005;
int n,k,f[N],tr[N],ans[N],tot;
struct node{
	int a,b,c,s,id;
	node(){a=b=c=id=0;}
	inline bool operator == (const node&t)const{return a==t.a&&b==t.b&&c==t.c;}
}a[N],cpy[N];
inline bool cmp1(const node&a,const node&b){return a.a!=b.a?a.a<b.a:a.b!=b.b?a.b<b.b:a.c<b.c;}
inline bool cmp2(const node&a,const node&b){return a.b!=b.b?a.b<b.b:a.c<b.c;}
void add(int x,int d){for(int i=x;i<=k;i+=i&-i)tr[i]+=d;}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
void merge(int l,int mid,int r){
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r){
		if(cmp2(a[i],a[j]))cpy[k++]=a[i++];
		else cpy[k++]=a[j++];
	}
	while(i<=mid)cpy[k++]=a[i++];
	while(j<=r)cpy[k++]=a[j++];
	for(int i=l;i<=r;++i)a[i]=cpy[i];
}
void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,i,j;
	cdq(l,mid),cdq(mid+1,r);
	//sort(a+l,a+mid+1,cmp2),sort(a+mid+1,a+r+1,cmp2);
	for(i=mid+1,j=l;i<=r;++i){
		for(;j<=mid&&a[j].b<=a[i].b;++j)add(a[j].c,a[j].s);
		f[a[i].id]+=ask(a[i].c);
	}
	for(--j;j>=l;--j)add(a[j].c,-a[j].s);
	merge(l,mid,r);
}
signed main(){
	n=read(),k=read();
	rep(i,1,n)a[i].a=read(),a[i].b=read(),a[i].c=read();
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;){
		int j=i;
		while(j+1<=n&&a[j+1]==a[i])++j;
		cpy[++tot]=a[i],cpy[tot].s=j-i+1,cpy[tot].id=tot,f[tot]=j-i;
		i=j+1;
	}
	rep(i,1,tot)a[i]=cpy[i];
	cdq(1,tot);
	for(int i=1;i<=tot;++i)ans[f[a[i].id]]+=a[i].s;
	for(int i=0;i<n;++i)printf("%d\n",ans[i]);
	return 0;
}