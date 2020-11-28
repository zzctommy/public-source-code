#include<bits/stdc++.h>
using namespace std;
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 100005
#define LOG 18
#define inf 20000000000000ll//2e13
int n,h[N],m;
int A[N][LOG],lg[N],B[N];
LL d[N][LOG],S[N][LOG],dB[N];
void init(){
	multiset<pair<LL,int> >s;
	s.insert(mkp(inf,0)),s.insert(mkp(inf,0)),s.insert(mkp(-inf,0)),s.insert(mkp(-inf,0));
	for(int i=n;i>=1;--i){
		set<pair<LL,int> >::iterator it;
		it=s.lower_bound(mkp(h[i],114514)),++it;
		pair<LL,int> x=*it--,y=*it--,z=*it--,k=*it;
		if(h[i]-z.fi<=y.fi-h[i]){
			B[i]=z.se,dB[i]=h[i]-z.fi;
			if(h[i]-k.fi<=y.fi-h[i])A[i][0]=k.se,d[i][0]=h[i]-k.fi;
			else A[i][0]=y.se,d[i][0]=y.fi-h[i];
		}else {
			B[i]=y.se,dB[i]=y.fi-h[i];
			if(h[i]-z.fi<=x.fi-h[i])A[i][0]=z.se,d[i][0]=h[i]-z.fi;
			else A[i][0]=x.se,d[i][0]=x.fi-h[i];
		}
		s.insert(mkp(h[i],i));
	}
	lg[0]=-1;for(int i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;++i)
		A[i][1]=B[A[i][0]],d[i][1]=d[i][0],
		S[i][0]=d[i][0],S[i][1]=S[i][0]+dB[A[i][0]];
	for(int j=2;j<=lg[n];++j)
		for(int i=1;i<=n;++i)
			A[i][j]=A[A[i][j-1]][j-1],d[i][j]=d[i][j-1]+d[A[i][j-1]][j-1],
			S[i][j]=S[i][j-1]+S[A[i][j-1]][j-1];
	h[0]=-1e9-114514;
}
pair<LL,LL>solve2(int s,int x){
	int u=s;LL sumA=0,sum=0;
	for(int i=lg[n];i>=0;--i)if(A[u][i]&&S[u][i]+sum<=x)sumA+=d[u][i],sum+=S[u][i],u=A[u][i];
	return mkp(sumA,sum-sumA);
}
const db eps=1e-10;
void solve1(){
	int x=read();
	pair<LL,LL>now=mkp(114514,0);
	int res=0;
	for(int i=1;i<=n;++i){
		pair<LL,LL>tmp=solve2(i,x);
		if(!tmp.se&&!now.se){
			if(h[i]>h[res])res=i,now=tmp;
		}else if(tmp.se){
			if(1.*now.fi/now.se>1.*tmp.fi/tmp.se)res=i,now=tmp;
		}
	}
	printf("%d\n",res);
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)h[i]=read();
	init();
	solve1();
	for(m=read();m;--m){
		int s=read(),x=read();
		pair<LL,LL>tmp=solve2(s,x);
		printf("%lld %lld\n",tmp.fi,tmp.se);
	}
	return 0;
}