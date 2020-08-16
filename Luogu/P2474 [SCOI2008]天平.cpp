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
const int N=55;
int n,A,B,f[N][N],g[N][N],ans[3];
char s[N];
signed main() {
	n=rd(),A=rd(),B=rd();
	for(int i=1;i<=n;++i) {
		scanf("%s",s+1);
		for(int j=1;j<=n;++j) {
			if(i==j)f[i][j]=g[i][j]=0;
			else if(s[j]=='+')f[i][j]=1,g[i][j]=2;
			else if(s[j]=='-')f[i][j]=-2,g[i][j]=-1;
			else if(s[j]=='=')f[i][j]=g[i][j]=0;
			else f[i][j]=-2,g[i][j]=2;
		}
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				f[i][j]=max(f[i][j],f[i][k]+f[k][j]),
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	for(int i=1;i<=n;++i) {
		if(i==A||i==B)continue;
		for(int j=1;j<=n;++j) {
			if(j==A||j==B||i==j)continue;
			if(f[A][i]>g[j][B]||f[A][j]>g[i][B])++ans[0];//A+B>i+j,A-i>j-B||A-j>i-B
			if((f[A][i]==g[A][i]&&f[j][B]==g[j][B]&&f[A][i]==f[j][B])||
			(f[A][j]==g[A][j]&&g[i][B]==f[i][B]&&f[A][j]==f[i][B]))++ans[1];//A+B=i+j,A-i=j-B||A-j=i-B
			if(g[A][i]<f[j][B]||g[A][j]<f[i][B])++ans[2];//A+B<i+j,A-i<j-B||A-j<i-B
		}
	}
	printf("%d %d %d\n",ans[0]/2,ans[1]/2,ans[2]/2);
	return 0;
}