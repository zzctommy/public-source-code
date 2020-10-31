#include<bits/stdc++.h>
using namespace std;
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
const int N=18;
int m,n;
const int mod=998244353;
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
struct mint{
	int x;
	void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
	mint(LL v=0){x=v%mod,x<0?x+=mod:0;}
	mint& operator += (const mint&t){fmod(x=x+t.x);return *this;}
	mint& operator -= (const mint&t){fmod(x=x-t.x);return *this;}
	mint& operator *= (const mint&t){x=1ll*x*t.x%mod;return *this;}
	mint& operator /= (const mint&t){x=1ll*x*qpow(t.x,mod-2)%mod;return *this;}
	friend mint operator + (const mint&a,const mint&b){return mint(a)+=b;}
	friend mint operator - (const mint&a,const mint&b){return mint(a)-=b;}
	friend mint operator * (const mint&a,const mint&b){return mint(a)*=b;}
	friend mint operator / (const mint&a,const mint&b){return mint(a)/=b;}
	mint operator -(){return !x?0:mod-x;}
	mint operator == (const mint&t){return x==t.x;}
	mint operator != (const mint&t){return x!=t.x;}
	mint operator < (const mint&t){return x<t.x;}
	mint operator > (const mint&t){return x>t.x;}
	mint operator <= (const mint&t){return x<=t.x;}
	mint operator >= (const mint&t){return x>=t.x;}
	friend ostream& operator << (ostream&stream,const mint&v){return stream<<v.x;}
	friend istream& operator >> (istream&stream,mint&v){return stream>>v.x;}
	explicit operator int() const{return x;}
}a[1<<N],b[1<<N],A[1<<N],B[1<<N];
void OR(mint*a,mint op){
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j)
				a[i+j+k]+=a[i+j]*op;
}
void AND(mint*a,mint op){
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j)
				a[i+j]+=a[i+j+k]*op;
}
void XOR(mint*a,mint op){
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j){
				int x=int(a[i+j]),y=int(a[i+j+k]);
				a[i+j]=(x+y)*op,a[i+j+k]=(x-y)*op;
			}
}
signed main(){
	n=1<<(m=read());
	for(int i=0;i<n;++i)A[i]=read();
	for(int i=0;i<n;++i)B[i]=read();
	
	for(int i=0;i<n;++i)a[i]=A[i];
	for(int i=0;i<n;++i)b[i]=B[i];
	OR(a,1),OR(b,1);
	for(int i=0;i<n;++i)a[i]*=b[i];
	OR(a,-1);
	for(int i=0;i<n;++i)printf("%d ",int(a[i]));puts("");
	
	for(int i=0;i<n;++i)a[i]=A[i];
	for(int i=0;i<n;++i)b[i]=B[i];
	AND(a,1),AND(b,1);
	for(int i=0;i<n;++i)a[i]*=b[i];
	AND(a,-1);
	for(int i=0;i<n;++i)printf("%d ",int(a[i]));puts("");
	
	for(int i=0;i<n;++i)a[i]=A[i];
	for(int i=0;i<n;++i)b[i]=B[i];
	XOR(a,1),XOR(b,1);
	for(int i=0;i<n;++i)a[i]*=b[i];
	XOR(a,mint((mod+1)>>1));
	for(int i=0;i<n;++i)printf("%d ",int(a[i]));puts("");
	return 0;
}