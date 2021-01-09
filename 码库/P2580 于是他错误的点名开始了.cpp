#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
int n,m;
map<string,int>mp;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;string str;
	for(int i=1;i<=n;++i)cin>>str,mp[str]=1;
	cin>>m;
	for(int i=1;i<=m;++i) {
		cin>>str;
		int t=mp[str];
		if(t==0)puts("WRONG");
		else if(t==1)puts("OK"),++mp[str];
		else puts("REPEAT");
	}
	return 0;
}