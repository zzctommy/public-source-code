#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1e6+10;
const int M=N<<1;
int n;
LL ans;
char s[N];
int lst,tot=1,ch[M][26],link[M],maxlen[M];
int ins(int c,int lst) {
	if(ch[lst][c]) {
		int p=lst,q=ch[p][c];
		if(maxlen[q]==maxlen[p]+1)return q;
		else {
			int nq=++tot;maxlen[nq]=maxlen[p]+1;
			for(rint i=0;i<26;++i)ch[nq][i]=ch[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&ch[p][c]==q;p=link[p])ch[p][c]=nq;
			return nq;
		}
	}
	int p=lst,np=++tot;maxlen[np]=maxlen[p]+1;
	for(;p&&!ch[p][c];p=link[p])ch[p][c]=np;
	if(!p)link[np]=1;
	else {
		int q=ch[p][c];
		if(maxlen[q]==maxlen[p]+1)link[np]=q;
		else {
			int nq=++tot;maxlen[nq]=maxlen[p]+1;
			for(rint i=0;i<26;++i)ch[nq][i]=ch[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&ch[p][c]==q;p=link[p])ch[p][c]=nq;
		}
	}
	return np;
}
signed main() {
	n=rd();
	for(rint i=1;i<=n;++i) {
		scanf("%s",s),lst=1;
		for(rint j=0,len=strlen(s);j<len;++j)lst=ins(s[j]-'a',lst);
	}
	for(rint i=2;i<=tot;++i)ans+=maxlen[i]-maxlen[link[i]];
	printf("%lld\n",ans);
	return 0;
}