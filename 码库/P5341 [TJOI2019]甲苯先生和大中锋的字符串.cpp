#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 3000005
#define S (N<<1)
int n,k,trans[S][26],tot,mxlen[S],link[S],cnt[S];
int q[S],t[N],dif[N];
char str[N];
int New(){return ++tot,memset(trans[tot],0,sizeof(trans[tot])),link[tot]=cnt[tot]=mxlen[tot]=0,tot;}
int extend(int c,int lst){
	int p=lst,np=New();mxlen[np]=mxlen[p]+1;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	return ++cnt[np],np;
}
void Main(){
	scanf("%s%d",str,&k),n=strlen(str);
	tot=0,New();
	for(int i=0,lst=1;i<n;++i)lst=extend(str[i]-'a',lst);
	fill(t,t+n+1,0),fill(dif,dif+n+1,0);
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=n;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
	for(int i=tot;i>=1;--i)cnt[link[q[i]]]+=cnt[q[i]];
	for(int i=1;i<=tot;++i)if(cnt[i]==k)++dif[mxlen[link[i]]+1],--dif[mxlen[i]+1];
	bool flg=0;
	for(int i=1;i<=n;++i)dif[i]+=dif[i-1],flg|=dif[i]>0;
	if(!flg)return puts("-1"),void();
	int tim=0,res=0;
	for(int i=1;i<=n;++i)
		if(dif[i]>=tim)tim=dif[i],res=i;
	printf("%d\n",res);
}
signed main(){for(int T=read();T;--T)Main();}
/*
6
aab 1
abc 1
aaaa 2
abab 2
ababacc 2
abab 4

*/