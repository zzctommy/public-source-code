#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=105;
int n,a[N],b[N];
void Main() {
	n=rd();
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;++i)a[i]=rd(),++b[a[i]];
	int f0=1,f1=1,ans=0;
	for(int i=0;i<N;++i) {
		if(b[i]==1) {
			if(f1)ans+=i,f1=0;
		} else if(!b[i]){
			if(f0)ans+=i,f0=0;
			if(f1)ans+=i,f1=0;
		}
	}
	printf("%d\n",ans);
}
signed main() {
	for(int T=rd();T;--T)Main();
}
