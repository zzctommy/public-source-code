#include<bits/stdc++.h>
using namespace std;
inline int rd() {
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
typedef long long LL;
#define rint register int
const int N=105;
char s[N];
int n,m;
signed main() {
	n=rd(),m=rd();
	scanf("%s",s+1);
	while(m--) {
		int l=rd(),r=rd();char s1,s2;
		cin>>s1>>s2;
		for(rint i=l;i<=r;++i)if(s[i]==s1)s[i]=s2;
	}
	printf("%s",s+1);
	return 0;
}