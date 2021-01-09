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
const int N=1e6+10;
char s[N];
int n;
vector<char>v[2];
signed main() {
	scanf("%s",s+1),n=strlen(s+1);
	for(rint i=1,j=n;j-i>=3;i+=2,j-=2) {
		if(s[i]==s[j])v[0].pb(s[i]),v[1].pb(s[j]);
		else if(s[i]==s[j-1])v[0].pb(s[i]),v[1].pb(s[j-1]);
		else if(s[i+1]==s[j])v[0].pb(s[i+1]),v[1].pb(s[j]);
		else if(s[i+1]==s[j-1])v[0].pb(s[i+1]),v[1].pb(s[j-1]);
	}
	if(n%4!=0)v[0].pb(s[1+n/2]);
	for(rint i=0;i<v[0].size();++i)putchar(v[0][i]);
	for(rint i=v[1].size()-1;i>=0;--i)putchar(v[1][i]);
}