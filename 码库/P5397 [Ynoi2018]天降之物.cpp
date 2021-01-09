#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define mkp(x,y) make_pair(x,y)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100009;
const int M=320;
const int inf=0x3f3f3f3f;
int n,m,a[N],lastans;
int lim,siz[N],ans[M][N],id[N],F[N];
int rub[N],top,tot;
vector<int>v[N];
int New() {return top?rub[top--]:++tot;}
void build(int x,int Id=0) {
	id[x]=Id?Id:New();
	int t=id[x];
	memset(ans[t],0x3f,sizeof(ans[t]));
	for(int i=1,j=inf;i<=n;++i)
		if(a[i]==x)j=0;
		else ans[t][a[i]]=min(ans[t][a[i]],++j);
	for(int i=n,j=inf;i;--i)
		if(a[i]==x)j=0;
		else ans[t][a[i]]=min(ans[t][a[i]],++j);
	vector<int>fyyAKIOI;
	ans[t][x]=0,v[x].swap(fyyAKIOI);
}
void merge(int x,int y) {
	int i=0,j=0,sx=v[x].size(),sy=v[y].size();
	vector<int>res;
	while(i<sx&&j<sy)res.push_back(v[x][i]<v[y][j]?v[x][i++]:v[y][j++]);
	while(i<sx)res.push_back(v[x][i++]);
	while(j<sy)res.push_back(v[y][j++]);
	v[y]=res;
}
int merge_(int x,int y) {
	int i=0,j=0,sx=v[x].size(),sy=v[y].size(),res=inf;
	if(!sx||!sy)return inf;
	while(i<sx&&j<sy)res=min(v[x][i]<v[y][j]?v[y][j]-v[x][i++]:v[x][i]-v[y][j++],res);
	if(i<sx)res=min(res,abs(v[x][i]-v[y][sy-1]));
	if(j<sy)res=min(res,abs(v[x][sx-1]-v[y][j]));
	return res;
}
int query(int x,int y) {
	x=F[x],y=F[y];
	if(!siz[x]||!siz[y])return -1;
	if(x==y)return 0;
	if(siz[x]>siz[y])x^=y^=x^=y;
	if(siz[y]<=lim)return merge_(x,y);
	else if(siz[x]<=lim)return min(ans[id[y]][x],merge_(x,y));
	else return min(merge_(x,y),min(ans[id[x]][y],ans[id[y]][x]));
}
void change(int x,int y) {
	int x_=F[x],y_=F[y];
	if(!siz[x_]||x_==y_)return;
	if(siz[x_]>siz[y_])F[y]=x_,F[x]=n+1,x_^=y_^=x_^=y_;
	else F[x]=n+1;
	if(x_>n||y_>n)return;
	x=x_,y=y_;
	if(siz[y]<=lim) {
		if(siz[x]+siz[y]<=lim) {
			for(int i:v[x])a[i]=y;
			for(int i=1;i<=tot;++i)ans[i][y]=min(ans[i][y],ans[i][x]);
			merge(x,y);
		} else {
			for(int i=1;i<=n;++i)if(a[i]==x)a[i]=y;
			build(y);
		}
	} else if(siz[x]<=lim) {
		if(siz[x]+v[y].size()<=lim) {
			for(int i:v[x])a[i]=y;
			for(int i=1;i<=tot;++i)ans[i][y]=min(ans[i][y],ans[i][x]);
			merge(x,y);
		} else {
			for(int i=1;i<=n;++i)if(a[i]==x)a[i]=y;
			build(y,id[y]);
		}
	} else {
		for(int i=1;i<=n;++i)if(a[i]==x)a[i]=y;
		rub[++top]=id[x],build(y,id[y]);
	}
	vector<int>fyyAKIOI;
	siz[y]+=siz[x],siz[x]=0,v[x].swap(fyyAKIOI);
}
signed main() {
	n=rd(),m=rd(),lim=sqrt(n);
	for(int i=1;i<=n;++i)++siz[a[i]=rd()],v[a[i]].push_back(i),F[i]=i;
	for(int i=0;i<=n;++i)if(siz[i]>lim)build(i);
	while(m--) {
		 int opt=rd(),x=rd()^lastans,y=rd()^lastans;
		if(opt==1)change(x,y);
		else {
			lastans=query(x,y);
			if(~lastans)printf("%d\n",lastans);
			else lastans=0,puts("Ikaros");
		}
	}
	return 0;
}
