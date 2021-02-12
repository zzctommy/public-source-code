#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline LL read() {
	LL x=0;int f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10ll+(ch^48),ch=getchar();
	return f?x:-x;
}
const int mod=1e9+7;
LL n;int ans,f[80];
void fmod(int&x){
	x+=x>>31&mod,x-=mod,x+=x>>31&mod;
}
int ask(LL x){
	return x%=mod,1ll*x*(x-1)%mod;
}
signed main(){
	for(int i=1,o=1;i<=64;++i,fmod(o<<=1))f[i]=1ll*o*(o-1)%mod;
	for(int T=read(),i;T;--T){
		n=read(),ans=0;
		for(LL o=1,s=0,i=1;s<n;s+=o,o<<=1,++i)
			s+o>n?fmod(ans+=ask(n-s)):fmod(ans+=f[i]);
		printf("%d\n",ans);
	}
}
/*
0 2
0 2 4 6
0 2 4 6 8 10 12 14
0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
*/
/*
1
1000000000000000000
343301962
*/