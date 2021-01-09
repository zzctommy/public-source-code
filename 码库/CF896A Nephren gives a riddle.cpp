#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define int long long
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=1e5+!0;
int len[N],n,k,T;
const int inf=1e18+20;
char s[4][100]={
" What are you doing at the end of the world? Are you busy? Will you save us?",
" What are you doing while sending \"",
" \"? Are you busy? Will you send \"",
" \"?"
};
char dfs(int n,int k) {
	if(k>len[n])return '.';
	if(!n)return s[0][k];
	if(k<=34)return s[1][k];
	if(k<=34+len[n-1])return dfs(n-1,k-34);
	if(k<=34+len[n-1]+32)return s[2][k-34-len[n-1]];
	if(k<=34+len[n-1]+32+len[n-1])return dfs(n-1,k-66-len[n-1]);
	return s[3][k-66-len[n-1]*2];
} 
signed main() {
	len[0]=75;
	for(rint i=1;i<N;++i)
		len[i]=min(len[i-1]*2+68,inf);
	T=rd();
	while(T--) {
		n=rd(),k=rd();
		putchar(dfs(n,k));
	}
	return 0;
}