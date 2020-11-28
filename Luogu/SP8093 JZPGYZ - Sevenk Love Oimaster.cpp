#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
#define T (N<<1)
#define M 360005
int n,m;
int trans[T][26],link[T],mxlen[T],tot=1,tag[T],cnt[T];
string S[10005];
int extend(int c,int lst){
	if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])return q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
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
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>S[i];
		for(int lst=1,len=S[i].length(),j=0;j<len;++j)
			lst=extend(S[i][j]-'a',lst);
	}
	for(int i=1;i<=n;++i){
		static int now,u;
		now=1;
		for(int j=0,len=S[i].length();j<len;++j){
			now=trans[now][S[i][j]-'a'],u=now;
			while(u&&tag[u]!=i)tag[u]=i,++cnt[u],u=link[u];
		}
	}
	while(m--){
		int u=1;string S;
		cin>>S;
		for(int i=0,len=S.length();i<len;++i)u=trans[u][S[i]-'a'];
		printf("%d\n",cnt[u]);
	}
	return 0;
}