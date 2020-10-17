#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=55;
const int mod=998244353;
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
int n,a[N],fac[N],ifc[N],ans;
void init(){
	fac[0]=1;
	for(int i=1;i<N;++i)fac[i]=1ll*fac[i-1]*i%mod;
	ifc[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;~i;--i)ifc[i]=1ll*ifc[i+1]*(i+1)%mod;
}
int f(int i,int j){
	if(i>j)return 0;
	return 1ll*fac[j]*fac[n-i-1]%mod*ifc[j-i]%mod*ifc[n-1]%mod;
}
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
signed main(){
	n=read(),init();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i){
		int l=i-1,r=i+1;
		while(l>=1&&a[l]<a[i])--l;
		while(r<=n&&a[r]<a[i])++r;
		int A,B=0,C=0;
		if(l<1&&r>n){printf("%d ",n-1);continue;}
		for(int j=1;j<n;++j){
			A=0;
			if(r<=n)fmod(A+=f(r-i,j));
			if(l>=1)fmod(A+=f(i-l,j));
			if(l>=1&&r<=n)fmod(A-=f(r-l,j));
			fmod(C+=1ll*(A-B)*(j-1)%mod),B=A;
		}
		printf("%d ",C);
	}
	return 0;
}