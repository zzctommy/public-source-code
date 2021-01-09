#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=500005;
const int T=N*50;
int tot;
int rt[N];
struct node{
	int ls,rs,siz,rnd,val;
	#define ls(x) (t[x].ls)
	#define rs(x) (t[x].rs)
	#define siz(x) (t[x].siz)
	#define rnd(x) (t[x].rnd)
	#define val(x) (t[x].val)
}t[T];
int newnode(int v){return ++tot,siz(tot)=1,rnd(tot)=rand()*rand(),val(tot)=v,tot;}
void pushup(int x){siz(x)=siz(ls(x))+1+siz(rs(x));}
int merge(int x,int y){
	if(!x||!y)return x|y;
	int p=++tot;
	if(rnd(x)<rnd(y)){
		t[p]=t[x];
		rs(p)=merge(rs(p),y);
		return pushup(p),p;
	} else{
		t[p]=t[y];
		ls(p)=merge(x,ls(p));
		return pushup(p),p;
	}
}
void split(int u,int k,int&x,int&y){
	if(!u)return x=y=0,void();
	if(val(u)<=k)t[x=++tot]=t[u],split(rs(x),k,rs(x),y),pushup(x);
	else t[y=++tot]=t[u],split(ls(y),k,x,ls(y)),pushup(y);
}
void insert(int&rt,int v){
	int x,y;
	split(rt,v,x,y);
	rt=merge(x,merge(newnode(v),y));
}
void del(int&rt,int v){
	int x,y,z;
	split(rt,v,y,z);
	split(y,v-1,x,y);
	y=merge(ls(y),rs(y));
	rt=merge(x,merge(y,z));
}
int rnk(int&rt,int v){
	int x,y,res;
	split(rt,v-1,x,y);
	res=siz(x)+1;
	rt=merge(x,y);
	return res;
}
int kth(int rt,int k){
	int now=rt;
	while("fyyAKIOI"){
		if(k<=siz(ls(now)))now=ls(now);
		else if(siz(ls(now))+1==k)return val(now);
		else k-=siz(ls(now))+1,now=rs(now);
	}
}
int lbound(int&rt,int v){
	int x,y,res;
	split(rt,v-1,x,y);
	res=kth(x,siz(x));
	rt=merge(x,y);
	return res;
}
int rbound(int&rt,int v){
	int x,y,res;
	split(rt,v,x,y);
	res=kth(y,1);
	rt=merge(x,y);
	return res;
}
signed main(){
	for(int n=read(),i=1;i<=n;++i){
		int v=read(),opt=read(),x=read();
		rt[i]=rt[v];
		if(opt==1)insert(rt[i],x);
		else if(opt==2)del(rt[i],x);
		else if(opt==3)printf("%d\n",rnk(rt[i],x));
		else if(opt==4)printf("%d\n",kth(rt[i],x));
		else if(opt==5)printf("%d\n",lbound(rt[i],x));
		else if(opt==6)printf("%d\n",rbound(rt[i],x));
		else puts("fyyAKIOI");
	}
	return 0;
}