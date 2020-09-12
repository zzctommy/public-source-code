#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
#include <iostream>
#include<cmath>

using std::cout;
using std::endl;
using std::vector;
using std::lower_bound;
using std::unique;
using std::sort;
using std::max;
using std::min;

inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

const int N=200009;
const int T=N*26;
int n,w[N],f[N];
int lsh[N],m;
int val[T],ls[T],rs[T],root[N],tot,tag[T];
std::vector<int>g[N];

void pushup(int p) {
	val[p]=val[ls[p]]+val[rs[p]];
}

int query(int ql,int qr,int l,int r,int p){
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ql,qr,l,mid,ls[p]);
	if(mid<qr)res+=query(ql,qr,mid+1,r,rs[p]);
	return res;
}

int merge(int x,int y,int l,int r) {
	if(!x||!y)return x|y;
	if(l==r)return val[x]+=val[y],x;
	int mid=(l+r)>>1;
	ls[x]=merge(ls[x],ls[y],l,mid);
	rs[x]=merge(rs[x],rs[y],mid+1,r);
	return pushup(x),x;
}

void add(int pos,int l,int r,int &p,int k){
	if(!p)p=++tot;
	if(l==r)return val[p]+=k,void();
	int mid=(l+r)>>1;
	if(pos<=mid)add(pos,l,mid,ls[p],k);
	else add(pos,mid+1,r,rs[p],k);
	pushup(p);
}

int find(int v,int l,int r,int p,int sum) {
	if(!p)return 1;
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(sum+val[ls[p]]<v)return find(v,l,mid,ls[p],sum);
	else return find(v,mid+1,r,rs[p],sum+val[ls[p]]);
}

void dfs(int u) {
	for(int v:g[u])
		dfs(v),root[u]=merge(root[u],root[v],1,m);
	int s=query(1,w[u],1,m,root[u]),t=find(s+1,1,m,root[u],0);
	add(t,1,m,root[u],1);
	if(w[u]!=m)add(w[u]+1,1,m,root[u],-1);
}

signed main() {
	n=rd();
	for (int i = 1; i <= n; ++i) w[i] = lsh[i] = rd();
	sort(lsh + 1, lsh + n + 1), m = unique(lsh + 1, lsh + n +1) - lsh -1;
	for (int i = 1; i <= n; ++i) w[i] = lower_bound(lsh + 1, lsh + m + 1, w[i]) - lsh;
	for (int i = 2; i <= n; ++i) g[f[i] = rd()].push_back(i);
	dfs(1), printf("%d\n", query(1,1,1,m,root[1])); 
	return 0;
}