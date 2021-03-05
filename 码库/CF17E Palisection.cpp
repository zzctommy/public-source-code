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
#define mod 51123987
const int N=2000005;
vector<int>tr[N];
int n,len[N],fail[N],tot,las,num[N];
char str[N];
LL ans,pre[N],suf[N];
inline int gfail(int x,int i){
	while(i-len[x]-1<0||str[i-len[x]-1]!=str[i])x=fail[x];
	return x;
}
inline int fnd(int u,int c){
	for(int i:tr[u])if(i/N==c)return i%N;
	return 0;
}
signed main(){
	scanf("%d%s",&n,str);
	LL sum;
	
	sum=0;
	len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0,las=0,tot=1;
	for(int i=0;i<n;++i){
		int c=str[i]-'a',f=gfail(las,i);
		if(!fnd(f,c)){
			fail[++tot]=fnd(gfail(fail[f],i),c);
			tr[f].pb(c*N+tot),len[tot]=len[f]+2,num[tot]=num[fail[tot]]+1;
		}
		las=fnd(f,c),sum=(sum+num[las])%mod,pre[i]=num[las];
	}
	ans=sum*(sum-1)/2%mod;
	
	reverse(str,str+n);
	memset(fail,0,sizeof(fail));
	memset(num,0,sizeof(num));
	memset(len,0,sizeof(len));
	for(int i=0;i<n;++i)tr[i].clear();
	
	sum=0;
	len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0,las=0,tot=1;
	for(int i=0;i<n;++i){
		int c=str[i]-'a',f=gfail(las,i);
		if(!fnd(f,c)){
			fail[++tot]=fnd(gfail(fail[f],i),c);
			tr[f].pb(c*N+tot),len[tot]=len[f]+2,num[tot]=num[fail[tot]]+1;
		}
		las=fnd(f,c),sum=(sum+num[las])%mod,suf[n-i-1]=sum;
	}
	
//	for(int i=0;i<n;++i)cout<<pre[i]<<' ';cout<<'\n';
//	for(int i=0;i<n;++i)cout<<suf[i]<<' ';cout<<'\n';
	
	for(int i=0;i<n-1;++i)ans=(ans-pre[i]*suf[i+1]%mod+mod)%mod;
	cout<<ans<<'\n';
}