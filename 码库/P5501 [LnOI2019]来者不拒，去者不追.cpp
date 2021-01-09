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
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=500005;
const int M=100005;
int n,m,a[N],S,V,num;
int bel[N],L[N],R[N];
int pr1[N],sf1[N],t1[M];
LL  pr2[N],sf2[N],t2[M];
LL sp1[N],ss1[N],sp2[N],ss2[N];
LL res1[N<<1],res2[N<<1],ans[N];
int tl,tr;

struct QUE{
	int id,l,r;
	QUE(){l=r=id=0;}
	inline bool operator < (const QUE&t)const{return bel[l]!=bel[t.l]?l<t.l:bel[l]&1?r<t.r:r>t.r;}
}q[N];
struct ASK{
	int pos,id,l,r;
	ASK(){pos=id=l=r=0;}
	inline bool operator < (const ASK&t)const{return pos<t.pos;}
}ql[N],qr[N];

namespace BLO{

int num,S,L[N],R[N],bel[N];
int sum1[N],tag1[N];
LL sum2[N],tag2[N];
void init(){
	S=sqrt(V-1)+1,num=(V-1)/S+1;
	rep(i,1,num)L[i]=R[i-1]+1,R[i]=i*S;R[num]=V;
	rep(i,1,num)rep(j,L[i],R[i])bel[j]=i;
}
void clear(){
	memset(sum1,0,sizeof(sum1)),memset(tag1,0,sizeof(tag1));
	memset(sum2,0,sizeof(sum2)),memset(tag2,0,sizeof(tag2));	
}
void update1(int x,int d){
	for(int i=num;i>bel[x];--i)tag1[i]+=d;
	for(int i=R[bel[x]];i>=x;--i)sum1[i]+=d;
}
int query1(int x){return sum1[x]+tag1[bel[x]];}
void update2(int x,int d){
	for(int i=1;i<bel[x];++i)tag2[i]+=d;
	for(int i=L[bel[x]];i<=x;++i)sum2[i]+=d;
}
LL query2(int x){return sum2[x]+tag2[bel[x]];}
}

