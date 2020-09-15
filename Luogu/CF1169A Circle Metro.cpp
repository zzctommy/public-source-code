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
const int N=105;
int n,a,b,x,y;
signed main() {
	n=rd(),a=rd(),x=rd(),b=rd(),y=rd();
	while("fyyAKIOI") {
		if(a==b)return puts("YES"),0;
		++a,--b;
		if(a==n+1)a=1;
		if(b==0)b=n;
		if(a==b)return puts("YES"),0;
		if(x==a||y==b)break;
	}
	puts("NO");
}
