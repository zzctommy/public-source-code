#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
const int N=109;
int n,m,a[N],mx,ans;
priority_queue<int,vector<int>,greater<int> >q;
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),mx=max(mx,a[i]),q.push(a[i]);
	for(int i=1;i<=m;++i) {
		int x=q.top();q.pop();q.push(x+1);
	}
	while(!q.empty())ans=max(ans,q.top()),q.pop();
	printf("%d %d\n",ans,mx+m);
	return 0;
}