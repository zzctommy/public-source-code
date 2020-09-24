#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rint register int
#define N 100001
#define C 200
#define M 500001
int val[M*C],rnd[M*C],ch[M*C][2],size[M*C],root[M],n,m,a[N],b[M],num_node,tot;
ll lastans;
vector<int>vec[M];
#define lt(i) (i&(-i))
ll tr[N];
void add(int x,int d) {
	if(x<=0)return;
	for(int i=x; i<=n; i+=lt(i))
		tr[i]+=d;
}
ll sum(int x) {
	if(x>n)x=n;
	ll res=0;
	for(int i=x; i>0; i-=lt(i))
		res+=tr[i];
	return res;
}
void upd(int u) {
	size[u]=size[ch[u][0]]+1+size[ch[u][1]];
}
int newnode(int x) {
	++num_node;
	val[num_node]=x;
	rnd[num_node]=rand();
	size[num_node]=1;
	return num_node;
}
int build(int l,int r,int *p) {
	if(l>r)return 0;
	int mid=(l+r)>>1;
	int u=newnode(p[mid]);
	ch[u][0]=build(l,mid-1,p);
	ch[u][1]=build(mid+1,r,p);
	return upd(u),u;
}
int merge(int a,int b) {
	if(!a||!b)return a+b;
	if(rnd[a]<rnd[b]) {
		ch[a][1]=merge(ch[a][1],b);
		return upd(a),a;
	} else {
		ch[b][0]=merge(a,ch[b][0]);
		return upd(b),b;
	}
}
void split(int u,int k,int &x,int &y) {
	if(!u) x=y=0;
	else {
		if(val[u]<=k)x=u,split(ch[u][1],k,ch[u][1],y);
		else y=u,split(ch[u][0],k,x,ch[u][0]);
		upd(u);
	}
}
void dfs(int u,int mo) {
	if(!u)return;
	if(ch[u][0])dfs(ch[u][0],mo);
	if(a[val[u]]%mo==0) {
		add(val[u],-a[val[u]]);
		a[val[u]]/=mo;
		add(val[u],a[val[u]]);
	}
	if(a[val[u]]%mo==0)b[++tot]=val[u];
	if(ch[u][1])dfs(ch[u][1],mo);
}
void del(int u,int l,int r) {
	int x,y,z;
	split(root[u],r,x,y);
	split(x,l-1,x,z);
	tot=0;
	dfs(z,u);
	root[u]=merge(x,merge(build(1,tot,b),y));
}
int main() {
	srand(time(0));
	scanf("%d%d",&n,&m);
	for(rint i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		add(i,a[i]);
		for(int j=1,mx=sqrt(a[i]); j<=mx; ++j) {
			if(a[i]%j)continue;
			vec[j].push_back(i);
			if(j*j!=a[i])vec[a[i]/j].push_back(i);
		}
	}
	for(rint i=1; i<=M-3; ++i) {
		int cnt=0;
		for(rint j=0; j<vec[i].size(); ++j)
			b[++cnt]=vec[i][j];
		root[i]=build(1,cnt,b);
	}
	while(m--) {
		int opt,l,r,x;
		scanf("%d",&opt);
		if(opt==1) {
			scanf("%d%d%d",&l,&r,&x);
			l^=lastans,r^=lastans,x^=lastans;
			if(x^1)del(x,l,r);
		} else {
			scanf("%d%d",&l,&r);
			l^=lastans,r^=lastans;
			lastans=sum(r)-sum(l-1);
			printf("%lld\n",lastans);
		}
	}
	return 0;
}
