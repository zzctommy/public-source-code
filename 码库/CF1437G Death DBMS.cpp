#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
//Data
#define N 3000005
#define inf 0x3f3f3f3f
int n,m,tot=1,trie[N][26],to[N],strval[N];
int fa[N],val[N],ch[N][2],mx[N],stk[N],top;
bool rev[N];
multiset<int,greater<int> >s[N];
//ACAM
void insert(char*str,int id){
	int u=1,len=strlen(str);
	for(int i=0;i<len;++i){
		int c=str[i]-'a';
		if(!trie[u][c])trie[u][c]=++tot;
		u=trie[u][c];
	}
	val[u]=0,to[id]=u;
}
void build_fail(){
	queue<int>q;
	for(int i=0;i<26;++i)
		if(trie[1][i])q.push(trie[1][i]),fa[trie[1][i]]=1;
		else trie[1][i]=1;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;++i)
			if(trie[u][i])fa[trie[u][i]]=trie[fa[u]][i],q.push(trie[u][i]);
			else trie[u][i]=trie[fa[u]][i];
	}
	for(int i=1;i<=n;++i)s[to[i]].insert(0);
}

//LCT
bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void pushup(int x){
	mx[x]=val[x];
	if(ch[x][0])mx[x]=max(mx[x],mx[ch[x][0]]);
	if(ch[x][1])mx[x]=max(mx[x],mx[ch[x][1]]);
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][!k];
	if(nroot(y))ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y,ch[y][k]=w;
	if(w)fa[w]=y;fa[y]=x,fa[x]=z;
	pushup(y);
}
void pushdown(int x){if(rev[x])swap(ch[x][0],ch[x][1]),rev[ch[x][0]]^=1,rev[ch[x][1]]^=1,rev[x]=0;}
void splay(int x){
	int y=x,z;stk[top=1]=x;
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
void makeroot(int x){access(x),splay(x),rev[x]^=1;}
void split(int x,int y){makeroot(x),access(y),splay(y);}

signed main(){
	n=read(),m=read();
	memset(val,-1,sizeof(val));
	for(int i=1;i<=n;++i){
		static char str[N];
		scanf("%s",str),insert(str,i);
	}
	build_fail();
	while(m--){
		static char str[N];
		static int opt,x,y,res,t;
		scanf("%d",&opt);
		if(opt==2){
			res=-1,scanf("%s",str);
			for(int u=1,i=0,len=strlen(str);i<len;++i)
				u=trie[u][str[i]-'a'],split(1,u),res=max(res,mx[u]);
			printf("%d\n",res);
		}else {
			x=read(),y=read(),t=to[x];
			splay(t),s[t].erase(s[t].find(strval[x])),s[t].insert(y),val[t]=*s[t].begin(),strval[x]=y;
		}
	}
	return 0;
}