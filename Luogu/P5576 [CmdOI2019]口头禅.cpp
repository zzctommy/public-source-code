#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 20004
#define M 100005
#define S 400005

int n,m,len,le[N],mxv[N],ans[M];
char str[S];
vector<pair<int,int> >q[N];
int trans[S<<1][2],mxlen[S<<1],link[S<<1],tot=1;
int elt[S<<1],ltt[S<<1],tag[S<<1];

bool ckmax(int&x,int y){return x<y?x=y,1:0;}

int extend(int c,int lst){
	if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])return q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			trans[nq][0]=trans[q][0],trans[nq][1]=trans[q][1];
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
			trans[nq][0]=trans[q][0],trans[nq][1]=trans[q][1];
			link[nq]=link[q],link[np]=link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}

void update(int u,int id,int lim){
	for(;u&&tag[u]!=id;u=link[u]){
		if(id>ltt[u]+1)elt[u]=ltt[u]=id;
		else{
			ltt[u]=id;
			ckmax(mxv[lower_bound(q[id].begin(),q[id].end(),mkp(elt[u],-1))-q[id].begin()+1],min(mxlen[u],lim));
		}
		tag[u]=id;
	}
}


signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		char ch=getchar();le[i]=len+1;
		int lst=1;
		while(!isdigit(ch))ch=getchar();
		while(isdigit(ch))str[++len]=ch,lst=extend(ch-'0',lst),ch=getchar();
	}
	le[n+1]=len+1;
	for(int i=1;i<=m;++i){
		int l=read(),r=read();
		q[r].pb(mkp(l,i));
	}
	for(int i=1;i<=n;++i){
		sort(q[i].begin(),q[i].end());
		fill(mxv,mxv+sz(q[i])+3,0);
		int u=1;
		for(int j=le[i];j<le[i+1];++j)
			u=trans[u][str[j]-'0'],update(u,i,j-le[i]+1);
		for(int j=0;j<sz(q[i]);++j)ckmax(mxv[j+1],mxv[j]),ans[q[i][j].se]=mxv[j+1];
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}