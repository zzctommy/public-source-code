#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
int n,a[N],tr[N];
LL now;
vector<int>v[N];
vector<LL>ans; 
void add(int x,int d) {
	for(int i=x;i<=n+2;i+=i&-i)tr[i]+=d;
}
int ask(int x) {
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=tr[i];
	return res;
}
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)v[a[i]=rd()].pb(i);
	for(int i=1;i<=n;++i)now+=ask(n-a[i]+1),add(n-a[i]+2,1);
	memset(tr,0,sizeof(tr));
	for(int i:v[n])add(i,1);
	for(int i=n-1;i>=0;--i) {
		for(int j:v[i])now-=ask(j);
		for(int j:v[i])add(j,1);
		ans.pb(now);
	}
	reverse(ans.begin(),ans.end());
	for(LL i:ans)printf("%lld\n",i);
	return 0;
}
