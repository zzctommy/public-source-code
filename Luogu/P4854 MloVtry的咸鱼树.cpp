#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=15;
const int M=N*(N+10);
const int inf=0x3f3f3f3f;
int n,m,dp[1<<N],U[M],V[M],S[M],L[M];
signed main(){
	n=read(),m=read();
	memset(dp,0x3f,sizeof(dp));
	for(int i=0;i<n;++i)dp[1<<i]=0;
	for(int i=0;i<m;++i)U[i]=read()-1,V[i]=read()-1,S[i]=read(),L[i]=read();
	for(int msk=0;msk<1<<n;++msk){
		for(int j=0;j<m;++j){
			if((S[j]|msk)==msk&&(msk>>U[j]&1||msk>>V[j]&1))dp[msk|(1<<U[j])|(1<<V[j])]=min(dp[msk|(1<<U[j])|(1<<V[j])],dp[msk]+L[j]);
		}
	}
	printf("%d\n",dp[(1<<n)-1]==inf?-1:dp[(1<<n)-1]);
	return 0;
}