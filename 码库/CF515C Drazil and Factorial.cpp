#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 20
char s[N];
int n,cnt[N];
void f(int x){
	if(x==2)++cnt[2];
	else if(x==3)++cnt[3];
	else if(x==4)++cnt[3],cnt[2]+=2;
	else if(x==5)++cnt[5];
	else if(x==6)++cnt[5],++cnt[3];
	else if(x==7)++cnt[7];
	else if(x==8)++cnt[7],cnt[2]+=3;
	else if(x==9)++cnt[7],cnt[3]+=2,++cnt[2];
}
signed main(){
	n=read(),scanf("%s",s+1);
	for(int i=1;i<=n;++i)f(s[i]-'0');
	for(int i=1;i<=cnt[7];++i)putchar('7');
	for(int i=1;i<=cnt[5];++i)putchar('5');
	for(int i=1;i<=cnt[3];++i)putchar('3');
	for(int i=1;i<=cnt[2];++i)putchar('2');
	puts("");
}