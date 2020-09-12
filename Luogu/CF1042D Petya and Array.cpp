#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200005;
int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
int n,t,ans,rt,tot,a[N],sum[N];
int siz[N],ch[N][2],val[N],rnd[N];
void pushup(int u) {
	siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;
}
int newnode(int x) {
	++tot;
	rnd[tot]=rand();
	val[tot]=x;
	siz[tot]=1;
	return tot;
}
int merge(int x,int y) {
	if(!x||!y)return x+y;
	if(rnd[x]<rnd[y]) {
		ch[x][1]=merge(ch[x][1],y);
		pushup(x);
		return x;
	} else {
		ch[y][0]=merge(x,ch[y][0]);
		pushup(y);
		return y;
	}
}
void split(int u,int k,int &x,int &y) {
	if(!u) {
		x=y=0;
		return;
	}
	if(val[u]<=k)
		x=u,split(ch[u][1],k,ch[u][1],y);
	else
		y=u,split(ch[u][0],k,x,ch[u][0]);
	pushup(u);
}
void insert(int x) {
	int a,b;
	split(rt,x,a,b);
	rt=merge(merge(a,newnode(x)),b);
}
void del(int x) {
	int a,b,c;
	split(rt,x,a,b);
	split(a,x-1,a,c);
	c=merge(ch[c][0],ch[c][1]);
	rt=merge(merge(a,c),b);
}
signed main() {
	n=rd(),t=rd();
	for(int i=1;i<=n;++i)a[i]=rd(),sum[i]=sum[i-1]+a[i];
	insert(0);for(int i=1;i<=n;++i)insert(sum[i]);
	for(int i=n;i>=1;--i) {
		del(sum[i]);
		int a,b;
		split(rt,sum[i]-t,a,b);
		ans+=siz[b];
		rt=merge(a,b);
	}
	printf("%lld\n",ans);
	return 0;
}