#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=500010;
int n,q;
struct linear_base {
	int d[30],pos[30];
	linear_base(){memset(d,0,sizeof(d)),memset(pos,0,sizeof(pos));}
	void insert(int val,int id,const linear_base &mzAKIOI) {
		*this=mzAKIOI;
		for(int i=21;i>=0;--i) {
			if(val>>i&1) {
				if(!d[i]){d[i]=val,pos[i]=id;break;}
				else if(pos[i]<id)swap(val,d[i]),swap(id,pos[i]);
				val^=d[i];
			}
		}
	}
	int query(int l) {
		int res=0;
		for(int i=21;i>=0;--i)
			if(d[i]&&pos[i]>=l)res=max(res,res^d[i]);
		return res;
	}
}a[N];
signed main() {
	n=rd();
	for(int i=1;i<=n;++i)a[i].insert(rd(),i,a[i-1]);
	for(q=rd();q;--q) {
		int x=rd(),y=rd();
		printf("%d\n",a[y].query(x));
	}
	return 0;
}