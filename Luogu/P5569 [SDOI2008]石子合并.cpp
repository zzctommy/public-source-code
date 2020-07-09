#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=40010;
int n;
LL a[N],ans;
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=rd();
	int i=1,j,k;
	for(;i<n-1;) {
		for(j=i;j<n-1;++j) {
			if(a[j]>a[j+2])continue;
			a[j+1]+=a[j],ans+=a[j+1];
			for(k=j;k>i;--k)a[k]=a[k-1];
			++i,k=j+1;
			while(i<k&&a[k-1]<a[k])swap(a[k-1],a[k]),--k;
			break;
		}
		if(j==n-1)a[n-1]+=a[n],ans+=a[--n];
	}
	if(i==n-1)ans+=a[n-1]+a[n];
	printf("%lld\n",ans);
	return 0;
}
