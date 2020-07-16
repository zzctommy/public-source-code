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
const int N=50010;
int n,a[N];
bool check(){
	for(int i=1;i<=n;i++)
		for(int j=i-1,k=i+1;j>0&&k<=n;j--,k++)
			if(a[i]*2==a[j]+a[k])return 0;
	return 1;
}
void solve(int st,int len) {
	if(st+len>n)return;
	vector<int>v;
	for(rint i=st;i<=n;i+=len)v.pb(a[i]);
	sort(v.begin(),v.end());int j=0;
	for(rint i=st+len;i<=n;i+=len*2,++j)a[i]=v[j];
	for(rint i=st;i<=n;i+=len*2,++j)a[i]=v[j];
	solve(st+len,len*2);solve(st,len*2);
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)a[i]=i;
	solve(1,1);
	for(rint i=1;i<=n;++i)printf("%d ",a[i]);
	return 0;
}
