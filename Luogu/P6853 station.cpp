#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=4005;
int n,m,need;
vector<int>a;
void f2(){
	printf("2 %d %d\n",m+1,m+2);
	printf("2 %d %d\n",m+2,m+3);
	a.pb(m+1),a.pb(m+3);
	need-=2,m+=3;
}
void f3(){
	printf("2 %d %d\n",m+1,m+4);
	printf("2 %d %d\n",m+2,m+4);
	printf("2 %d %d\n",m+3,m+4);
	a.pb(m+1),a.pb(m+2),a.pb(m+3);
	need-=3,m+=4;
}
signed main(){
	n=read(),need=n-1;
	if((n-1)%6==0)printf("%d\n",(n-1)/6*5);
	else if((n-1)%6==1)printf("%d\n",(n-8)/6*5+10),f2(),f2(),f3();
	else if((n-1)%6==2)printf("%d\n",(n-3)/6*5+3),f2();
	else if((n-1)%6==3)printf("%d\n",(n-4)/6*5+4),f3();
	else if((n-1)%6==4)printf("%d\n",(n-5)/6*5+6),f2(),f2();
	else if((n-1)%6==5)printf("%d\n",(n-6)/6*5+7),f2(),f3();
////	cout<<need<<' '<<m<<endl;
	for(int i=1;i<=need;i+=6,m+=5){
		printf("2 %d %d\n",m+1,m+4);
		printf("2 %d %d\n",m+1,m+5);
		printf("2 %d %d\n",m+2,m+4);
		printf("2 %d %d\n",m+2,m+5);
		printf("2 %d %d\n",m+3,m+4);
		printf("2 %d %d\n",m+3,m+5);
		a.pb(m+1),a.pb(m+2),a.pb(m+3);
	}
	printf("%d ",(int)a.size());
	for(int i:a)printf("%d ",i);
	return 0;
}