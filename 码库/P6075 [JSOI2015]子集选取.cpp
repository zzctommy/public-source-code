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
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
int n,k;
const int mod=1e9+7;
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;
	return res;
}
signed main(){
	cin>>n>>k,cout<<qpow(2,1ll*n*k%(mod-1));
}