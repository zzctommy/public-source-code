#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int M=300010;
const int N=M<<1;
int dst[N],ls[N],rs[N],tot;
LL val[N];
int n,m,Fa[N],rt[N],len[N],son[N];
LL ans;
int merge(int x,int y) {
	if(!x||!y)return x|y;
	if(val[x]<val[y])swap(x,y);
	rs[x]=merge(rs[x],y);
	if(dst[ls[x]]<dst[rs[x]])swap(ls[x],rs[x]);
	dst[x]=dst[rs[x]]+1;
	return x;
}
signed main() {
	n=rd(),m=rd();
	for(int i=2;i<=n+m;++i)
		Fa[i]=rd(),len[i]=rd(),++son[Fa[i]],ans+=len[i];
	for(int i=n+m;i>1;--i) {
		LL L=0,R=0;
		if(i<=n) {
			while(--son[i])rt[i]=merge(ls[rt[i]],rs[rt[i]]);
			R=val[rt[i]],rt[i]=merge(ls[rt[i]],rs[rt[i]]);
			L=val[rt[i]],rt[i]=merge(ls[rt[i]],rs[rt[i]]);
		}
		++tot,val[tot]=L+len[i];
		rt[i]=merge(rt[i],tot);
		++tot,val[tot]=R+len[i];
		rt[i]=merge(rt[i],tot);
		rt[Fa[i]]=merge(rt[Fa[i]],rt[i]);
	}
	while(son[1]--)rt[1]=merge(ls[rt[1]],rs[rt[1]]);
	while(rt[1])ans-=val[rt[1]],rt[1]=merge(ls[rt[1]],rs[rt[1]]);
	printf("%lld\n",ans);
	return 0;
}