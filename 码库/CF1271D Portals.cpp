#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1000009;
int n,m,k,a[N],b[N],c[N],to[N],ans;
vector<int>v[N];
struct Heap {
	int siz,a[N];
	Heap(){siz=0;memset(a,0,sizeof(a));}
	void push(int x) {
		a[++siz]=x;int now=siz;
		while(now>1&&a[now]<a[now>>1])swap(a[now],a[now>>1]),now>>=1;
	}
	void pop() {
		a[1]=a[siz--];int now=1;
		while((now<<1)<=siz) {
			int nex=a[now<<1]<a[now<<1|1]?now<<1:now<<1|1;
			if(a[now]<=a[nex])return;
			swap(a[now],a[nex]),now=nex;
		}
	}
	int top(){return a[1];}
	bool empty(){return !siz;}
}h;
inline bool cmp(const int &a,const int &b) {return c[a]>c[b];}
int main(){
	n=rd(),m=rd(),k=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),b[i]=rd(),c[i]=rd(),to[i]=i;
	for(int i=1;i<=m;++i) {
		int u=rd(),v=rd();
		if(to[v]<u)to[v]=u;
	}
	for(int i=1;i<=n;++i)v[to[i]].pb(i);
	for(int i=1;i<=n;++i)sort(v[i].begin(),v[i].end(),cmp);
	for(int i=1;i<=n;++i) {
		while(!h.empty()&&k<a[i])++k,ans-=h.top(),h.pop();
		if(k<a[i])return puts("-1"),0;
		k+=b[i];
		for(int j:v[i])
			if(k)h.push(c[j]),--k,ans+=c[j];
			else if(!h.empty()&&h.top()<c[j])ans+=c[j]-h.top(),h.pop(),h.push(c[j]);
			else break;
	}
	printf("%d\n",ans);
	return 0;
}