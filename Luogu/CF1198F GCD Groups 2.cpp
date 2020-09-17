#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200005;
int n,ans[N];
struct node {
	int x,id;
}a[N];
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i].x=read(),a[i].id=i;
	clock_t st=clock();
	while(0.45>1.*(clock()-st)/CLOCKS_PER_SEC) {
		random_shuffle(a+1,a+n+1);
		int x=0,y=0;
		for(int i=1;i<=n;++i) {
			if(!x){ans[a[i].id]=1,x=a[i].x;continue;}
			int g=gcd(a[i].x,x);
			if(a[i].x%x==0)y=gcd(a[i].x,y),ans[a[i].id]=2;
			else x=g,ans[a[i].id]=1;
		}
		if(x==1&&y==1){puts("YES");for(int i=1;i<=n;++i)printf("%d ",ans[i]);return puts(""),0;}
	}
	puts("NO");
}
