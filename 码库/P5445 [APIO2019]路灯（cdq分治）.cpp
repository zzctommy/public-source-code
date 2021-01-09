/*

    |-------                                                   |------                                   
    |                                                          |     | 
    |                                                          |     |
    |                                                          |     |                             *    |
    |------ |----|   ---  -----  \       / -----   ---         |-----| |    |   ---  ----- |    |     --|--
    |       |    | |/   \ |   |   \     /  |   | |/   \        |       |    | |/   \ |     |    |  |    |  
    |       |    | |      -----    \   /   ----- |             |       |    | |      |---- |    |  |    |
    |       |    | |      |         \ /    |     |             |       |    | |          | |    |  |    |
    |       |----| |      ----/      -     ---/  |     _____   |       |----| |      ----| |----|  |    --/


    \       /  \       / |----\     ------
     \     /    \     /  |     \    |
      \   /      \   /   |      \   |
       \-/        \-/    |      |   ------
        |          |     |      |        |
        |          |     |      /        |
        |          |     |     /         |
        |          |     |----/     ------


*/
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
int rdopt(){
	static char opt[10];
	scanf("%s",opt);
	return opt[0]=='t';
}
const int N=300005;
const int T=N*19*19;
int n,q,c[N],o,tr[N],ans[N];
char str[N];
set<pair<int,int> >s;
struct node{
	int s,x,y,id;
	node(){s=x=y=id=0;}
}a[N<<2],b[N<<2];
inline bool cmp1(const node&a,const node&b){return a.x!=b.x?a.x<b.x:a.y!=b.y?a.y<b.y:a.id<b.id;}
void upd(int a1,int b1,int a2,int b2,int d){
	++o,a[o].s=d,a[o].x=a1,a[o].y=b1,a[o].id=0;
	++o,a[o].s=-d,a[o].x=a1,a[o].y=b2+1,a[o].id=0;
	++o,a[o].s=-d,a[o].x=a2+1,a[o].y=b1,a[o].id=0;
	++o,a[o].s=d,a[o].x=a2+1,a[o].y=b2+1,a[o].id=0;
}
void add(int x,int d){for(int i=x;i<=n;i+=i&-i)tr[i]+=d;}
int ask(int x){int res=0;for(int i=x;i>0;i-=i&-i)res+=tr[i];return res;}
void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,i,j;
	cdq(l,mid),cdq(mid+1,r);
	// cerr<<"cdq:"<<l<<' '<<r<<'\n';
	// rep(i,l,r)cerr<<a[i].x<<' '<<a[i].y<<' '<<a[i].s<<' '<<a[i].id<<'\n';
	for(i=mid+1,j=l;i<=r;++i){
		for(;j<=mid&&a[j].x<=a[i].x;++j)if(!a[j].id)add(a[j].y,a[j].s);
		if(a[i].id)a[i].s+=ask(a[i].y);
	}
	for(--j;j>=l;--j)if(!a[j].id)add(a[j].y,-a[j].s);
	merge(a+l,a+mid+1,a+mid+1,a+r+1,b+l,cmp1);
	for(int i=l;i<=r;++i)a[i]=b[i];
}
signed main(){
	scanf("%d%d%s",&n,&q,str+1);
	rep(i,1,n)c[i]=str[i]-'0';
	for(int i=1,j;i<=n;++i){
		if(!c[i])continue;
		j=i;
		while(j<n&&c[j+1])++j;
		s.insert(mkp(i,j));
		i=j;
	}
	for(set<pair<int,int> >::iterator it=s.begin();it!=s.end();++it)
		upd(it->fi,it->fi,it->se,it->se,q);
	s.insert(mkp(N,N));
	rep(t,1,q){
		int opt=rdopt(),x=read(),y,a1,a2,b1,b2;
		if(opt){
			if(!c[x]){
				set<pair<int,int> >::iterator ir=s.upper_bound(mkp(x,N)),il=ir;--il;
				if(ir==s.begin()||il->se!=x-1)a1=a2=x;
				else a1=il->fi,a2=x,s.erase(il);
				if(ir==s.end()||ir->fi!=x+1)b1=b2=x;
				else b1=x,b2=ir->se,s.erase(ir);
				s.insert(mkp(a1,b2));
				upd(a1,b1,a2,b2,q-t);
			}
			else{
				set<pair<int,int> >::iterator it=s.upper_bound(mkp(x,N));--it;
				a1=it->fi,a2=x,b1=x,b2=it->se,s.erase(it);
				if(a1<x)s.insert(mkp(a1,x-1));
				if(b2>x)s.insert(mkp(x+1,b2));
				upd(a1,b1,a2,b2,t-q);
			}
			c[x]^=1;
		}else{
			y=read()-1;
			set<pair<int,int> >::iterator i1=s.upper_bound(mkp(x,N)),i2=s.upper_bound(mkp(y,N));
			if(c[x]&&c[y]&&i1==i2)a1=q-t;else a1=0;
			++o,a[o].x=x,a[o].y=y,a[o].s=-a1,a[o].id=t;
		}
	}
	cdq(1,o);
	memset(ans,-1,sizeof(ans));
	rep(i,1,o)if(a[i].id)ans[a[i].id]=a[i].s;
	for(int i=1;i<=q;++i)if(~ans[i])printf("%d\n",ans[i]);
	return 0;
}