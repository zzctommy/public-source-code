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
#define T (N<<1)
int n,tag[T],trans[T][26],mxlen[T],link[T],tot=1,lst;
LL ans[N];
vector<int>e[T];
int extend(int c,int id){
	 if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[q]==mxlen[p]+1)return tag[q]=-1,q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			tag[nq]=id;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
			return nq;
		}
	}
	int p=lst,np=++tot;mxlen[np]=mxlen[p]+1;tag[np]=id;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[q]==mxlen[p]+1)link[np]=q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			tag[nq]=id;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
void dfs(int u){
	for(int v:e[u]){
		dfs(v);
		if(tag[v]!=tag[u])tag[u]=-1;
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		static char str[N];
		scanf("%s",str),lst=1;
		for(int j=0,m=strlen(str);j<m;++j)lst=extend(str[j]-'a',i);
	}
	for(int i=1;i<=tot;++i)e[link[i]].pb(i);
	dfs(1);
	for(int i=1;i<=tot;++i)if(~tag[i])ans[tag[i]]+=mxlen[i]-mxlen[link[i]];
	for(int i=1;i<=n;++i)printf("%lld\n",ans[i]);
	return 0;
}