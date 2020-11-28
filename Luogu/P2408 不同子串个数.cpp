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
template<int L>
struct Suffix_Automation{

#define N (L+5)

#define S (N<<1)

int trans[S][26],tot,mxlen[S],link[S];
int q[S],t[S],rt[S];

int New(){++tot;memset(trans[tot],0,sizeof(trans[tot]));mxlen[tot]=link[tot]=0;return tot;}

Suffix_Automation(){tot=0,New();}
void clear(){tot=0;New();}

int extend(int c,int lst,int id,int op=0){
	if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])return q;
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
			return nq;
		}
	}
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
	return np;
}
void insert(char*str,int op=0){
	int n=strlen(str);
	for(int i=0,lst=1;i<n;++i)lst=extend(str[i]-'a',lst,i+1);
}
void rsort(){
	for(int i=1;i<=tot;++i)t[i]=0;
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=tot;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
}
LL distinct_substring(){
	LL res=0;
	for(int i=1;i<=tot;++i)res+=mxlen[i]-mxlen[link[i]];
	return res;
}
#undef S
#undef N

};

Suffix_Automation<100000>sam;
signed main(){
	static char str[100005];read();
	scanf("%s",str),sam.insert(str),cout<<sam.distinct_substring()<<'\n';
}