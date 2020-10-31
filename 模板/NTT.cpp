#include<bits/stdc++.h>
using namespace std;
const int P=998244353;
const int N=4000010;
const int G=3;
const int Gi=332748118;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,m,rev[N],lg,lim;
int a[N],b[N];
int qpow(int n,int k) {
    int res=1;
    while(k) {
        if(k&1)res=1ll*res*n%P;
        n=1ll*n*n%P,k>>=1;
    }
    return res;
}
void NTT(int *a,int g,int op=1) {
    for(int i=0;i<lim;++i)
        if(i>rev[i])swap(a[i],a[rev[i]]);
    for(int i=1;i<lim;i<<=1) {
        int wn=qpow(g,(P-1)/(i<<1));
        for(int j=0;j<lim;j+=(i<<1)) {
            int w0=1;
            for(int k=0;k<i;++k,w0=1ll*w0*wn%P) {
                int X=a[j+k],Y=1ll*w0*a[j+k+i]%P;
                a[j+k]=(X+Y)%P;
                a[j+k+i]=(X-Y+P)%P;
            }
        }
    }
    if(op)return;int ilim=qpow(lim,P-2);
    for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%P;
}
void init(int n){
	for(lim=1,lg=0;lim<=n;lim<<=1,++lg);
    for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
signed main() {
	n=read(),m=read();
    for(int i=0;i<=n;++i)a[i]=read();
    for(int i=0;i<=m;++i)b[i]=read();
    init(n+m);
    NTT(a,G),NTT(b,G);
    for(int i=0;i<lim;++i)a[i]=1ll*a[i]*b[i]%P;
    NTT(a,Gi,0);
    for(int i=0;i<=n+m;++i)printf("%d ",a[i]);
    return 0;
}