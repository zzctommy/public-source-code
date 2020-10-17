#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
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
const int N=20000005;
const int mod=1000000007;
int A,B,C;
int pri[N/10],cnt,s[N];
bool vis[N];
void Sieve(const int N=20000000){
	s[1]=1;
	for(int i=2;i<=N;++i){
		if(!vis[i])pri[++cnt]=i,s[i]=1ll*i*i%mod-1;
		for(int j=1;j<=cnt&&i*pri[j]<=N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){s[i*pri[j]]=1ll*s[i]*pri[j]%mod*pri[j]%mod;break;}
			s[i*pri[j]]=1ll*s[i]*s[pri[j]]%mod;
		}
	}
	for(int i=1;i<=N;++i)s[i]=(s[i]+s[i-1])%mod;
}
int f(int A,int B,int C){
	int res=0;
	for(int l=1,r,mx=min(A,B);l<=mx;l=r+1){
		r=min(A/(A/l),B/(B/l));
		res=(res+1ll*(A/l)*(B/l)%mod*(s[r]-s[l-1])%mod)%mod;
	}
	return 1ll*res*C%mod;
}
signed main(){
	Sieve();
	for(int T=read();T;--T){
		A=read(),B=read(),C=read();
		printf("%d\n",(((f(A,B,C)+f(B,C,A))%mod+f(C,A,B))%mod+mod)%mod);
	}
}