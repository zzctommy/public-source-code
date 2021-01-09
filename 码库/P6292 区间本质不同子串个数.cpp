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

template<int L>
struct Suffix_Automation{

#define N (L+5)
#define S (N<<1)

int trans[S][26],tot,mxlen[S],link[S],to[S];
int q[S],t[S],rt[S];

int New(){++tot;memset(trans[tot],0,sizeof(trans[tot]));mxlen[tot]=link[tot]=0;return tot;}

Suffix_Automation(){tot=0,New();}
void clear(){tot=0;New();}

int extend(int c,int lst,int id,int op=0){
	int p=lst,np=New();mxlen[np]=mxlen[p]+1;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
void insert(char*str,int op=0){
	int n=strlen(str);
	for(int i=0,lst=1;i<n;++i)lst=extend(str[i]-'a',lst,i+1),to[i+1]=lst;
}
void rsort(){
	for(int i=1;i<=tot;++i)t[i]=0;
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=tot;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
}
LL distinct_substring(){
	LL res=0;
	for(int i=1;i<=tot;++i)res+=mxlen[i]-mxlen[link[i]];
	return res;
}
#undef S
#undef N

};

template<int N,class typ>
struct SegmentTree{

#define T (N<<2)
typ sum[T],mx[T],tag[T];
#define lc (p<<1)
#define rc (p<<1|1)
void pushup(int p){sum[p]=sum[lc]+sum[rc],mx[p]=max(mx[lc],mx[rc]);}
void clear(int p=1,int l=1,int r=N){
	sum[p]=mx[p]=tag[p]=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	clear(lc,l,mid),clear(rc,mid+1,r);
}
void build(typ*a,int p=1,int l=1,int r=N){
	sum[p]=mx[p]=tag[p]=0;
	if(l==r){
		sum[p]=mx[p]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(a,lc,l,mid),build(a,rc,mid+1,r);
	pushup(p);
}
void pushdown(int p,int l,int r){
	if(tag[p]){
		int mid=(l+r)>>1;
		tag[lc]+=tag[p],tag[rc]+=tag[p];
		sum[lc]+=tag[p]*(mid-l+1),sum[rc]+=tag[p]*(r-mid);
		mx[lc]+=tag[p],mx[rc]+=tag[p];
		tag[p]=0;
	}
}
void update(int ql,int qr,typ k,int p=1,int l=1,int r=N){
	if(ql<=l&&r<=qr){
		sum[p]+=k*(r-l+1),mx[p]+=k,tag[p]+=k;
		return;
	}
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid)update(ql,qr,k,lc,l,mid);
	if(mid<qr)update(ql,qr,k,rc,mid+1,r);
	pushup(p);
}
typ query_sum(int ql,int qr,int p=1,int l=1,int r=N){
	if(ql<=l&&r<=qr)return sum[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(qr<=mid)return query_sum(ql,qr,lc,l,mid);
	if(mid<ql)return query_sum(ql,qr,rc,mid+1,r);
	return query_sum(ql,qr,lc,l,mid)+query_sum(ql,qr,rc,mid+1,r);
}
typ query_max(int ql,int qr,int p=1,int l=1,int r=N){
	if(ql<=l&&r<=qr)return mx[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(qr<=mid)return query_max(ql,qr,lc,l,mid);
	if(mid<ql)return query_max(ql,qr,rc,mid+1,r);
	return max(query_max(ql,qr,lc,l,mid),query_max(ql,qr,rc,mid+1,r));
}

#undef lc
#undef rc
#undef T

};

template<int N>
struct Link_Cut_Tree{

static const int O=N+5;
int ch[O][2],fa[O],sum[O],val[O],id[O],tag[O];
bool fl[O];
Link_Cut_Tree(){
	memset(ch,0,sizeof(ch));
	memset(fa,0,sizeof(fa));
	memset(val,0,sizeof(val));
	memset(sum,0,sizeof(sum));
	memset(id,0,sizeof(id));
	memset(fl,0,sizeof(fl));
	memset(tag,0,sizeof(tag));
}
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){}
void addtag(int x,int d){
	val[x]=d,tag[x]=d;
}
void pushdown(int x){
	if(fl[x]){
		fl[x]^=1,fl[ch[x][0]]^=1,fl[ch[x][1]]^=1;
		swap(ch[x][0],ch[x][1]);
	}
	if(tag[x]){
		if(ch[x][0])addtag(ch[x][0],tag[x]);
		if(ch[x][1])addtag(ch[x][1],tag[x]);
		tag[x]=0;
	}
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;
	fa[y]=x,fa[x]=z;
	pushup(y);
}
void splay(int x){
	static int stk[O],top;
	int y=x,z;stk[top=1]=y;
	while(nroot(y))stk[++top]=y=fa[y];
	while(top)pushdown(stk[top--]);
	while(nroot(x)){
		y=fa[x],z=fa[y];
		if(nroot(y))rotate((ch[z][1]==y)^(ch[y][1]==x)?x:y);
		rotate(x);
	}
	pushup(x);
}
void access(int x){
	for(int y=0;x;x=fa[y=x])
		splay(x),ch[x][1]=y,pushup(x);
}
void makeroot(int x){
	access(x),splay(x),fl[x]^=1;
}
int findroot(int x){
	access(x),splay(x);
	while(ch[x][0])pushdown(x),x=ch[x][0];
	return splay(x),x;
}
void split(int x,int y){
	makeroot(x),access(y),splay(y);
}
void link(int x,int y,int op=0){
	if(op){
		makeroot(x);
		if(findroot(y)!=x)splay(y),fa[x]=y;
	}else makeroot(x),fa[x]=y;
}
void cut(int x,int y,int op=0){
	if(op){
		makeroot(x);
		if(findroot(y)==x&&fa[y]==x&&!ch[y][0])
			fa[y]=ch[x][1]=0;
	}else split(x,y),fa[x]=ch[y][0]=0,pushup(y);
}
int ask_sum(int x,int y){return split(x,y),sum[y];}
pair<int,int>ask_max(int x,int y){return split(x,y),mkp(val[id[y]],id[y]);}
};

/*第一次拉板子呢，有点激动.草草草错光了是什么鬼啊*/

const int N=200000;
int n,m;
LL ans[N+5];
char str[N+5];
vector<pair<int,int> >q[N+5];

Suffix_Automation<N>sam;
SegmentTree<N,LL>seg;
Link_Cut_Tree<N*2>lct;

void Newaccess(int x,int id){
	int y=0;
	for(;x;x=lct.fa[y=x]){
		lct.splay(x);
		int tmp=lct.val[x];
		if(tmp)seg.update(tmp-sam.mxlen[x]+1,tmp-sam.mxlen[lct.fa[x]],-1);
		lct.ch[x][1]=y;
	}
	lct.addtag(y,id),seg.update(1,id,1);
}

signed main(){
	scanf("%s%d",str+1,&m),n=strlen(str+1),sam.insert(str+1),seg.clear();
	for(int i=1;i<=sam.tot;++i)lct.fa[i]=sam.link[i];
	for(int i=1;i<=m;++i){
		int l=read(),r=read();
		q[r].pb(mkp(l,i));
	}
	for(int i=1;i<=n;++i){
		Newaccess(sam.to[i],i);
		for(int j=0;j<sz(q[i]);++j)
			ans[q[i][j].se]=seg.query_sum(q[i][j].fi,i);
	}
	for(int i=1;i<=m;++i)printf("%lld\n",ans[i]);
}