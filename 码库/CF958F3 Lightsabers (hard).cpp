#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200010;
const int L=400010;
const db pi=acos(-1.0);
const int mod=1009;
int n,m,k,a[N],cnt;
struct node {
    vector<int>a;int n;
    bool operator < (const node &rhs)const{return n>rhs.n;}
};
priority_queue<node>q;
node make(int len) {
    node res;
    res.n=len,res.a.resize(len+5);
    for(int i=0;i<=len;++i)res.a[i]=1;
    return res;
}
int lim,lg,rev[L];
void init(int len){
    for(lim=1,lg=0;lim<=len;lim<<=1,++lg);
    for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
struct cp {
    db x,y;
    cp(){x=y=0;}
    cp(db x_,db y_){x=x_,y=y_;}
    cp operator + (const cp &rhs){return cp(x+rhs.x,y+rhs.y);}
    cp operator - (const cp &rhs){return cp(x-rhs.x,y-rhs.y);}
    cp operator * (const cp &rhs){return cp(x*rhs.x-y*rhs.y,x*rhs.y+y*rhs.x);}
}A[L],B[L];
void FFT(cp*a,int o) {
    for(int i=0;i<lim;++i)
        if(i>rev[i])swap(a[i],a[rev[i]]);
    for(int i=1;i<lim;i<<=1) {
        cp wn=cp(cos(pi/i),o*sin(pi/i));
        for(int j=0;j<lim;j+=(i<<1)) {
            cp w0=cp(1,0);
            for(int k=0;k<i;++k,w0=w0*wn) {
                cp X=a[j+k],Y=w0*a[i+j+k];
                a[j+k]=X+Y,a[i+j+k]=X-Y;
            }
        }
    }
    if(~o)return;
    for(int i=0;i<lim;++i)a[i].x=(LL)(a[i].x/lim+0.5)%mod;
}
node merge(const node &a,const node &b) {
    int n=a.n,m=b.n;init(n+m);
    for(int i=0;i<=n;++i)A[i]=cp(a.a[i],0);for(int i=n+1;i<lim;++i)A[i]=cp(0,0);
    for(int i=0;i<=m;++i)B[i]=cp(b.a[i],0);for(int i=m+1;i<lim;++i)B[i]=cp(0,0);
    FFT(A,1),FFT(B,1);
    for(int i=0;i<lim;++i)A[i]=A[i]*B[i];
    FFT(A,-1);
    node res;res.n=min(n+m,k),res.a.resize(res.n+5);
    for(int i=0;i<=res.n;++i)res.a[i]=A[i].x;
    return res;
}
signed main() {
    n=rd(),m=rd(),k=rd();
    for(int i=1;i<=n;++i)++a[rd()];
    for(int i=1;i<=m;++i)if(a[i])q.push(make(a[i])),++cnt;
    for(;cnt>1;--cnt) {
        node t1=q.top();q.pop();
        node t2=q.top();q.pop();
        q.push(merge(t1,t2));
    }
    node ans=q.top();
    printf("%lld\n",ans.a[k]);
    return 0;
}