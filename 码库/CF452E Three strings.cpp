#include<bits/stdc++.h>
using namespace std;
#define N 300005
#define S (N<<1)
#define mod 1000000007
char str[N];
int trans[S][26],tot=1,link[S],mxlen[S];
int n,cnt[S][3],q[S],t[S],ans[N];
int extend(int c,int id,int lst){
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
bool ckmax(int&x,int y){return x<y?x=y,1:0;}
bool ckmin(int&x,int y){return x>y?x=y,1:0;}
void fmod(int&x){x+=x>>31&mod,x-=mod,x+=x>>31&mod;}
signed main(){
	scanf("%s",str),n=strlen(str);
	for(int i=0,lst=1,len=strlen(str);i<len;++i)lst=extend(str[i]-'a',0,lst);
	scanf("%s",str),ckmin(n,strlen(str));
	for(int i=0,lst=1,len=strlen(str);i<len;++i)lst=extend(str[i]-'a',1,lst);
	scanf("%s",str),ckmin(n,strlen(str));
	for(int i=0,lst=1,len=strlen(str);i<len;++i)lst=extend(str[i]-'a',2,lst);
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=tot;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
	for(int i=tot;i>=1;--i)for(int j=0;j<3;++j)fmod(cnt[link[q[i]]][j]+=cnt[q[i]][j]);
	for(int i=2;i<=tot;++i){
		int tmp=1ll*cnt[i][0]*cnt[i][1]%mod*cnt[i][2]%mod;
		fmod(ans[mxlen[link[i]]+1]+=tmp),fmod(ans[mxlen[i]+1]-=tmp);
	}
	for(int i=1;i<=n;++i)fmod(ans[i]+=ans[i-1]);
	for(int i=1;i<=n;++i)printf("%d%c",ans[i]," \n"[i==n]);
	return 0;
}
/*
abc
bc
cbc

abacaba
abac
abcd

*/