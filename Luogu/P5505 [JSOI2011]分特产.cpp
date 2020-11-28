#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define mod 1000000007
#define N 2005
int n,m,a[N],C[N][N],ans;
void fmod(int&x){x-=mod,x+=x>>31&mod;}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i)a[i]=read();
	C[0][0]=1;
	for(int i=1;i<=2000;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j){
			fmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
		}
	}
	for(int i=0;i<=n;++i){
		int res=1;
		for(int j=1;j<=m;++j)res=1ll*res*C[a[j]+n-i-1][n-i-1]%mod;
		res=1ll*res*C[n][i]%mod;
		(i&1)?fmod(ans+=mod-res):fmod(ans+=res);
	}
	printf("%d\n",ans);
	return 0;
}
