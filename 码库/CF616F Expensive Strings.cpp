#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
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
const int N=1000005;
const int S=N<<1;
int n,a[N];
string str[N];
int trans[S][26],mxlen[S],link[S],rt[S],tot=1;
vector<int>e[S];
LL s[S],ans=-1e18;
int extend(int c,int lst,int id){
	if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])return s[q]+=a[id],q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
			return s[nq]+=a[id],nq;
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
	return s[np]+=a[id],np;
}
void dfs(int u){
	for(int v:e[u])dfs(v),s[u]+=s[v];
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	rep(i,1,n)cin>>str[i];
	rep(i,1,n)cin>>a[i];
	rep(i,1,n){
		int lst=1,len=sz(str[i]);
		for(int j=0;j<len;++j)lst=extend(str[i][j]-'a',lst,i);
	}
	for(int i=1;i<=tot;++i)e[link[i]].pb(i);
	dfs(1);
	for(int i=1;i<=tot;++i)ckmax(ans,1ll*mxlen[i]*s[i]);
	cout<<ans<<'\n';
}