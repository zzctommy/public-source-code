#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int a,p,b,ans;
int BSGS(int k,int a,int p,int b) {
	map<int,int>mp;
	int m=ceil(sqrt(p)),t=1;
	for(rint i=1;i<=m;++i)t=t*a%p,mp[t*b%p]=i;
	for(rint i=1;i<=m;++i) {
		k=k*t%p;
		if(mp.find(k)!=mp.end()) {
			return ((i*m-mp[k])%p+p)%p;
		}
	}
	return -1;
}
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
int exBSGS(int a,int p,int b) {
	a%=p,b%=p;
	if(b==1||p==1)return 0;
	int cnt=0,d,k=1,res;
	while((d=gcd(a,p))!=1) {
		if(b%d)return -1;
		++cnt,b/=d,p/=d;
		k=a/d*k%p;
		if(k==b)return cnt;
	}
	res=BSGS(k,a,p,b);
	if(~res)return res+cnt;
	else return -1;
}
signed main() {
	while("fyy AK Noip&ZJOI&NOI&CTSC&WC&ACM&IOI&POI&global-round") {
		a=rd(),p=rd(),b=rd();
		if(!a&&!p&&!b)return 0;
		ans=exBSGS(a,p,b);
		if(~ans)printf("%lld\n",ans);
		else puts("No Solution");
	}
}
