#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=100005;
char strr[N];
int n,len[N],tr[N][4],fail[N],tot,las,trans[N],ans,dp[N],str[N];
inline int gfail(int x,int i){
	while(i-len[x]-1<0||str[i-len[x]-1]!=str[i])x=fail[x];
	return x;
}
inline int gtrans(int x,int i,int lim){
	while((len[x]+2)*2>lim||str[i-len[x]-1]!=str[i])x=fail[x];
	return x;
}
void Main(){
	scanf("%s",strr),n=strlen(strr);
	for(int i=0;i<n;++i){
		if(strr[i]=='A')str[i]=0;
		else if(strr[i]=='G')str[i]=1;
		else if(strr[i]=='C')str[i]=2;
		else str[i]=3;
	}
	memset(len,0,(n+3)<<2);
	memset(fail,0,(n+3)<<2);
	memset(trans,0,(n+3)<<2);
	for(int i=0;i<=n+3;++i)
		memset(tr[i],0,sizeof(tr[i]));
	len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0,tot=1,las=0;
	for(int i=0;i<n;++i){
		int c=str[i],f=gfail(las,i);
		if(!tr[f][c]){
			fail[++tot]=tr[gfail(fail[f],i)][c];
			tr[f][c]=tot,len[tot]=len[f]+2;
			if(len[tot]<=2)trans[tot]=fail[tot];
			else trans[tot]=tr[gtrans(trans[f],i,len[tot])][c];
			dp[tot]=len[tot];
		}
		las=tr[f][c];
	}
	queue<int>q;
	q.push(0),dp[0]=1,ans=n;
	while(!q.empty()){
		int u=q.front();q.pop();
		ckmin(dp[u],dp[trans[u]]+1+len[u]/2-len[trans[u]]);
		ckmin(ans,n-len[u]+dp[u]);
		for(int i=0;i<4;++i){
			int v=tr[u][i];
			if(!v)continue;
			ckmin(dp[v],dp[u]+1),q.push(v);
		}
	}
	printf("%d\n",ans);
}
signed main(){
	for(int T=read();T;--T)Main();
}