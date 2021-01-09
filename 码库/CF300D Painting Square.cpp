#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int mod=7340033;
int n,k,f[35][1005],g[35][1005];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
signed main(){
	for(int i=0;i<=33;++i)f[i][0]=g[i][0]=1;
	for(int i=1;i<=33;++i){
		for(int j=1;j<=1000;++j)
			for(int k=0;k<j;++k)
				fmod(f[i][j]+=1ll*g[i-1][k]*g[i-1][j-k-1]%mod);
		for(int j=1;j<=1000;++j)
			for(int k=0;k<=j;++k)
				fmod(g[i][j]+=1ll*f[i][k]*f[i][j-k]%mod);
	}
	for(int T=read();T;--T){
		n=read(),k=read();
		int cnt=0;
		while(n&1&&n>2)n>>=1,++cnt;
		printf("%d\n",f[cnt][k]);
	}
	return 0;
}