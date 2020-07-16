#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int nxt[N][26];
int n,a[N],sg[N],vis[N];
char s[N];
struct lin {
	int d[35],flg;
	lin(){flg=1;memset(d,0,sizeof(d));}
	void add(int x) {
		if(!x)flg=0;
		for(rint i=30;i>=0;--i) {
			if(x>>i&1) {
				if(d[i]) x^=d[i];
				else {d[i]=x;break;}
			}
		}
	}
	int ask()  {
		if(flg)return 0;
		for(rint i=0;i<=30;++i)if(!d[i])return 1<<i;
	}
}t[N];
int dfs(int u) {
	if(u==n)return 0;
	if(u==-1)return 1<<30;
	if(vis[u])return sg[u];
	vis[u]=1;
	for(rint i=0;i<26;++i)
		t[u].add(dfs(nxt[u][i]));
	return sg[u]=t[u].ask();
}
signed main() {
	memset(nxt,-1,sizeof(nxt));
	scanf("%s",s+1),n=strlen(s+1);
	for(rint i=1;i<=n;++i)a[i]=s[i]-'A';
	for(rint i=n;i>=1;--i) {
		for(rint j=0;j<26;++j)nxt[i-1][j]=nxt[i][j];
		nxt[i-1][a[i]]=i;
	}
	puts(dfs(0)?"Alif":"yww");
	return 0;
}
