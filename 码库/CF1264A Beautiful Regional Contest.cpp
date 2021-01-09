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
const int N=400010;
int T,n,a[N],g,s,b;
signed main() {
	T=rd();
	while(T--) {
		n=rd();
		for(rint i=1;i<=n;++i)a[i]=rd();
		int i1=1,i2=1,i3=1;
		g=s=b=-1;
		while(i1<=n&&a[i1+1]==a[i1])++i1;
		g=i1;
		i2=i1+1;
		while(i2<=n&&(i2<=i1*2||a[i2+1]==a[i2]))++i2;
		s=i2-i1;
		i3=i2+1;
		while(i3<=n&&(i3<=i1+i2||a[i3+1]==a[i3]))++i3;
		for(;;) {
			if(i3>n/2)break;
			b=i3-i2;++i3;
			while(a[i3+1]==a[i3])++i3;
		}
		if(g==-1||s==-1||b==-1||g>=s||g>=b)g=s=b=0;
		printf("%d %d %d\n",g,s,b);
	}
	return 0;
}