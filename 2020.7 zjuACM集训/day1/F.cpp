#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1e5+10;
int n,x[N],y[N],p;
bool check(int k) {
	unordered_map<double,int>mp;
	int sum=0;
	for(rint i=1;i<=n;++i) {
		if(i==k)continue;
		double l=(y[i]-y[k])/(double)(x[i]-x[k]);
		++mp[l],sum=max(sum,mp[l]);
	}
	++sum;
	return sum>=p;
}
signed main() {
	srand(787);
	n=rd(),p=rd();
	p=ceil(1.0*n*p/100);
	for(rint i=1;i<=n;++i)x[i]=rd(),y[i]=rd();
	int nowtime=clock();
	if(check(rand()%n+1))return puts("possible"),0;
	int once=clock()-nowtime;
	while(nowtime<990-once) {
		int x=rand()*rand()%n+1;
		if(check(x))return puts("possible"),0;
		nowtime=clock();
	}
	puts("impossible");
	return 0;
}
