#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int a[9][9];
char s[9];
int check(int x,int y) {
	if(a[x-1][y]==1&&a[x+1][y]==1)return 1;
	if(a[x+1][y]==1&&a[x+2][y]==1)return 1;
	if(a[x-1][y]==1&&a[x-2][y]==1)return 1;

	if(a[x][y-1]==1&&a[x][y+1]==1)return 1;
	if(a[x][y-1]==1&&a[x][y-2]==1)return 1;
	if(a[x][y+1]==1&&a[x][y+2]==1)return 1;

	if(a[x-1][y-1]==1&&a[x+1][y+1]==1)return 1;
	if(a[x-2][y-2]==1&&a[x-1][y-1]==1)return 1;
	if(a[x+1][y+1]==1&&a[x+2][y+2]==1)return 1;

	if(a[x+1][y-1]==1&&a[x+2][y-2]==1)return 1;
	if(a[x-1][y+1]==1&&a[x+1][y-1]==1)return 1;
	if(a[x-2][y+2]==1&&a[x-1][y+1]==1)return 1;

	return 0;
}
signed main() {
	for(int i=2;i<=5;++i) {
		scanf("%s",s+2);
		for(int j=2;j<=5;++j)
			if(s[j]=='x')a[i][j]=1;
			else if(s[j]=='.')a[i][j]=0;
			else a[i][j]=-1;
	}
	for(int i=2;i<=5;++i)for(int j=2;j<=5;++j)if(!a[i][j]&&check(i,j))return puts("YES"),0;
	puts("NO");return 0;
}