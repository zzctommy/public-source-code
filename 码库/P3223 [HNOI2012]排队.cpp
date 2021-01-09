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
	while(!isdigit(ch)) {if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?x:-x;
}
const int base=1000000000;
const int limit=9;
struct bint {
	LL a[100000];
	bint(int x=0){a[a[0]=1]=x;}
	void rprint(LL x,int len){
		int d[20];d[0]=0;
		while(x)d[++d[0]]=x%10,x/=10;
		for(int i=d[0]+1;i<=len;++i)d[++d[0]]=0;
		for(int i=d[0];i;--i)putchar('0'+d[i]);
	}
	void print(char text=-1){
		for(int i=a[0];i;--i)rprint(a[i],i<a[0]?limit:1);
		if(~text)putchar(text);
	}
}A,B;
bint operator * (const bint&a,const int&b){
	bint res=a;
	for(int i=1;i<=res.a[0];++i)res.a[i]*=b;
	for(int i=1;i<=res.a[0];++i)if(res.a[i]>=base)res.a[i+1]+=res.a[i]/base,res.a[i]%=base;
	while(res.a[res.a[0]+1]){
		++res.a[0];
		if(res.a[res.a[0]]>=base)res.a[res.a[0]+1]+=res.a[res.a[0]]/base,res.a[res.a[0]]%=base;
	}
	return res;
}
bint operator - (const bint&a,const bint&b){
	bint res=a;
	for(int i=1;i<=res.a[0];++i){
		res.a[i]-=b.a[i];
		if(res.a[i]<0)res.a[i]+=base,--res.a[i+1];
	}
	while(res.a[0]>1&&!res.a[res.a[0]])--res.a[0];
	return res;
}
signed main(){
	int n=read(),m=read();
	if(n+4-m<=0)return puts("0"),0;
	A=1,B=2;
	for(int i=n+4-m;i<=n+3;++i)A=A*i;
	for(int i=1;i<=n+2;++i)A=A*i;
	for(int i=n+3-m;i<=n+2;++i)B=B*i;
	for(int i=1;i<=n+1;++i)B=B*i;
	(A-B).print('\n');
}
/*
20 10
4426611674116398910034411520000000
5 2
221760
*/