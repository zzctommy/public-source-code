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
#define mod 19930726
const int N=1000005;
inline int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)
		if(k&1)res=1ll*n*res%mod;
	return res;
}
int n,id[N],ans=1;
LL k;
char str[N];
int len[N],tr[N][26],fail[N],tot,las,cnt[N];
inline int gfail(int x,int i){
	while(i-len[x]-1<0||str[i-len[x]-1]!=str[i])x=fail[x];
	return x;
}
inline bool cmp(const int&a,const int&b){
	return len[a]>len[b];
}
signed main(){
	scanf("%d%lld%s",&n,&k,str);
	len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0,tot=1,las=0;
	for(int i=0;i<n;++i){
		int c=str[i]-'a',f=gfail(las,i);
		if(!tr[f][c]){
			fail[++tot]=tr[gfail(fail[f],i)][c];
			len[tot]=len[f]+2,tr[f][c]=tot;
		}
		las=tr[f][c],++cnt[las];
	}
	for(int i=tot;i>=0;--i)cnt[fail[i]]+=cnt[i];
	for(int i=0;i<=tot;++i)id[i]=i;
	sort(id,id+tot+1,cmp);
	for(int i=0;i<=tot;++i){
		int x=id[i];
		if(len[x]%2==0)continue;
		if(k<=cnt[x]){
			ans=1ll*ans*qpow(len[x],k)%mod,k=0;
			break;
		}else{
			ans=1ll*ans*qpow(len[x],cnt[x])%mod;
			k-=cnt[x];
		}
	}
	if(k)cout<<-1<<'\n';
	else cout<<ans<<'\n';
}