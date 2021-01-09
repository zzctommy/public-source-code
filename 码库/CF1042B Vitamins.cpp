#include<bits/stdc++.h>
#define N 100009
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int n,c[N],a[N],dp[8];
char s[N];
signed main() {
	memset(dp,0x3f,sizeof(dp));
	n=rd();
	for(int i=1;i<=n;++i) {
		c[i]=rd(),scanf("%s",s+1);
		for(int j=1,m=strlen(s+1);j<=m;++j)a[i]|=(1<<(s[j]-'A'));
	}
	for(int i=1;i<=n;++i) {
		dp[a[i]]=std::min(dp[a[i]],c[i]);
		for(int msk=0;msk<8;++msk)
			dp[msk|a[i]]=std::min(dp[msk|a[i]],dp[msk]+c[i]);
	}
	if(dp[7]==0x3f3f3f3f)puts("-1");
	else printf("%d\n",dp[7]);
	return 0;
}