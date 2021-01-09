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
#define N 200005
#define S (N<<1)
int n,m,q;
int trans[S][2],mxlen[S],link[S],tot=1,lst;
int b[S],c[S];
int len[N],ST[18][N],lg[N],pw[30];
char s[N],t[N];
int extend(int c,int lst){
	int p=lst,np=++tot;mxlen[np]=mxlen[p]+1;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=++tot;mxlen[nq]=mxlen[p]+1;
			trans[nq][0]=trans[q][0],trans[nq][1]=trans[q][1];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}
int ask(int l,int r){
	if(l>r)return 0;int t=lg[r-l+1];
	return max(ST[t][l],ST[t][r-pw[t]+1]);
}
signed main(){
	scanf("%s%s%d",s,t,&q),n=strlen(s),m=strlen(t);
	for(int i=0,lst=1;i<m;++i)lst=extend(t[i]-'a',lst);
	for(int i=0,l=0,u=1;i<n;++i){
		int c=s[i]-'a';
		if(trans[u][c])u=trans[u][c],++l;
		else{
			for(;u&&!trans[u][c];u=link[u]);
			if(trans[u][c])l=mxlen[u]+1,u=trans[u][c];
			else u=1,l=0;
		}
		len[i+1]=l;
	}
	lg[0]=-1;for(int i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
	pw[0]=1;for(int i=1;i<=20;++i)pw[i]=pw[i-1]<<1;
	for(int i=1;i<=n;++i)ST[0][i]=len[i];
	for(int i=1;i<=lg[n];++i)
		for(int j=1;j+pw[i]-1<=n;++j)
			ST[i][j]=max(ST[i-1][j],ST[i-1][j+pw[i-1]]);
	while(q--){
		int L=read(),R=read(),l=L,r=R+1,pos=R+1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(mid-len[mid]+1>=L)r=mid-1,pos=mid;
			else l=mid+1;
		}
		printf("%d\n",max(pos-L,ask(pos,R)));
	}
	return 0;
}