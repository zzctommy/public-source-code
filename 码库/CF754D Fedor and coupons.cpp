#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=300009;
int n,k,ans,L,R;
struct node {
	int l,r,id;
}a[N];
priority_queue<int,vector<int>,greater<int> >q;
bool cmp(const node&a,const node&b) {
	return a.l!=b.l?a.l<b.l:a.r<b.r;
}
signed main() {
	n=rd(),k=rd();
	for(int i=1;i<=n;++i)a[i].l=rd(),a[i].r=rd(),a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<k;++i)q.push(a[i].r);
	for(int i=k;i<=n;++i) {
		q.push(a[i].r);
		if(q.size()>k)q.pop();
		int t=q.top()-a[i].l+1;
		if(t>ans)ans=t,L=a[i].l,R=q.top();
	}
	printf("%d\n",ans);
	if(!ans)for(int i=1;i<=k;++i)printf("%d ",i);
	else for(int i=1,j=1;i<=n&&j<=k;++i)if(a[i].l<=L&&a[i].r>=R)printf("%d ",a[i].id),++j;
	return 0;
}