#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1010;
const int inf=2000000000;
int n,s,T,k,a[N],ans;
signed main() {
	T=rd();
	while(T--) {
		n=rd(),s=rd(),k=rd();ans=inf;
		map<int,bool>mp;
		for(rint i=1;i<=k;++i)mp[rd()]=1;
		if(!mp[s]) {puts("0");continue;}
		for(rint i=s+1;i<=n;++i)if(!mp[i]){ans=min(ans,i-s);break;}
		for(rint i=s-1;i>=1;--i)if(!mp[i]){ans=min(ans,s-i);break;}
		printf("%d\n",ans);
	} 
	return 0;
}
 