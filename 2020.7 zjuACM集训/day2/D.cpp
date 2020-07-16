#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define int long long
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=5000010;
int pri[N],phi[N],cnt;
int sum_phi[N];
bool vis[N];
int T,n,m;
inline void init(int lim) {
	phi[1]=1;
	for(rint i=2;i<=lim;++i) {
		if(!vis[i])pri[++cnt]=i,phi[i]=i-1;
		for(rint j=1;j<=cnt&&i*pri[j]<=lim;++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j];break;}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	for(rint i=1;i<=lim;++i)sum_phi[i]=sum_phi[i-1]+phi[i];
}
signed main() {
	init(5000005);
	T=rd();
	while(T--) {
		n=rd(),m=rd();
		if(m==1)puts("1");
		else if(m==n+1)puts("3");
		else if(m>n+1)puts("0");
		else printf("%lld\n",sum_phi[n/(m-1)]*2-sum_phi[n/m]*2);
	}
	return 0;
}
