#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
typedef long long LL;
typedef double db;
template<class T>inline bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>inline bool ckmin(T&x,T y){return x>y?x=y,1:0;}
const int N=(1<<20)+5;
#define mod 1000000021
#define base 37
LL ans;
int n;
int pw[N],H[N],pre[N],suf[N],cnt[30],tr[30];
char str[N];
LL val(int l,int r){return (H[r]-1ll*H[l-1]*pw[r-l+1]%mod+mod)%mod;}
void add(int x,int d){for(int i=x;i<=29;i+=i&-i)tr[i]+=d;}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
void Main(){
	ans=0,memset(tr,0,sizeof(tr));
	scanf("%s",str+1),n=strlen(str+1);
	rep(i,1,n)H[i]=(1ll*H[i-1]*base+str[i]-'a')%mod;
	pre[0]=0;rep(i,0,25)cnt[i]=-1;
	rep(i,1,n)pre[i]=pre[i-1]+(cnt[str[i]-'a']*=-1);
	suf[n+1]=0;rep(i,0,25)cnt[i]=-1;
	per(i,n,1)suf[i]=suf[i+1]+(cnt[str[i]-'a']*=-1);
	for(int len=2;len<n;++len){
		add(pre[len-1]+1,1);LL tmp=val(1,len);
		for(int i=1;i+len-1<n;i+=len){
			if(tmp!=val(i,i+len-1))break;
			ans+=ask(suf[i+len]+1);
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	pw[0]=1;rep(i,1,N-1)pw[i]=1ll*base*pw[i-1]%mod;
	for(int T=read();T;--T)Main();
}