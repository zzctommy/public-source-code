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
#define N 100005
#define T (1900000*2)
int n,c,a[N],deg[N],lef[N],fa[N];
LL ans;
int link[T],lst,tot=1,mxlen[T],trans[T][10];
struct edge{int nxt,to;}e[N<<1];
int head[N],num_edge;
void addedge(int fr,int to){
	++num_edge;
	e[num_edge].nxt=head[fr];
	e[num_edge].to=to;
	head[fr]=num_edge;
}
void dfs(int u,int ft){
	fa[u]=ft;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ft)continue;
		dfs(v,u);
	}
}
int extend(int c){
	if(trans[lst][c]){
		int p=lst,q=trans[lst][c];
		if(mxlen[p]+1==mxlen[q])return q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<10;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
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
			for(int i=0;i<10;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
signed main(){
	n=read(),c=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		addedge(x,y),addedge(y,x);
		++deg[x],++deg[y];
	}
	for(int i=1;i<=n;++i)if(deg[i]==1)lef[++lef[0]]=i;
	for(int i=1;i<=lef[0];++i){
		dfs(lef[i],0);
		for(int j=1;j<=lef[0];++j){
			if(i==j)continue;
			int u=lef[j];
			lst=1;
			while(u){
				lst=extend(a[u]);
				u=fa[u];
			}
		}
	}
	for(int i=1;i<=tot;++i)ans+=mxlen[i]-mxlen[link[i]];
	printf("%lld\n",ans);
	return 0;
}