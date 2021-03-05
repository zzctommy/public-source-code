//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
typedef double db;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 100005
const db eps=1e-6;
int n,a[N],s,t;
db ans;
bool check(db m){
	static int q[N],H,T;
	static db b[N]={0};
	for(int i=1;i<=n;++i)b[i]=1.*a[i]-m+b[i-1];
	H=1,T=0;
	for(int i=1;i<=n;++i){
		if(i>=s){
			while(H<=T&&b[q[T]]>b[i-s])--T;
			q[++T]=i-s;
		}
		while(H<=T&&i-q[H]>t)++H;
		if(H<=T){if(b[i]-b[q[H]]>-1e-9)return 1;}
	}
	return 0;
}
signed main(){
	n=read(),s=read(),t=read();
	for(int i=1;i<=n;++i)a[i]=read();
	db l=-10000,r=10000;
	while(r-l>eps){
		db mid=(l+r)/2;
		if(check(mid))ans=mid,l=mid;
		else r=mid;
	}
	printf("%.3lf\n",ans);
	return 0;
}