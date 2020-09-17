#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int rd() {
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=100010;
int n=1,a[N],st[N],top;
int main() {
    while(scanf("%d",&a[n])!=EOF)++n;
	--n;
    for(rint i=1;i<=n;++i) {
        if(!top||st[top]>=a[i])st[++top]=a[i];
        else st[upper_bound(st+1,st+top+1,a[i],greater<int>())-st]=a[i];
    }
    printf("%d\n",top),top=0;
    for(rint i=1;i<=n;++i) {
        if(!top||st[top]<a[i])st[++top]=a[i];
        else st[lower_bound(st+1,st+top+1,a[i])-st]=a[i];
    }
    printf("%d\n",top);
    return 0;
}
