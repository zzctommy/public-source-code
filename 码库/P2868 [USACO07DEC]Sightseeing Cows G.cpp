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
const int N=1010;
const int M=5010;
const double eps=1e-4;
int n,m,F[N];
int head[N],num_edge;
double dst[N];
int inq[N],num[N];
struct edge {
	int nxt,to,tim;
	double val;
}e[M];
void addedge(int from,int to,int val) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	e[num_edge].tim=val;
	head[from]=num_edge;
}
bool spfa() {
	for(rint i=1;i<=n;++i)dst[i]=1e12,inq[i]=0,num[i]=0;
	queue<int>q;q.push(1);
	num[1]=1,inq[1]=1,dst[1]=0;
	while(!q.empty()) {
		int u=q.front();q.pop(),inq[u]=0;
		for(rint i=head[u];i;i=e[i].nxt) {
			int v=e[i].to;
			if(dst[v]>dst[u]+e[i].val) {
				dst[v]=dst[u]+e[i].val;
				++num[v];
				if(num[v]>n)return 1;
				if(!inq[v])inq[v]=1,q.push(v);
			}
		}
	}
	return 0;
}
bool check(double k) {
	for(rint i=1;i<=m;++i)e[i].val=1.0*k*e[i].tim-F[e[i].to]-eps;
	return spfa();
} 
signed main() {
	n=rd(),m=rd();
	for(rint i=1;i<=n;++i)F[i]=rd();
	for(rint i=1;i<=m;++i) {
		int x=rd(),y=rd(),z=rd();
		addedge(x,y,z);
	}
	double l=0,r=1e6;
	while(r-l>eps) {
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.2lf\n",l);
	return 0;
}
