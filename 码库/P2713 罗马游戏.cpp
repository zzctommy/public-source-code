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
int rdc() {
	char ch=getchar();
	while(ch!='M'&&ch!='K')ch=getchar();
	return ch=='M';
}
const int N=1e6+10;
const int inf=1<<29;
int n,m;
int val[N],fa[N],dst[N],ls[N],rs[N];
int merge(int x,int y) {
	if(!x||!y)return x|y;
	if(val[x]>val[y]||(val[x]==val[y]&&x>y))swap(x,y);
	rs[x]=merge(rs[x],y),fa[rs[x]]=x;
	if(dst[ls[x]]<dst[rs[x]])swap(ls[x],rs[x]);
	dst[x]=dst[rs[x]]+1;
	return x;
}
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
void del(int x) {
	val[x]=inf;
	fa[ls[x]]=ls[x],fa[rs[x]]=rs[x];
	fa[x]=merge(ls[x],rs[x]);
	dst[x]=ls[x]=rs[x]=0;
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i)val[i]=rd(),fa[i]=i;
	m=rd();
	while(m--) {
		int opt=rdc(),x,y;
		if(opt==1) {
			x=rd(),y=rd();
			int tx=find(x),ty=find(y);
			if(tx==ty||val[x]==inf||val[y]==inf)continue;
			merge(tx,ty);
		} else {
			x=rd();
			if(val[x]==inf) {puts("0");continue;}
			int tx=find(x);
			printf("%d\n",val[tx]);
			del(tx);
		}
	}
	return 0;
}
