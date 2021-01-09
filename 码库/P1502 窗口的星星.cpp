#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=10005;
const int M=N<<2;
int n,W,H,ans;
int cpyy[N],leny,cpyx[N],lenx;
int val[M],tag[M];
struct node {
	int x,y,l;
	inline bool operator < (const node&rhs)const{return x<rhs.x;}
}a[N];
struct line {
	int x,l,r,opt;
	inline bool operator < (const line&rhs)const{return x<rhs.x;}
}b[N<<1];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p) {val[p]=max(val[lc],val[rc]);}
void pushdown(int p) {
	if(tag[p]) {
		val[lc]+=tag[p];
		val[rc]+=tag[p];
		tag[lc]+=tag[p];
		tag[rc]+=tag[p];
		tag[p]=0;
	}
}
void update(int ql,int qr,int l,int r,int p,int k) {
	if(ql<=l&&r<=qr) {
		val[p]+=k,tag[p]+=k;
		return;
	}
	pushdown(p);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,l,mid,lc,k);
	if(mid<qr)update(ql,qr,mid+1,r,rc,k);
	pushup(p);
}
void clear() {
	lenx=leny=0;
	memset(val,0,sizeof(val));
	memset(tag,0,sizeof(tag));
	ans=0;
}
void Main() {
	n=rd(),W=rd()-1,H=rd()-1;
	clear();
	for(int i=1;i<=n;++i)cpyx[++lenx]=a[i].x=rd(),cpyy[++leny]=a[i].y=rd(),a[i].l=rd();
	sort(a+1,a+n+1);
	sort(cpyx+1,cpyx+lenx+1),lenx=unique(cpyx+1,cpyx+lenx+1)-cpyx-1;
	sort(cpyy+1,cpyy+leny+1),leny=unique(cpyy+1,cpyy+leny+1)-cpyy-1;
	for(int i=1;i<=n;++i)
		b[i*2-1].x=lower_bound(cpyx+1,cpyx+lenx+1,a[i].x)-cpyx,
		b[i*2-1].l=lower_bound(cpyy+1,cpyy+leny+1,a[i].y)-cpyy,
		b[i*2-1].r=upper_bound(cpyy+1,cpyy+leny+1,a[i].y+H)-cpyy-1,b[i*2-1].opt=a[i].l,
		b[i*2].x=upper_bound(cpyx+1,cpyx+lenx+1,a[i].x+W)-cpyx,
		b[i*2].l=b[i*2-1].l,b[i*2].r=b[i*2-1].r,b[i*2].opt=-a[i].l;
	sort(b+1,b+(n<<1)+1);
//	for(int i=1;i<=n<<1;++i)cout<<i<<' '<<b[i].l<<' '<<b[i].r<<' '<<b[i].x<<' '<<b[i].opt<<endl;
//	exit(0);
	for(int i=1;i<=n<<1;++i) {
		int j=i;
		while(j<=(n<<1)&&b[j+1].x==b[j].x)++j;
		for(int k=i;k<=j;++k)update(b[k].l,b[k].r,1,n,1,b[k].opt);//,cout<<"update"<<b[k].l<<' '<<b[k].r<<' '<<b[k].opt<<endl;
		ans=max(ans,val[1]),i=j;
//		cout<<i<<' '<<val[1]<<endl;
	}
	printf("%d\n",ans);
}
signed main() {
	for(int T=rd();T;--T)Main();
}
