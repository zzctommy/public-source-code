#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
LL n;
int y,m,d;
const int y4=1461;
const int y100=36524;
const int y400=146097;
int mon[]={-1,31,0,31,30,31,30,31,31,30,31,30,31};
void run1(int&d,int&m,int&y,int n){
	while(n>mon[m]){
		n-=mon[m],++m;
		if(m==2){
			if(y<0)mon[2]=-y%4==1?29:28;
			else {
				if(y<=1582)mon[2]=y%4==0?29:28;
				else{
					if(y%400==0)mon[2]=29;
					else if(y%4==0&&y%100!=0)mon[2]=29;
					else mon[2]=28;
				}
			}
		}
		if(m==13)m=1,++y;
		if(!y)++y;
	}
	d=n;
}
void run2(int&d,int&m,int&y,int n){
	static int cnt;
	cnt=1;
	while(cnt<=n){
		++cnt,++d;
		if(d==mon[m]+1)++m,d=1;
		if(m==2){
			if(y<0)mon[2]=-y%4==1?29:28;
			else {
				if(y<=1582)mon[2]=y%4==0?29:28;
				else{
					if(y%400==0)mon[2]=29;
					else if(y%4==0&&y%100!=0)mon[2]=29;
					else mon[2]=28;
				}
			}
		}
		if(m==13)m=1,++y;
		if(!y)++y;
	}
}
void Main(){
	scanf("%lld",&n);
	LL tmp=n;
	y=-4713,m=1,d=1;
	if(n<=2299160){
		y+=4*(n/y4);
		n-=(n/y4)*y4;
		if(y>=0)++y;
		m=1,d=1;
		run1(d,m,y,n+1);
		if(y<0)printf("%d %d %d BC\n",d,m,-y);
		else printf("%d %d %d\n",d,m,y);
		return;
	}
	n-=2299161;
	y=1582,m=10,d=15;
	if(n<=6653){
		run2(d,m,y,n);
		printf("%d %d %d\n",d,m,y);
		return;
	}
	n-=6653,y=1601,m=1,d=1;
	y+=400*(n/y400);
	n-=y400*(n/y400);
	if(n==y400-1){
		y+=400-1,m=12,d=31;
		printf("%d %d %d\n",d,m,y);
		return;
	}
	y+=100*(n/y100);
	n-=y100*(n/y100);
	y+=4*(n/y4);
	n-=y4*(n/y4);
	run1(d,m,y,n+1);
//	if(tmp==913512802)cerr<<d<<' '<<m<<' '<<y<<'\n';
	printf("%d %d %d\n",d,m,y);
}
signed main(){
	for(int T=read();T;--T)Main();
}