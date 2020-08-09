#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=105;
const int mod=2017;
int n,m,ans;
struct Matrix {
	int a[N][N];
	Matrix(){memset(a,0,sizeof(a));}
}fyyAKIOI;
Matrix mul(const Matrix &a,const Matrix &b) {
	Matrix c;
	for(int i=1;i<=n+1;++i)
		for(int k=1;k<=n+1;++k)
			for(int j=1;j<=n+1;++j)
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
	return c;
}
Matrix qpow(Matrix a,int k) {
	Matrix res=a;--k;
	while(k) {
		if(k&1)res=mul(res,a);
		a=mul(a,a),k>>=1;
	}
	return res;
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=m;++i) {
		int x=rd(),y=rd();
		fyyAKIOI.a[x][y]=fyyAKIOI.a[y][x]=1;
	}
	for(int i=1;i<=n;++i)fyyAKIOI.a[i][i]=1;
	for(int i=1;i<=n+1;++i)fyyAKIOI.a[i][n+1]=1;
	fyyAKIOI=qpow(fyyAKIOI,rd());
	for(int i=1;i<=n+1;++i)ans=(ans+fyyAKIOI.a[1][i])%mod;
	printf("%d\n",ans);
	return 0;
}
