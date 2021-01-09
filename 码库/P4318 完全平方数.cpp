#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
int n;
int pri[N/9],cnt,mu[N];
bool vis[N];
void Sieve(){
	mu[1]=1;
	for(int i=2;i<N;++i){
		if(!vis[i])pri[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pri[j]<N;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
			mu[i*pri[j]]=-mu[i];
		}
	}
}
int check(int k){
	int res=0;
	for(int i=1;i*i<=k;++i)res+=k/i/i*mu[i];
	return res;
}
void Main(){
	n=read();
	int l=n,r=n*2,res=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)>=n)res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",res);
}
signed main(){
	Sieve();
	for(int T=read();T;--T)Main();
}