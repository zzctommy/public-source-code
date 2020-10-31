#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
const int mod=998244353;
const int N=10005;
int p,s,r,ans;
int jc[N],jv[N],inv[N];
int qpow(int n,int k){int res=1;for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;return res;}
void init(const int&N){
	jc[0]=1;
	for(int i=1;i<=N;++i)jc[i]=1ll*jc[i-1]*i%mod;
	jv[N]=qpow(jc[N],mod-2);
	for(int i=N-1;i>=0;--i)jv[i]=1ll*jv[i+1]*(i+1)%mod;
	inv[1]=1;
	for(int i=2;i<=N;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
int C(int n,int m){return 1ll*jc[n]*jv[m]%mod*jv[n-m]%mod;}
int g(int n,int m){return C(n+m-1,m-1);}//sum of m non-neg integers=n
int f(int x,int y,int z){//number=x,sum=y,limit=z
	if(!x&&!y)return 1;
	int res=0,flg=(x&1)?-1:1;
	for(int i=0;i<=x;++i,flg*=-1)
		if(y-(z+1)*(x-i)>=0)res=(res+1ll*flg*C(x,i)*g(y-(z+1)*(x-i),x)%mod)%mod;
	return res;
}
signed main(){
	init(6000);
	p=read(),s=read(),r=read();
	for(int i=r;i<=s;++i){
		for(int j=0;(j+1)*i<=s&&j<p;++j){
			ans=(ans+1ll*C(p-1,j)*f(p-j-1,s-(j+1)*i,i-1)%mod*inv[j+1]%mod)%mod;
		}
	}
	ans=1ll*ans*qpow(C(s-r+p-1,p-1),mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}