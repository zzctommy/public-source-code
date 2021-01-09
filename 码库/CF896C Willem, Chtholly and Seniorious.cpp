#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=100005;
int n,m,seed,vmax,a[MAXN];
int rnd()
{
	int ret=seed;
	seed=(seed*7+13)%1000000007;
	return ret;
}
int ksm(int n,int k,int p)
{
	int base=n%p,ans=1;
	while(k)
	{
		if(k&1)ans=ans*base%p;
		k>>=1;
		base=base*base%p;
	}
	return ans%p;
}
struct node{
	int ll,rr;
	mutable int val;
	node(int L,int R=-1,int V=0):ll(L),rr(R),val(V){}
	bool operator < (const node & rhs)const{return ll<rhs.ll;}
};
set<node>s;
#define it set<node>::iterator
it split(int pos)
{
	it iter=s.lower_bound(node(pos));
	if(iter!=s.end()&&iter->ll==pos)return iter;
	--iter;
	int l=iter->ll,r=iter->rr,v=iter->val;
	s.erase(iter);
	s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v)).first;
}
void assign(int l,int r,int v)
{
	it itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,v));
}
int querysum(int l,int r)
{
	it itr=split(r+1),itl=split(l);
	int res=0;
	for(;itl!=itr;itl++)res=res+(itl->rr-itl->ll+1)*itl->val;
	return res;
}
int kth(int l,int r,int k)
{
	vector<pair<int,int> >v;
	it itr=split(r+1),itl=split(l);	
	for(;itl!=itr;itl++)v.push_back(pair<int,int>(itl->val,itl->rr-itl->ll+1));
	sort(v.begin(),v.end());
	for(vector<pair<int,int> >::iterator iter=v.begin();iter!=v.end();iter++)
	{
		k-=iter->second;
		if(k<=0)return iter->first;
	}
	return -1;
}
void add(int l,int r,int k)
{
	it itr=split(r+1),itl=split(l);
	for(;itl!=itr;itl++) 
	itl->val+=k;
}
int querypow(int l,int r,int k,int mod)
{
	it itr=split(r+1),itl=split(l);
	int res=0;
	for(;itl!=itr;itl++)
		res=(res+ksm(itl->val,k,mod)*((itl->rr-itl->ll+1)%mod)%mod)%mod;
	return res;
}

signed main() {
	scanf("%lld%lld%lld%lld",&n,&m,&seed,&vmax);
	for(int i=1;i<=n;i++)
	{
		a[i]=(rnd()%vmax)+1;
		s.insert(node(i,i,a[i]));
	}
	for(int i=1;i<=m;i++)
	{
		int opt=(rnd()%4)+1;
		int l=(rnd()%n)+1;
		int r=(rnd()%n)+1;
		if(l>r)swap(l,r);
		int x,y;
		if(opt==3)x=(rnd()%(r-l+1))+1;
		else x=(rnd()%vmax)+1;
		if(opt==4)y=(rnd()%vmax)+1;
		if(opt==1)add(l,r,x);
		if(opt==2)assign(l,r,x);
		if(opt==3)printf("%lld\n",kth(l,r,x));
		if(opt==4)printf("%lld\n",querypow(l,r,x,y));
	}
	return 0;
}