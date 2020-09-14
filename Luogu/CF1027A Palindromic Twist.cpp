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
const int N=105;
int n;
char s[N];
void Main() {
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n>>1;++i)
		if(abs(s[i]-s[n-i+1])>2||abs(s[i]-s[n-i+1])%2)return puts("NO"),void();
	puts("YES");
}
signed main() {
	for(int T=rd();T;--T)Main();
}
