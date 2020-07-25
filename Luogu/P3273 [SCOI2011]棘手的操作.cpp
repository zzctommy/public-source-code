#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
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
const int N=300010;
const int inf=1e9+7;
int n,m,a[N],root;
int TAG_ALL;
struct Leftist_Tree {
	int tag[N],val[N],fa[N],Fa[N],ls[N],rs[N],dst[N],tot;
	Leftist_Tree(){tot=0;}
	void init(const int &n,const int *a) {
		for(int i=0;i<=n;++i) {
			val[i]=a[i];
			Fa[i]=fa[i]=i;
			tag[i]=ls[i]=rs[i]=dst[i]=0;
		}
		tot=n;
	}
	void pushdown(int x) {
		if(!tag[x])return;
		val[ls[x]]+=tag[x],val[rs[x]]+=tag[x];
		tag[ls[x]]+=tag[x],tag[rs[x]]+=tag[x];
		tag[x]=0;
	}
	int merge(int x,int y) {
		if(!x||!y)return x|y;
		if(val[x]<val[y])swap(x,y);
		pushdown(x);
		rs[x]=merge(rs[x],y),Fa[rs[x]]=fa[rs[x]]=x;
		if(dst[ls[x]]<dst[rs[x]])swap(ls[x],rs[x]);
		dst[x]=dst[rs[x]]+1;
		return x;
	}
	int build(int n) {
		queue<int>q;
		for(int i=1;i<=n;++i)q.push(i);
		while(!q.empty()) {
			if(q.size()==1)break;
			int x=q.front();q.pop();
			int y=q.front();q.pop();
			q.push(merge(x,y));
		}
		return q.front();
	}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	int getval(int x) {
		int res=val[x];
		while(Fa[x]!=x)x=Fa[x],res+=tag[x];
		return res;
	}
	int New(int x) {
		++tot;
		val[tot]=x;
		fa[tot]=Fa[tot]=tot;
		ls[tot]=rs[tot]=dst[tot]=tag[tot]=0;
		return tot;
	}
	int insert(int v,int x) {
		return merge(New(v),x);
	}
	int pop(int x) {
		pushdown(x);
		fa[ls[x]]=Fa[ls[x]]=ls[x];
		fa[rs[x]]=Fa[rs[x]]=rs[x];
		fa[x]=merge(ls[x],rs[x]);
		ls[x]=rs[x]=dst[x]=0;
		val[x]=-inf;
		return fa[x];
	}
	int del_node(int x) {
		if(x==Fa[x])return pop(x);
		int zkyAKIOI=find(x);
		pushdown(x);
		int u=merge(ls[x],rs[x]),fx=Fa[x];
		fa[u]=Fa[u]=fx;
		if(ls[fx]==x)ls[fx]=u;
		else rs[fx]=u;
		ls[x]=rs[x]=dst[x]=0;
		val[x]=-inf;
		x=fx;
		while(x!=Fa[x]) {
			pushdown(x);
			if(dst[ls[x]]<dst[rs[x]])swap(ls[x],rs[x]);
			if(dst[x]==dst[rs[x]]+1)return zkyAKIOI;
			dst[x]=dst[rs[x]]+1,x=Fa[x];
		}
		return zkyAKIOI;
	}
}H[2];
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	H[0].init(n,a),H[1].init(n,a);
	root=H[1].build(n);
	for(m=rd();m;--m) {
		char opt[5];int x,y;
		scanf("%s",opt);
		if(!strcmp(opt,"U")) {
			x=rd(),y=rd();
			x=H[0].find(x),y=H[0].find(y);
			if(x==y)continue;
			root=H[1].del_node(H[0].merge(x,y)==x?y:x);
		} else if(!strcmp(opt,"A1")) {
			x=rd(),y=rd();
			int cnAKIOI=H[0].getval(x)+y;
			int whkAKIOI=H[0].find(x);
			int fyyAKIOI=H[0].del_node(x);
			H[0].val[x]=cnAKIOI;
			H[0].fa[x]=H[0].Fa[x]=x;
			x=H[0].merge(x,fyyAKIOI);
			root=H[1].del_node(whkAKIOI);
			H[1].val[x]=H[0].val[x];
			H[1].fa[x]=H[1].Fa[x]=x;
			root=H[1].merge(root,x);
		} else if(!strcmp(opt,"A2")) {
			x=rd(),y=rd();
			x=H[0].find(x);
			H[0].tag[x]+=y;
			H[0].val[x]+=y;
			root=H[1].del_node(x);
			H[1].val[x]=H[0].val[x];
			H[1].fa[x]=H[1].Fa[x]=x;
			root=H[1].merge(root,x);
		} else if(!strcmp(opt,"A3"))TAG_ALL+=rd();
		else if(!strcmp(opt,"F1"))printf("%d\n",H[0].getval(rd())+TAG_ALL);
		else if(!strcmp(opt,"F2"))printf("%d\n",H[0].val[H[0].find(rd())]+TAG_ALL);
		else if(!strcmp(opt,"F3"))printf("%d\n",H[1].val[root]+TAG_ALL);
	}
	return 0;
}