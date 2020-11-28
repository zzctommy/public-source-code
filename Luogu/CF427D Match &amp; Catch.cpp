#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 10005
#define S (N<<1)
int n,ans=N;
int trans[S][26],mxlen[S],link[S],tot=1,lst,cnt[S][2];
int t[S],q[S];
int extend(int c,int lst,int id){
	if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])return ++cnt[q][id],q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
			return ++cnt[nq][id],nq;
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
	return ++cnt[np][id],np;
}
signed main(){
	static char str[N];
	scanf("%s",str),lst=1,n=strlen(str);
	for(int i=0;i<n;++i)lst=extend(str[i]-'a',lst,0);
	scanf("%s",str),lst=1,n=strlen(str);
	for(int i=0;i<n;++i)lst=extend(str[i]-'a',lst,1);
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=tot;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
	for(int i=tot;i>=1;--i)cnt[link[q[i]]][0]+=cnt[q[i]][0],cnt[link[q[i]]][1]+=cnt[q[i]][1];
	for(int i=2;i<=tot;++i)if(cnt[i][0]==1&&cnt[i][1]==1)ans=min(ans,mxlen[link[i]]+1);
	if(ans==N)ans=-1;printf("%d\n",ans);
	return 0;
}