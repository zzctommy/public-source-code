//Orz cyn2006
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
#define N 150005
int n,pre[N],suf[N],Lm[N],Rm[N],fa[N],val[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)fa[i]=i,Lm[i]=Rm[i]=i,val[i]=i;
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		int fx=find(x),fy=find(y);
		if(!pre[Lm[fx]])pre[Lm[fx]]=Rm[fy],suf[Rm[fy]]=Lm[fx],Lm[fx]=Lm[fy];
		else suf[Rm[fx]]=Lm[fy],pre[Lm[fy]]=Rm[fx],Rm[fx]=Rm[fy];
		fa[fy]=fx;
	}
	for(int i=Lm[find(1)];i;i=suf[i])printf("%d ",i);
	puts("");
	return 0;
}