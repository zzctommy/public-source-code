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
#define N (11000005)
#define S (N<<1)

int n,m;
int ma[N];
int trans[S][2],mxlen[S],link[S],tot=1;
int q[N],H,T,dp[N];

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
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return np;
}

int check(int L,int len){
	H=1,T=0,dp[0]=0;
	for(int i=1;i<=len;++i){
		if(i>=L){
			while(H<=T&&dp[q[T]]-q[T]<=dp[i-L]-(i-L))--T;
			q[++T]=i-L;
		}
		if(ma[i]<L){dp[i]=dp[i-1];continue;}
		while(H<=T&&i-ma[i]>q[H])++H;
		if(H<=T)dp[i]=max(dp[q[H]]+i-q[H],ma[i]);
		dp[i]=max(dp[i-1],dp[i]);
	}
	return dp[len];
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		static char str[N];
		scanf("%s",str);
		for(int j=0,len=strlen(str),lst=1;j<len;++j)lst=extend(str[j]-'0',lst);
	}
	while(n--){
		static char str[N];
		static int u,len,now;
		scanf("%s",str+1),len=strlen(str+1),u=1,now=0;
		for(int i=1;i<=len;++i){
			int c=str[i]-'0';
			if(trans[u][c])u=trans[u][c],++now;
			else{
				for(;u&&!trans[u][c];u=link[u]);
				if(!u)u=1,now=0;
				else now=mxlen[u]+1,u=trans[u][c];
			}
			ma[i]=now;
		}
		int l=1,r=len,res=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid,len)*10>=len*9)res=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",res);
	}
	return 0;
}