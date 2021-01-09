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
const int T=40000000;
int n,q,c[N];
char str[N];
set<pair<int,int> >s;
int rt[N],ls[T],rs[T],val[T],tot;
void update(int&p,int pos,int k,int l=1,int r=n+1){
	if(!p){
		p=++tot;
		if(tot>=T){puts("fyy AK IOI");exit(0);}
	}
	val[p]+=k;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],pos,k,l,mid);
	else update(rs[p],pos,k,mid+1,r);
}
int query(int p,int ql,int qr,int l=1,int r=n+1){
	if(!p)return 0;
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ls[p],ql,qr,l,mid);
	if(mid<qr)res+=query(rs[p],ql,qr,mid+1,r);
	return res;
}
void add(int x,int y,int d){
	if(x>n||y>n)return;
	for(int i=x;i<=n+1;i+=i&-i)update(rt[i],y,d);
	// a[x][y]+=d;
}
void upd(int a1,int b1,int a2,int b2,int d){
	// cerr<<"upd:"<<a1<<' '<<b1<<' '<<a2<<' '<<b2<<' '<<d<<'\n';
	add(a1,b1,d),add(a1,b2+1,-d),add(a2+1,b1,-d),add(a2+1,b2+1,d);
}
int ask(int x,int y){
	// cerr<<"ask:"<<x<<' '<<y<<'\n';
	int res=0;
	for(int i=x;i>0;i-=i&-i)res+=query(rt[i],1,y);
	// rep(i,1,x)rep(j,1,y)res+=a[i][j];
	return res;
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
	// cerr<<"s:\n";for(auto i:s)cerr<<i.fi<<' '<<i.se<<'\n';
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
				// cerr<<"touggle:"<<x<<' '<<it->fi<<' '<<it->se<<'\n';
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
			printf("%d\n",ask(x,y)-a1);
		}
		// cerr<<"s:\n";for(auto i:s)cerr<<i.fi<<' '<<i.se<<'\n';
	}
}
/*
5 7
11011
query 1 2
query 1 2
query 1 6
query 3 4
toggle 3
query 3 4
query 1 6

10 10
0111001101
query 9 10
toggle 1
toggle 4
query 6 11
query 7 9
toggle 10
query 7 11
query 1 6
query 1 10
query 1 9

*/