signed main(){
	n=read(),m=read(),
	S=sqrt(n-1)+1,num=(n-1)/S+1;
	rep(i,1,num)L[i]=R[i-1]+1,R[i]=i*S;R[num]=n;
	rep(i,1,num)rep(j,L[i],R[i])bel[j]=i;
	rep(i,1,n)ckmax(V,a[i]=read());
	rep(i,1,m)q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1);
	
	for(int i=1;i<=n;++i){
		int r1=0;LL r2=0;
		for(int j=a[i]-1;j>0;j-=j&-j)r1+=t1[j];
		for(int j=a[i]+1;j<=V;j+=j&-j)r2+=t2[j];
		pr1[i]=r1,pr2[i]=r2,sp1[i]=sp1[i-1]+r1,sp2[i]=sp2[i-1]+r2;
		for(int j=a[i];j<=V;j+=j&-j)++t1[j];
		for(int j=a[i];j>0;j-=j&-j)t2[j]+=a[i];
	}
	memset(t1,0,sizeof(t1)),memset(t2,0,sizeof(t2));
	for(int i=n;i>=1;--i){
		int r1=0;LL r2=0;
		for(int j=a[i]-1;j>0;j-=j&-j)r1+=t1[j];
		for(int j=a[i]+1;j<=V;j+=j&-j)r2+=t2[j];
		sf1[i]=r1,sf2[i]=r2,ss1[i]=ss1[i+1]+r1,ss2[i]=ss2[i+1]+r2;
		for(int j=a[i];j<=V;j+=j&-j)++t1[j];
		for(int j=a[i];j>0;j-=j&-j)t2[j]+=a[i];
	}

	rep(i,1,n)sp1[i]=sp1[i-1]+1ll*a[i]*(pr1[i]+1);
	rep(i,1,n)sp2[i]=sp2[i-1]+pr2[i];
	per(i,n,1)ss1[i]=ss1[i+1]+1ll*a[i]*(sf1[i]+1);
	per(i,n,1)ss2[i]=ss2[i+1]+sf2[i];

	// for(int i=1;i<=n;++i)cerr<<sp1[i]<<' ';cerr<<'\n';
	// for(int i=1;i<=n;++i)cerr<<sp2[i]<<' ';cerr<<'\n';
	// for(int i=1;i<=n;++i)cerr<<sf1[i]<<' ';cerr<<'\n';
	// for(int i=1;i<=n;++i)cerr<<sf2[i]<<' ';cerr<<'\n';

	for(int i=1,l=1,r=0;i<=m;++i){
		// cerr<<q[i].id<<' '<<q[i].l<<' '<<q[i].r<<' '<<l<<' '<<r<<'\n';
		if(l>q[i].l)ql[++tl].pos=r+1,ql[tl].l=q[i].l,ql[tl].r=l-1,ql[tl].id=q[i].id<<1,l=q[i].l;
		if(r<q[i].r)qr[++tr].pos=l-1,qr[tr].l=r+1,qr[tr].r=q[i].r,qr[tr].id=q[i].id<<1|1,r=q[i].r;
		if(l<q[i].l)ql[++tl].pos=r+1,ql[tl].l=l,ql[tl].r=q[i].l-1,ql[tl].id=q[i].id<<1,l=q[i].l;
		if(r>q[i].r)qr[++tr].pos=l-1,qr[tr].l=q[i].r+1,qr[tr].r=r,qr[tr].id=q[i].id<<1|1,r=q[i].r;
	}
	sort(ql+1,ql+tl+1),sort(qr+1,qr+tr+1);

	BLO::init();
	for(int i=1,j=1;i<=n;++i){
		while(j<=tr&&qr[j].pos<i)++j;
		BLO::update1(a[i],1),BLO::update2(a[i],a[i]);
		for(;j<=tr&&qr[j].pos==i;++j){
			int st=qr[j].l,ed=qr[j].r,id=qr[j].id;
			for(int k=st;k<=ed;++k)
				res1[id]+=1ll*BLO::query1(a[k]-1)*a[k],res2[id]+=BLO::query2(a[k]+1);
			// cerr<<"qr:"<<i<<' '<<qr[j].l<<' '<<qr[j].r<<' '<<res1[id]<<' '<<res2[id]<<'\n';
		}
	}
	BLO::clear();
	for(int i=n,j=tl;i>=1;--i){
		while(j>=1&&ql[j].pos>i)--j;
		BLO::update1(a[i],1),BLO::update2(a[i],a[i]);
		for(;j>=1&&ql[j].pos==i;--j){
			int st=ql[j].l,ed=ql[j].r,id=ql[j].id;
			for(int k=st;k<=ed;++k)
				res1[id]+=1ll*BLO::query1(a[k]-1)*a[k],res2[id]+=BLO::query2(a[k]+1);
			// cerr<<"ql:"<<i<<' '<<ql[j].l<<' '<<ql[j].r<<' '<<res1[id]<<' '<<res2[id]<<'\n';
		}
	}

	LL now=0;
	for(int i=1,l=1,r=0;i<=m;++i){
		int id=q[i].id;
		if(l>q[i].l)now+=ss1[q[i].l]-ss1[l]-res1[id<<1]+ss2[q[i].l]-ss2[l]-res2[id<<1],l=q[i].l;
		if(r<q[i].r)now+=sp1[q[i].r]-sp1[r]-res1[id<<1|1]+sp2[q[i].r]-sp2[r]-res2[id<<1|1],r=q[i].r;
		if(l<q[i].l)now-=ss1[l]-ss1[q[i].l]-res1[id<<1]+ss2[l]-ss2[q[i].l]-res2[id<<1],l=q[i].l;
		if(r>q[i].r)now-=sp1[r]-sp1[q[i].r]-res1[id<<1|1]+sp2[r]-sp2[q[i].r]-res2[id<<1|1],r=q[i].r;
		ans[id]=now;
	}
	rep(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}