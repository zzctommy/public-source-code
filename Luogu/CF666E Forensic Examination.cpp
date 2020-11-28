#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
#define pb(x) push_back(x)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 550005
int n,m;
char str[N];

namespace seg{

#define T (N*21*2)
int ls[T],rs[T],tot;
struct node{
	int mx,id;
	node(){mx=id=0;}
	node(int mx_,int id_){mx=mx_,id=id_;}
	inline bool operator < (const node&t)const{return mx==t.mx?id>t.id:mx<t.mx;}
}v[T];
void pushup(int p){v[p]=max(v[ls[p]],v[rs[p]]);}
void update(int&p,int id,int l=1,int r=m){
	if(!p)p=++tot;
	if(l==r)return v[p]=node(++v[p].mx,id),void();
	int mid=(l+r)>>1;
	if(id<=mid)update(ls[p],id,l,mid);
	else update(rs[p],id,mid+1,r);
	pushup(p);
}
int merge(int x,int y,int l=1,int r=m){
	if(!x||!y)return x|y;
	if(l==r)return v[++tot]=node(v[x].mx+v[y].mx,v[x].id),tot;
	int mid=(l+r)>>1,p=++tot;
	ls[p]=merge(ls[x],ls[y],l,mid);
	rs[p]=merge(rs[x],rs[y],mid+1,r);
	return pushup(p),p;
}
node query(int p,int ql,int qr,int l=1,int r=m){
	if(!p)return node(0,0);
	if(ql<=l&&r<=qr)return v[p];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(ls[p],ql,qr,l,mid);
	if(mid<ql)return query(rs[p],ql,qr,mid+1,r);
	return max(query(ls[p],ql,qr,l,mid),query(rs[p],ql,qr,mid+1,r));
}
#undef T

}

namespace sam{

#define T (N<<1)
int trans[T][26],link[T],mxlen[T],tot=1,lst,to[N];
int fa[20][T],rt[T];
vector<int>e[T];
int extend(int c,int id,int index){
	if(trans[lst][c]){
		int p=lst,q=trans[lst][c];
		if(mxlen[p]+1==mxlen[q]){
			if(id)seg::update(rt[q],id);
			else to[index]=q;
			return q;
		}else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
			if(id)seg::update(rt[nq],id);
			else to[index]=nq;
			return nq;
		}
	}
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
	if(id)seg::update(rt[np],id);
	else to[index]=np;
	return np;
}
void insert(char*str,int id){
	lst=1;
	for(int i=0,n=strlen(str);i<n;++i)lst=extend(str[i]-'a',id,i);
}
void dfs(int u,int dep){
	for(int i=1;1<<i<=dep;++i)fa[i][u]=fa[i-1][fa[i-1][u]];
	for(int v:e[u])fa[0][v]=u,dfs(v,dep+1),rt[u]=seg::merge(rt[u],rt[v]);
}
void init(){
	for(int i=1;i<=tot;++i)e[link[i]].pb(i);
	dfs(1,1);
}
void solve(int l,int r,int pl,int pr){
	int u=to[pr-1];
	for(int i=19;i>=0;--i)if(mxlen[fa[i][u]]>=pr-pl+1)u=fa[i][u];
	seg::node tmp=seg::query(rt[u],l,r);
	if(tmp.id)printf("%d %d\n",tmp.id,tmp.mx);
	else printf("%d 0\n",l);
}
#undef T

}

signed main(){
	scanf("%s",str),n=strlen(str),sam::insert(str,0);
	m=read();
	for(int i=1;i<=m;++i)
		scanf("%s",str),sam::insert(str,i);
	sam::init();
	for(int q=read();q;--q){
		int l=read(),r=read(),pl=read(),pr=read();
		sam::solve(l,r,pl,pr);
	}
	return 0;
}