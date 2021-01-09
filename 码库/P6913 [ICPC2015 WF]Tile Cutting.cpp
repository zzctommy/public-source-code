#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 500005
#define M (N<<2)
#define C 500000
#define mod 998244353
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
int a[M],rev[M],lg,lim;
int id[20][N],mx[20][N],lg2[N],pw2[40];
int n;
void init_poly(int n){
	for(lim=1,lg=0;lim<n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void fmod(int&x){x-=mod,x+=x>>31&mod;}
void NTT(int*a,int g,int op=0){
	for(int i=0;i<lim;++i)
		if(i>rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1){
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod){
				int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
				a[j+k]=(X+Y)%mod,a[i+j+k]=(X-Y+mod)%mod;
			}
		}
	}
	if(!op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
void init_ST(const int&n){
	lg2[0]=-1;for(int i=1;i<=n;++i)lg2[i]=lg2[i>>1]+1;
	pw2[0]=1;for(int i=1;i<=20;++i)pw2[i]=pw2[i-1]<<1;
	for(int i=1;i<=n;++i)mx[0][i]=a[i],id[0][i]=i;
	for(int i=1;i<=lg2[n];++i)
		for(int j=1;j+pw2[i]-1<=n;++j){
			int t=j+pw2[i-1];
			if(mx[i-1][j]>=mx[i-1][t])mx[i][j]=mx[i-1][j],id[i][j]=id[i-1][j];
			else mx[i][j]=mx[i-1][t],id[i][j]=id[i-1][t];
		}
}
void ask(int l,int r){
	int x=lg2[r-l+1],t=r-pw2[x]+1;
	if(mx[x][l]>=mx[x][t])printf("%d %d\n",id[x][l],mx[x][l]);
	else printf("%d %d\n",id[x][t],mx[x][t]);
}
signed main(){
	for(int i=1;i<=C;++i)
		for(int j=1;i*j<=C;++j)
			++a[i*j];
	init_poly(C<<1),NTT(a,3);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*a[i]%mod;
	NTT(a,qpow(3,mod-2),1);
	init_ST(C);
	n=read();
	while(n--){
		int l=read(),r=read();
		ask(l,r);
	}
	return 0;
}
/*
2
4 4
2 6

*/