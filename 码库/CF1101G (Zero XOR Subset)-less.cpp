//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")
//#pragma GCC optimize("-fgcse")
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define rint register int
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200010;
int n,a[N],d[35],ele;
void add(int x) {
	for(rint i=30;i>=0;--i) {
		if(x&(1<<i)) {
			if(d[i])x^=d[i];
			else {++ele,d[i]=x;break;}
		}
	}
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd()^a[i-1];
	if(!a[n])return puts("-1"),0;
	for(rint i=1;i<=n;++i)add(a[i]);
	printf("%d\n",ele);
	return 0;
}