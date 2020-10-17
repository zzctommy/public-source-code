#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
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
const int N=1005;
const int M=10005;
int n,m,k,D[N],T[M],A[M],B[M];
int las[N],nex[N],arv[N],sum[N];
LL ans;
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<n;++i)D[i]=read();
	for(int i=1;i<=m;++i){
		T[i]=read(),A[i]=read(),B[i]=read();
		las[A[i]]=max(las[A[i]],T[i]);
		++sum[B[i]];
	}
	arv[1]=0;
	for(int i=1;i<n;++i){
		arv[i+1]=arv[i];
		if(las[i]>arv[i])arv[i+1]+=las[i]-arv[i]; 
		arv[i+1]+=D[i];
	}
	for(int i=1;i<=m;++i)ans+=arv[B[i]]-T[i];
	for(int i=1;i<=n;++i)sum[i]+=sum[i-1];
	while(k--){
		nex[n-1]=n;
		for(int i=n-2;i>0;--i)
			if(las[i+1]>=arv[i+1])nex[i]=i+1;
			else nex[i]=nex[i+1];
		int add=-1,mx=0;
		for(int i=1;i<n;++i){
			int s=sum[nex[i]]-sum[i];
			if(s>mx&&D[i]>0)mx=s,add=i;
		}
		if(!~add)break;
		ans-=mx,--D[add];
		arv[1]=0;
		for(int i=2;i<=n;++i){
			arv[i+1]=arv[i];
			if(las[i]>arv[i])arv[i+1]+=las[i]-arv[i];
			arv[i+1]+=D[i];
		}
	}
	printf("%lld\n",ans);
	return 0;
}