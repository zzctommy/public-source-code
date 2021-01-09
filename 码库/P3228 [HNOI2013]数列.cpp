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
LL n;
int m,k,p;
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%p)
		if(k&1)res=1ll*n*res%p;
	return res;
}
signed main(){
	std::cin>>n>>k>>m>>p;
	std::cout<<(n%p*qpow(m,k-1)%p-1ll*(k-1)*qpow(m,k-2)%p*(1ll*m*(m+1)/2%p)%p+p)%p<<'\n';
}