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
const int N=10000010;
int T,n,P[N];
char s[N];
int f(int x,int n) {return x>=n?x-n:x;}
int getmin(char*s,int n) {
	int i=1,j=0,k=0;
	while(i<n&&j<n&&k<n) {
		if(s[f(i+k,n)]==s[f(j+k,n)])++k;
		else {
			if(s[f(i+k,n)]>s[f(j+k,n)])i+=k+1;
			else j+=k+1;
			if(i==j)++i;
			k=0;
		}
	}
	return min(i,j);
}
int stringcmp(char*a,char*b,int len) {
	for(rint i=0;i<len;++i)
		if(a[i]!=b[i])return 1;
	return 0;
}
void Main() {
	scanf("%s",s);n=strlen(s);
	reverse(s,s+n);
	int t=getmin(s,n),j=0,ans1,ans2;
	P[t]=0;
	for(rint i=t+1;i<n;++i) {
		while(j&&s[j+t]!=s[i])j=P[j+t-1];
		if(s[t+j]==s[i])++j;
		P[i]=j;
	}
	j=P[n-1];
	if(j) {
		while(P[t+j-1])j=P[t+j-1];
		t=n-j;
	}
	for(j=t;;)
		if(j>=n-t&&!stringcmp(s+t,s+j-(n-t),n-t))j-=n-t;
		else break;
	t=j,ans1=n-t;
	t=getmin(s,t);
	ans2=n-t;
	printf("%d %d\n",ans1,ans2);
}
signed main() {
	T=rd();
	while(T--)Main();
	return 0;
}
