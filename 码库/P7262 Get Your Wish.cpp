#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
char rddir(){
	char ch=getchar();
	while(ch!='<'&&ch!='>'&&ch!='v'&&ch!='^')ch=getchar();
	return ch;
}
const int N=105;
int n,m,a[N][N],s[N][N];
char dir;
signed main(){
	n=read(),m=read(),dir=rddir();
	rep(i,1,n){
		static char str[N];
		scanf("%s",str+1);
		rep(j,1,m)a[i][j]=str[j]=='o'?-1:str[j]=='x'?0:1;
	}
	if(dir=='^'||dir=='v'){rep(j,1,m)rep(i,1,n)s[i][j]=s[i-1][j]+(!a[i][j]);}
	else {rep(i,1,n)rep(j,1,m)s[i][j]=s[i][j-1]+(!a[i][j]);}
	if(dir=='^'){rep(i,1,n)rep(j,1,m)if(!~a[i][j]&&s[i][j])return puts("GG"),0;}
	else if(dir=='v'){rep(i,1,n)rep(j,1,m)if(!~a[i][j]&&s[n][j]^s[i-1][j])return puts("GG"),0;}
	else if(dir=='<'){rep(i,1,n)rep(j,1,m)if(!~a[i][j]&&s[i][j])return puts("GG"),0;}
	else {rep(i,1,n)rep(j,1,m)if(!~a[i][j]&&s[i][m]^s[i][j-1])return puts("GG"),0;}
	puts("OK");
}