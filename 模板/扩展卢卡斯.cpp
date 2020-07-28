#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1000010;
const int M=1010;
int n,m,mod;
int A[M],B[M];
int qpow(int n,int k,int mod) {
	int res=1;
	while(k) {
		if(k&1)res=res*n%mod;
		n=n*n%mod,k>>=1;
	}
	return res;
}
int mul(int a,int b,int mod) {
	int res=0;
	while(b) {
		if(b&1)res=(res+a)%mod;
		a=(a+a)%mod,b>>=1;
	}
	return res;
}
void exgcd(int a,int b,int &d,int &x,int &y) {
	if(!b){x=1,y=0,d=a;return;}
	exgcd(b,a%b,d,y,x),y-=a/b*x;
}
int inv(int x,int mod) {
	int a,b,d;
	exgcd(x,mod,d,a,b);
	return (a%mod+mod)%mod;
}
int F(int n,int m,int k) {
	if(!n)return 1;
	int cyc=1,rem=1;
	for(int i=1;i<=k;++i)
		if(i%m)cyc=cyc*i%k;
	cyc=qpow(cyc,n/k,k);
	for(int i=k*(n/k);i<=n;++i)
		if(i%m)rem=rem*(i%k)%k;
	return F(n/m,m,k)*cyc%k*rem%k;
}
int G(int n,int m) {
	if(n<m)return 0;
	return n/m+G(n/m,m);
}
int solve(int n,int m,int f,int k) {
	int fz=F(n,f,k),fm1=inv(F(m,f,k),k),fm2=inv(F(n-m,f,k),k),index=G(n,f)-G(m,f)-G(n-m,f);
	return fz*fm1%k*fm2%k*qpow(f,index,k)%k;
}
int excrt(int n) {
	int lcm=A[1],res=B[1],x,y,a,b,c,d,tmp;
	for(int i=2;i<=n;++i) {
		a=lcm,b=A[i],c=(B[i]-res%b+b)%b;
		exgcd(a,b,d,x,y),tmp=b/d;
		if(c%d)return -1;
		x=x*(c/d)%tmp;
		res+=x*lcm;
		lcm*=tmp;
		res=(res%lcm+lcm)%lcm;
	}
	return res;
}
int exLucas(int n,int m,int mod) {
	int t=mod,tot=0;
	for(int i=2;i*i<=mod;++i) {
		if(t%i==0) {
			int k=1;
			while(t%i==0)t/=i,k*=i;
			++tot,A[tot]=k,B[tot]=solve(n,m,i,k);
		}
	}
	if(t>1)++tot,A[tot]=t,B[tot]=solve(n,m,t,t);
	return excrt(tot);
}
signed main() {
	n=rd(),m=rd(),mod=rd();
	printf("%lld\n",exLucas(n,m,mod));
	return 0;
}
