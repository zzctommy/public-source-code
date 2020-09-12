#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int long long
#define rint register int
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100010;
int n,p,a[N],now,ans[N];
priority_queue<pair<int,int> >q;
queue<int>qu;
set<int>s;
signed main() {
	n=rd(),p=rd();
	for(rint i=1;i<=n;++i)q.push(make_pair(-rd(),-i));
	for(rint i=1;i<=n;++i) {
		if(qu.empty()&&s.empty())now=-q.top().first;
		now+=p;
		while(!q.empty()&&-q.top().first<=now) {
			if(qu.empty()||-q.top().second<qu.back())qu.push(-q.top().second);
			else s.insert(-q.top().second);
			q.pop();
		}
		ans[qu.front()]=now,qu.pop();
		if(qu.empty()&&!s.empty())qu.push(*s.begin()),s.erase(s.begin());
	}
	for(rint i=1;i<=n;++i)printf("%lld ",ans[i]);
	return 0;
} 