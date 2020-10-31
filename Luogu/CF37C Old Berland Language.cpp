#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define x first
#define y second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
const int N=1005;
const int M=1000005;
int n,ls[M],rs[M],to[N],rt,tot,fa[M];
bool full[M];
pair<int,int>a[N];
void insert(int len,int&ed,int&o){
	if(!o)o=++tot;
	if(!len)return ed=o,full[o]=1,void();
	if(!full[ls[o]])insert(len-1,ed,ls[o]),fa[ls[o]]=o;
	else if(!full[rs[o]])insert(len-1,ed,rs[o]),fa[rs[o]]=o;
	else puts("NO"),exit(0);
	if(full[ls[o]]&&full[rs[o]])full[o]=1;
}
int d[1005];
void print(int o){
	d[0]=0;
	while(o!=rt)d[++d[0]]=rs[fa[o]]==o,o=fa[o];
	for(int i=d[0];i;--i)putchar('0'+d[i]);
	puts("");
}
bool cmp(pair<int,int>a,pair<int,int>b){return a.y<b.y;}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i].x=read(),a[i].y=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)insert(a[i].x,to[a[i].y],rt);
	puts("YES");
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)print(to[i]);
}