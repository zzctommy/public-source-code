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
char cltout[1<<21],*oh=cltout,*ot=cltout+(1<<21);
inline void pc(char c){
    if(oh==ot){
        fwrite(cltout,1,1<<21,stdout);
        oh=cltout;
    }
    *oh++=c;
}
inline void write(LL w,char text=-1){
    if(!w)pc(48);
    else{
        int d[20];
        for(d[0]=0;w;d[++d[0]]=w%10,w/=10);
        for(;d[0];pc(d[d[0]--]^48));
    }
    if(text>=0)pc(text);
}
const int N=500005;
int n,m,a[N];
int V,S,bin[N],bel[N];
LL pre[N],ans[N];
int tot;
int cnt[N],tim[N];
LL suf[N];
vector<int>d[N];
struct QUE{
	int id,l,r;
	QUE(){id=l=r=0;}
	inline bool operator < (const QUE&t)const{return bel[l]!=bel[t.l]?l<t.l:bel[l]&1?r<t.r:r>t.r;}
}q[N];
struct ASK{
	int pos,id,op,l,r;
	ASK(){pos=l=r=op=id=0;}
	inline bool operator < (const ASK&t)const{return pos<t.pos;}
}qn[N<<1];
void init(){
	for(int i=1;i<=n;++i)suf[a[i]]+=V/a[i];
	for(int i=V;i>=1;--i)suf[i]+=suf[i+1];
	LL mx=1e15;
	for(int i=1;i*i<=V;++i)if(ckmin(mx,5ll*i*n+suf[i+1]))S=i;
	for(int i=1;i<=V;++i)for(int j=1;i*j<=V;++j)d[i*j].pb(i);
}
signed main(){
//	freopen("data1.in","r",stdin);
//	freopen("1.out","w",stdout); 
	clock_t ST=clock(),ED;
	n=read(),m=read();
	int blocksize=sqrt(n-1)+1;
	rep(i,1,n)ckmax(V,a[i]=read()),bel[i]=(i-1)/blocksize+1;
	init();
	cerr<<S<<'\n';
	for(int i=1;i<=n;++i){
		int x=a[i],res=bin[x];
		for(int j=0,up=sz(d[x]);j<up;++j){
			if(d[x][j]>S)break;
			res+=tim[d[x][j]];
		}
		pre[i]=pre[i-1]+res;
		for(int j=0,up=sz(d[x]);j<up;++j)++bin[d[x][j]];
		if(x>S)for(int j=x;j<=V;j+=x)++bin[j];
		else ++tim[x];
	}
	rep(i,1,m)q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1);
	for(int i=1,l=1,r=0;i<=m;++i){
		if(l>q[i].l){
			if(r<=n)qn[++tot].pos=r,qn[tot].id=q[i].id,qn[tot].l=q[i].l,qn[tot].r=l-1,qn[tot].op=1;
			ans[q[i].id]-=pre[l-1]-pre[q[i].l-1]+(l-q[i].l)*2,l=q[i].l;
		}
		if(r<q[i].r){
			if(l>1)qn[++tot].pos=l-1,qn[tot].id=q[i].id,qn[tot].l=r+1,qn[tot].r=q[i].r,qn[tot].op=-1;
			ans[q[i].id]+=pre[q[i].r]-pre[r],r=q[i].r;
		}
		if(l<q[i].l){
			if(r<=n)qn[++tot].pos=r,qn[tot].id=q[i].id,qn[tot].l=l,qn[tot].r=q[i].l-1,qn[tot].op=-1;
			ans[q[i].id]+=pre[q[i].l-1]-pre[l-1]+(q[i].l-l)*2,l=q[i].l;
		}
		if(r>q[i].r){
			if(l>1)qn[++tot].pos=l-1,qn[tot].id=q[i].id,qn[tot].l=q[i].r+1,qn[tot].r=r,qn[tot].op=1;
			ans[q[i].id]-=pre[r]-pre[q[i].r],r=q[i].r;
		}
	}
	sort(qn+1,qn+tot+1);
	memset(bin,0,sizeof(bin));
	for(int i=1,j=1;i<=n;++i){
		int x=a[i];
		for(int k=0,up=sz(d[x]);k<up;++k)++bin[d[x][k]];
		if(x>S)for(int k=x;k<=V;k+=x)++bin[k];
		for(;j<=tot&&qn[j].pos==i;++j){
			int st=qn[j].l,ed=qn[j].r; LL sum=0;
			for(int k=st;k<=ed;++k)sum+=bin[a[k]];
			ans[qn[j].id]+=1ll*sum*qn[j].op;
		}
	}
	ED=clock(),cerr<<1.*(ED-ST)/CLOCKS_PER_SEC<<'\n';
	for(int v=1;v<=S;++v){
		for(int i=1;i<=n;++i)cnt[i]=cnt[i-1]+(a[i]%v==0),tim[i]=tim[i-1]+(a[i]==v);
		for(int i=1;i<=tot;++i)ans[qn[i].id]+=1ll*(cnt[qn[i].r]-cnt[qn[i].l-1])*tim[qn[i].pos]*qn[i].op;
	}
	rep(i,1,m)ans[q[i].id]+=ans[q[i-1].id];
	rep(i,1,m)ans[q[i].id]+=q[i].r-q[i].l+1;
	rep(i,1,m)write(ans[i],'\n');
	// rep(i,1,m)printf("%lld\n",ans[i]);
	fwrite(cltout,1,oh-cltout,stdout),oh=cltout;
	ED=clock(),cerr<<1.*(ED-ST)/CLOCKS_PER_SEC<<'\n';
	return 0;
}
/*
6 3
1 1 4 5 1 4
1 1
4 5
1 4

*/