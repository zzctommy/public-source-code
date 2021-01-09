#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
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
const int N=300005;
int X,Y,n,m,a[N],b[N],ans;
int check(int t,int x) {
	for(int i=t;i<=m;++i)if(a[i]!=x&&b[i]!=x&&a[i]!=X&&b[i]!=X)return 0;
	return 1;
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=m;++i)a[i]=rd(),b[i]=rd();
	X=a[1];
	for(int i=1;i<=m;++i) {
		if(a[i]!=X&&b[i]!=X) {
			Y=1;
			if(check(i,a[i]))ans=1;
			else if(check(i,b[i]))ans=1;
			break;
		}
	}
	X=b[1];
	for(int i=1;i<=m;++i) {
		if(a[i]!=X&&b[i]!=X) {
			Y=1;
			if(check(i,a[i]))ans=1;
			else if(check(i,b[i]))ans=1;
			break;
		}
	}
	puts(ans|(!Y)?"YES":"NO");
}
