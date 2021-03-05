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

struct Bignum{
int a[300],len;
Bignum(){len=1,memset(a,0,sizeof(a));}
inline void print(char text=-1){
	per(i,len,1)putchar('0'+a[i]);
	if(~text)putchar(text);
}
inline void init(int n){
	if(!n)a[len=1]=0;
	else{
		len=0;
		while(n)a[++len]=n%10,n/=10;
	}
}
inline Bignum operator + (const Bignum&t){
	Bignum res;
	int mx=max(len,t.len);
	for(int i=1;i<=mx;++i){
		res.a[i]+=a[i]+t.a[i];
		if(res.a[i]>9)++res.a[i+1],res.a[i]-=10;
	}
	res.len=mx;
	if(res.a[mx+1])++res.len;
	return res;
}
inline Bignum operator - (const Bignum&t){
	Bignum res;
	int mx=max(len,t.len);
	for(int i=1;i<=mx;++i){
		res.a[i]+=a[i]-t.a[i];
		if(res.a[i]<0)--res.a[i+1],res.a[i]+=10;
	}
	res.len=mx;
	while(!res.a[res.len])--res.len;
	return res;
}
inline Bignum operator * (const Bignum&t){
	Bignum res;
	for(int i=1;i<=len;++i)
		for(int j=1;j<=t.len;++j)
			res.a[i+j-1]+=a[i]*t.a[j];
	res.len=len+t.len-1;
	for(int i=1;i<=res.len;++i)
		res.a[i+1]+=res.a[i]/10,res.a[i]%=10;
	if(res.a[res.len+1])++res.len;
	return res;
}
inline Bignum operator / (const int&t){
	Bignum res;
	int now=0;
	for(int i=len;i>=1;--i){
		now=now*10+a[i];
		res.a[++res.len]=now/t,now%=t;
	}
	reverse(res.a+1,res.a+res.len+1);
	while(!res.a[res.len])--res.len;
	return res;
}

}ans,two,thr;
inline Bignum change(int x){
	Bignum res;
	res.init(x);
	return res;
}
inline Bignum qpow(Bignum n,int k){
	Bignum res;
	res.init(1);
	for(;k;k>>=1,n=n*n)
		if(k&1)res=res*n;
	return res;
}
signed main(){
	two.init(2),thr.init(3);
	int n=read(),m=n*(n+1)/2,p=(n+1)/2;
	ans=ans+thr*qpow(two,(m-p)/2+p);
	ans=ans+two*qpow(two,(m+2)/3);
	ans=ans+qpow(two,m);
	ans=ans/6;
	ans.print();
}