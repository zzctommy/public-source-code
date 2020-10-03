#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=2000005;
int n;
LL phi[N],ans;
int pri[N],cnt;
bool vis[N];
void Sieve(const int&N){
	phi[1]=1;
	for(int i=2;i<N;++i){
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for(int j=1;i*pri[j]<N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			phi[i*pri[j]]=phi[i]*phi[pri[j]];
		}
	}
	for(int i=1;i<N;++i)phi[i]+=phi[i-1];
}
signed main(){
	n=read(),Sieve(n+1);
	for(int i=1;i<=n;++i)ans+=1ll*i*phi[n/i];
	ans-=1ll*n*(n+1)/2;
	printf("%lld\n",ans);
	return 0;
}
