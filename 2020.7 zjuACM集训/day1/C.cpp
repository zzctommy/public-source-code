#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=1.2e5+10;
const int M=400;
struct edge {
	int nxt,to;
}e[N<<1];
int num_edge,head[N];
void addedge(int from,int to) {
	++num_edge;
	e[num_edge].nxt=head[from];
	e[num_edge].to=to;
	head[from]=num_edge;
}
int n,m,size,cnt;
int deg[N],id[N],rev[M];
bool ans[M][M];
unordered_map<int,bool>mp[N];
bool isc(int x,int y) {//is connected?
	return mp[x].find(y)!=mp[x].end();
}
void add(int x) {//add a new big point
	id[x]=++cnt,rev[cnt]=x;
	for(rint i=1;i<cnt;++i) {
		if(isc(rev[i],x))continue;
		for(rint j=head[x];j;j=e[j].nxt)
			if(isc(e[j].to,rev[i])){ans[i][cnt]=ans[cnt][i]=1;break;}
	}
}
void upd(int x,int y) {
	for(rint i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(deg[v]<=size)continue;
		if(isc(y,v))ans[id[y]][id[v]]=ans[id[v]][id[y]]=0;
		else ans[id[y]][id[v]]=ans[id[v]][id[y]]=1;
	}
}
void modify(int x,int y) {
	ans[id[x]][id[y]]=ans[id[y]][id[x]]=0;
	for(rint i=1;i<=cnt;++i){
		if(!isc(y,rev[i])&&isc(x,rev[i]))ans[id[y]][i]=ans[i][id[y]]=1;
		if(!isc(x,rev[i])&&isc(y,rev[i]))ans[id[x]][i]=ans[i][id[x]]=1;
	}
} 
void query(int x,int y) {  
	if(isc(x,y)){puts("No");return;}
	if(deg[x]>deg[y])x^=y^=x^=y;
	if(deg[x]>size) {puts(ans[id[x]][id[y]]?"Yes":"No");return;}
	for(rint i=head[x];i;i=e[i].nxt)
		if(isc(y,e[i].to)){puts("Yes");return;}
	puts("No");
}
signed main()  {
	n=rd(),m=rd(),size=sqrt(m)+1;
	while(m--){
		int opt=rd(),x=rd(),y=rd();
		if(opt==1){
			++deg[x],++deg[y];
			addedge(x,y),addedge(y,x);
			mp[x][y]=mp[y][x]=1;
			if(deg[x]==size+1)add(x);
			if(deg[y]==size+1)add(y);
			if(deg[x]>deg[y])x^=y^=x^=y;
			if(deg[x]<=size&&deg[y]>size)upd(x,y);
			if(deg[x]>size&&deg[y]>size)modify(x,y);
		} else query(x,y);
	}
	return 0;
}
