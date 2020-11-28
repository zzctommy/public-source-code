#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}

#define N 100005
char str[N];
LL ans=2;
int n,rt[N<<1];
struct SAM{

static const int S=N<<1;
int mxlen[S],link[S],trans[S][26],tot,to[N];
int q[S],t[N];
SAM(){
	memset(trans,0,sizeof(trans));
	tot=1;
	memset(link,0,sizeof(link));
	memset(mxlen,0,sizeof(mxlen));
}
int extend(int c,int lst){
	int p=lst,np=++tot;mxlen[np]=mxlen[p]+1;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
void rsort(){
	for(int i=0;i<=n;++i)t[i]=0;
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=n;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
}

}sam[2];

int fa[20][N<<1],lg[N<<1],pw[30],dep[N<<1],rev[N<<1],dfn[N<<1],tmr;
void init_lca(){
	lg[0]=-1;for(int i=1;i<=n<<1;++i)lg[i]=lg[i>>1]+1;
	pw[0]=1;for(int i=1;i<=20;++i)pw[i]=pw[i-1]<<1;
	for(int i=1;i<=lg[n<<1];++i)
		for(int j=1;j<=n<<1;++j)
			fa[i][j]=fa[i-1][fa[i-1][j]];
}
int LCA(int x,int y){
	if(!x||!y)return 0;
	if(dep[x]<dep[y])x^=y^=x^=y;
	int delta=dep[x]-dep[y];
	for(int i=19;i>=0;--i)if(delta>>i&1)x=fa[i][x];
	if(x==y)return x;
	for(int i=19;i>=0;--i)if(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
vector<int>e[N<<1];
void dfs(int u){
	rev[dfn[u]=++tmr]=u;
	for(int v:e[u])fa[0][v]=u,dep[v]=dep[u]+1,dfs(v);
}
struct SegmentTree{

static const int T=(N<<1)*40;
int ls[T],rs[T],tot,L[T],R[T];
LL val[T];
SegmentTree(){
	memset(ls,0,sizeof(ls));
	memset(rs,0,sizeof(rs));
	memset(val,0,sizeof(val));
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
	tot=0;
}
void pushup(int p){
	val[p]=val[ls[p]]+val[rs[p]]-sam[1].mxlen[LCA(rev[R[ls[p]]],rev[L[rs[p]]])];
	L[p]=ls[p]?L[ls[p]]:L[rs[p]];
	R[p]=rs[p]?R[rs[p]]:R[ls[p]];
}
void update(int&p,int pos,int k,int l=1,int r=n<<1){
	if(!p)p=++tot;
	int mid=(l+r)>>1;
	if(l==r){
		L[p]=R[p]=pos,val[p]=sam[1].mxlen[rev[pos]];
		return;
	}
	if(pos<=mid)update(ls[p],pos,k,l,mid);
	else update(rs[p],pos,k,mid+1,r);
	pushup(p);
}
int merge(int x,int y,int l=1,int r=n<<1){
	if(!x||!y)return x|y;
	int mid=(l+r)>>1,p=++tot;
	ls[p]=merge(ls[x],ls[y],l,mid);
	rs[p]=merge(rs[x],rs[y],mid+1,r);
	return pushup(p),p;
}

}seg;


signed main(){
	scanf("%s",str+1),n=strlen(str+1);
	for(int i=1,lst=1;i<=n;++i){
		sam[0].to[i]=lst=sam[0].extend(str[i]-'a',lst);
		if(i==n-1)for(int i=1;i<=sam[0].tot;++i)ans+=sam[0].mxlen[i]-sam[0].mxlen[sam[0].link[i]];
	}
	for(int i=n,lst=1;i>=1;--i){
		sam[1].to[i]=lst=sam[1].extend(str[i]-'a',lst);
		if(i==2)for(int i=1;i<=sam[1].tot;++i)ans+=sam[1].mxlen[i]-sam[1].mxlen[sam[1].link[i]];
	}
	for(int i=1;i<=sam[0].tot;++i)ans+=sam[0].mxlen[i]-sam[0].mxlen[sam[0].link[i]];

	sam[0].rsort();
	for(int i=2;i<=sam[1].tot;++i)e[sam[1].link[i]].pb(i);
	dfs(1),init_lca();
	for(int i=1;i<=n-2;++i)
		seg.update(rt[sam[0].to[i]],dfn[sam[1].to[i+2]],1);
	
	for(int i=sam[0].tot;i>=1;--i){
		int u=sam[0].q[i];
		rt[sam[0].link[u]]=seg.merge(rt[sam[0].link[u]],rt[u]);
	}
		
	for(int i=1;i<=sam[0].tot;++i)
		ans+=1ll*(sam[0].mxlen[i]-sam[0].mxlen[sam[0].link[i]])*seg.val[rt[i]];
	printf("%lld\n",ans);
	return 0;
}