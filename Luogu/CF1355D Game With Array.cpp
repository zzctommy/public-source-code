#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)) {
    	if(ch=='-')f=-1;
    	ch=getchar();
    }
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=1000010;
int n,s;
signed main() {
    n=rd(),s=rd();
    int res=n<<1;
    if(res>s)puts("NO");
    else {
    	puts("YES");
    	for(rint i=1;i<n;++i)printf("1 ");
    	printf("%d\n",s-n+1);
    	printf("%d\n",n);
    }
    return 0;
}