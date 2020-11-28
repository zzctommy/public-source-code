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
#define N 100005
#define S (N<<1)
char str[N];
int n;
int trans[S][26],link[S],mxlen[S],lst,tot,cnt[S];
int t[S],q[S];
LL ans;
int extend(int c,int lst){
	int p=lst,np=++tot;mxlen[np]=mxlen[p]+1;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else {
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	cnt[np]=1;
	return np;
}
void Main(){
	memset(trans,0,sizeof(trans));
	memset(link,0,sizeof(link));
	memset(mxlen,0,sizeof(mxlen));
	memset(cnt,0,sizeof(cnt));
	memset(t,0,sizeof(t));
	lst=tot=1,ans=0;

	scanf("%s",str),n=strlen(str);
	for(int i=0;i<n;++i)lst=extend(str[i]-'a',lst);
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=tot;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
	for(int i=tot;i>=1;--i)cnt[link[q[i]]]+=cnt[q[i]];
	for(int i=1;i<=tot;++i)ans+=1ll*cnt[i]*cnt[i]*(mxlen[i]-mxlen[link[i]]);
	printf("%lld\n",ans);
}
signed main(){for(int T=read();T;--T)Main();}