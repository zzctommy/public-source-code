#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int ans,f[2][N],q,n;
signed main() {
	n=rd(),q=rd();
	while(q--) {
		int x=rd()-1,y=rd();
		if(f[x][y]) {
			ans-=f[!x][y+1]+f[!x][y-1]+f[!x][y];
		} else {
			ans+=f[!x][y+1]+f[!x][y-1]+f[!x][y];
		}
		f[x][y]^=1;
		puts(ans?"No":"Yes");
		f[0][0]=0;
		f[1][0]=0;
		f[0][n+1]=0;
		f[1][n+1]=0;
	}
	return 0;
}