#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int L,S,T,m,dp[500000],now,flg[500000],ans=114514,x[114];
signed main() {
	L=rd(),S=rd(),T=rd(),m=rd();
	for(int i=1;i<=m;++i)x[i]=rd();
	sort(x+1,x+m+1);
	if(S==T) {
		ans=0;
		for(int i=1;i<=m;++i)if(x[i]%S==0)++ans;
		return printf("%d\n",ans),0;
	}
	for(int i=1,lst=0;i<=m;++i) {
		if(x[i]-lst<=2520)now+=x[i]-lst,flg[now]=1;
		else now+=2520,flg[now]=1;
		lst=x[i];
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0,now+=10;
	for(int i=1;i<=now;++i) {
		for(int j=S;j<=T;++j)
			if(i-j>-1)dp[i]=min(dp[i],dp[i-j]);
		dp[i]+=flg[i];
	}
	for(int i=now-9;i<=now;++i)ans=min(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
