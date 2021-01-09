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
const int N=20;
const int M=(1<<N)+5;
const db eps=1e-9;
int m,n,cnt[M];
db f[M],ans;
signed main(){
	n=1<<(m=read());
	for(int i=0;i<n;++i)scanf("%lf",&f[i]),cnt[i]=cnt[i>>1]+(i&1);
	for(int o=2,k=1;k<n;o<<=1,k<<=1)
		for(int i=0;i<n;i+=o)
			for(int j=0;j<k;++j)
				f[i+j+k]+=f[i+j];
	for(int msk=0;msk<n;++msk){
		db t=1-f[(n-1)^msk];
		if(t>eps)ans+=((cnt[msk]&1)?1:-1)/t;
	}
	if(ans<eps)puts("INF");else printf("%.10lf\n",ans);
}