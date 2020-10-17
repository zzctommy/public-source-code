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
int a[10];
signed main(){
	a[1]=read(),a[2]=read(),a[3]=read(),a[4]=read(),a[5]=read(),a[6]=read(),a[7]=read(),a[8]=read(),a[9]=read();
	a[0]=50+a[1]+a[8]*5+a[2]+a[3]+a[4]+a[5]+a[6]+a[7];
	a[0]>=a[9]?puts("AKIOI"):puts("AFO");
}