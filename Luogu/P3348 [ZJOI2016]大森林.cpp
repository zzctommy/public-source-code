#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=100005;
const int M=200005;
int n,m,nq,q,ans[M];
int id[M],tot,rel,vir,L[M],R[M];
int fa[M],sum[M],val[M],ch[M][2];
struct node{
	int pos,id,x,y;
	node(){pos=id=x=y=0;}
	node(int pos_,int id_,int x_,int y_){pos=pos_,id=id_,x=x_,y=y_;}
	inline bool operator < (const node&t)const{return pos!=t.pos?pos<t.pos:id<t.id;}
}v[M<<1];
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){
	sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x];
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;fa[y]=x,fa[x]=z;
	pushup(y);
}
void splay(int x){
	while(nroot(x)){
		int y=fa[x],z=fa[y];
		if(nroot(y))rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
		rotate(x);
	}
	pushup(x);
}
int access(int x){
	int y=0;
	for(;x;x=fa[y=x])
		splay(x),ch[x][1]=y,pushup(x);
	return y;
}
void link(int x,int y){
	splay(x),fa[x]=y;
}
void cutfa(int x){
	access(x),splay(x),ch[x][0]=fa[ch[x][0]]=0,pushup(x);
}
int query(int x,int y){
	int res=0,lca;
	access(x),splay(x),res+=sum[x];
	lca=access(y),splay(y),res+=sum[y];
	access(lca),splay(lca),res-=sum[lca]<<1;
	return res;
}
signed main(){
	n=read(),m=read();
	id[rel=++tot]=1,vir=++tot,val[1]=1,L[1]=1,R[1]=n,link(2,1);
	rep(i,1,m){
		int opt=read(),x,y,z;
		if(opt==0){
			x=read(),y=read();
			id[++rel]=++tot,link(tot,vir),val[tot]=1,L[rel]=x,R[rel]=y;
		}else if(opt==1){
			x=read(),y=read(),z=read();
			ckmax(x,L[z]),ckmin(y,R[z]);
			if(x>y)continue;
			++tot,link(tot,vir);
			++q,v[q]=node(x,i-m,tot,id[z]);
			++q,v[q]=node(y+1,i-m,tot,vir);
			vir=tot;
		}else{
			x=read(),y=read(),z=read();
			++q,v[q]=node(x,++nq,id[y],id[z]);
		}
	}
	sort(v+1,v+q+1);
	for(int i=1;i<=q;++i){
		if(v[i].id<0)cutfa(v[i].x),link(v[i].x,v[i].y);
		else ans[v[i].id]=query(v[i].x,v[i].y);
	}
	rep(i,1,nq)printf("%d\n",ans[i]);
	return 0;
}