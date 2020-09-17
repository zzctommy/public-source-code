#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
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
const int N=500005;
int n,cnt,ans[N],stk[N],top;
struct node {
	int id,p;
}a[N];
inline bool cmp(const node&a,const node&b){return a.p!=b.p?a.p>b.p:a.id<b.id;}
void Main() {
	n=rd(),cnt=0;
	for(int i=1;i<=n;++i){
		a[i].id=i,a[i].p=rd();
	}
	stk[top=1]=n+1;
	for(int i=1;i<=n;++i) {
		while(stk[top]<=i)--top;
		if(a[i].p>stk[top])return puts("-1"),void();
		if(~a[i].p)stk[++top]=a[i].p;
	}
	for(int i=1;i<=n;++i)if(!~a[i].p)a[i].p=i+1;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)ans[a[i].id]=n-i+1;
	for(int i=1;i<=n;++i)printf("%d ",ans[i]);
	puts("");
}
signed main() {
	for(int T=rd();T;--T)Main();
}
