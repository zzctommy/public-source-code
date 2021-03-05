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

const int N=300005;
const int M=N<<1;
int n,m;
LL ans;
int len[M],fail[M],tr[M][26],tot,cnt[2][M];
char S[N],T[N];
inline int gfail(char*str,int x,int i){
	while(i-len[x]-1<0||str[i-len[x]-1]!=str[i])x=fail[x];
	return x;
}
inline int extend(char*str,int i,int las){
	int c=str[i]-'a',f=gfail(str,las,i);
	if(!tr[f][c]){
		fail[++tot]=tr[gfail(str,fail[f],i)][c];
		tr[f][c]=tot,len[tot]=len[f]+2;
	}
	return tr[f][c];
}
signed main(){
	scanf("%s%s",S,T),n=strlen(S),m=strlen(T);
	len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0,tot=1;
	for(int i=0,las=0;i<n;++i)las=extend(S,i,las),++cnt[0][las];
	for(int i=0,las=0;i<m;++i)las=extend(T,i,las),++cnt[1][las];
	for(int i=tot;i>=0;--i)cnt[0][fail[i]]+=cnt[0][i],cnt[1][fail[i]]+=cnt[1][i];
	for(int i=2;i<=tot;++i)ans+=1ll*cnt[0][i]*cnt[1][i];
	cout<<ans<<'\n';
}