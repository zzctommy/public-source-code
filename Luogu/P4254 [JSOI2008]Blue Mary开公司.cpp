#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define fi first
#define se second
#define sz(v) (int)v.size()
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=0;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return f?x:-x;
}

int rdc(){
	char ch=getchar();
	while(ch!='t'&&ch!='y')ch=getchar();
	return ch=='t';
}
#define N 50005
#define T (N<<2)
#define M 100005
pair<db,db>li[M];
int cnt,v[T];
#define lc (p<<1)
#define rc (p<<1|1)
#define val(x,y) (li[x].fi*y+li[x].se)
void update(int id,int l=1,int r=50000,int p=1){
	int mid=(l+r)>>1;
	if(!v[p])return v[p]=id,void();
	db nol=val(id,l),nor=val(id,r),lal=val(v[p],l),lar=val(v[p],r);
	if(nol<=lal&&nor<=lar)return;
	if(nol>=lal&&nor>=lar)return v[p]=id,void();
	db inter=(li[v[p]].se-li[id].se)/(li[id].fi-li[v[p]].fi);
	if(nol>=lal){
		if(inter<=mid)update(id,l,mid,lc);
		else update(v[p],mid+1,r,rc),v[p]=id;
	}else{
		if(inter>mid)update(id,mid+1,r,rc);
		else update(v[p],l,mid,lc),v[p]=id;
	}
}
db query(int X,int l=1,int r=50000,int p=1){
	db res=0;
	if(v[p]&&val(v[p],X)>res)res=val(v[p],X);
	if(l==r)return res;
	int mid=(l+r)>>1;
	if(X<=mid)res=max(res,query(X,l,mid,lc));
	else res=max(res,query(X,mid+1,r,rc));
	return res;
}
signed main(){
	for(int Te=read();Te;--Te){
		static int op,x;
		static db S,P;
		op=rdc();
		if(op)scanf("%lf%lf",&S,&P),li[++cnt]=mkp(P,S-P),update(cnt);
		else x=read(),printf("%d\n",(int)floor(query(x)/100));
	}
	return 0;
}