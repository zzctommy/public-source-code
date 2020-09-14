#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int n,q;
signed main() {
	n=rd(),q=rd();
	while(q--) {
		int x=rd(),y=rd(),t=0;
		if((x+y)%2==0) {
			if(n%2==0)t=n/2*(x-1)+(y+1)/2;
			else {
				if(x%2==1)t=n*(x/2)+(y+1)/2;
				else t=n*(x/2-1)+n/2+1+(y+1)/2;
			}
			printf("%lld\n",t);
		} else {
			if(n%2==0)t=n/2*(x-1)+(y+1)/2;
			else {
				if(x%2==1)t=n*(x/2)+(y+1)/2;
				else t=n*(x/2-1)+n/2+(y+1)/2;
			}
			printf("%lld\n",t+(n*n+1)/2);
		}
	}
}
