#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
const int M=1000005;
int n,m,ans,a[N],siz[M],head[M],nxt[M],F[M],st[M];
void merge(int x,int y){
	for(int i=head[x];i;i=nxt[i])ans-=(a[i-1]==y)+(a[i+1]==y);
	for(int i=head[x];i;i=nxt[i])a[i]=y;
	nxt[st[x]]=head[y],head[y]=head[x],siz[y]+=siz[x];
	siz[x]=head[x]=st[x]=0;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		++siz[a[i]=read()],F[a[i]]=a[i],ans+=a[i]!=a[i-1];
		if(!head[a[i]])st[a[i]]=i;
		nxt[i]=head[a[i]],head[a[i]]=i;
	}
	while(m--) {
		int opt=read(),x,y;
		if(opt==1){
			x=read(),y=read();
			if(x==y)continue;
			if(siz[F[x]]>siz[F[y]])swap(F[x],F[y]);
			if(!siz[F[x]])continue;
			merge(F[x],F[y]);
		}else printf("%d\n",ans);
	}
}
