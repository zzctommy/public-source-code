#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int mod=1e9+7;
const int N=18;
const int M=(1<<N)+5;
int ans,n,dp[M],phi[M],pri[M],pri_tot,mx,len,cnt[M];
bool vis[M];
void fmod(int&x){x-=mod,x+=x>>31&mod;}
void Sieve(const int&N){
    phi[1]=1;
    for(int i=2;i<=N;++i){
        if(!vis[i])pri[++pri_tot]=i,phi[i]=i-1;
        for(int j=1;j<=pri_tot&&i*pri[j]<=N;++j){
            vis[i*pri[j]]=1;
            if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
            phi[i*pri[j]]=phi[i]*phi[pri[j]];
        }
    }
}
int qpow(int n,int k){
    int res=1;
    for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;
    return res;
}
signed main(){
    n=read();
    for(int i=1,x;i<=n;++i)++cnt[x=read()],mx=max(mx,x);
    while(mx)++len,mx>>=1;
    dp[0]=qpow(2,cnt[0]);
    for(int msk=1;msk<1<<len;++msk){
        int k=msk&-msk;
        for(int i=msk;i;i=(i-1)&msk)if(i&k)fmod(dp[msk]+=1ll*cnt[i]*dp[msk^i]%mod);
    }
    Sieve(1<<len);
    for(int i=0;i<1<<len;++i)fmod(ans+=1ll*phi[i+1]*dp[i]%mod);
    printf("%d\n",ans);
    return 0;
}