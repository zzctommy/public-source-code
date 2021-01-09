#include<bits/stdc++.h>
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
const int N=100005;
int n,m,k,ans,idl,idr;
int lg[N],pw[30];
struct ST_TABLE{
	int ST[20][N];
	void init(){
		for(int i=1;i<=lg[n];++i)
			for(int j=1;j+pw[i]-1<=n;++j)
				ST[i][j]=std::max(ST[i-1][j],ST[i-1][j+pw[i-1]]);
	}
	int ask(int l,int r){int t=lg[r-l+1];return std::max(ST[t][l],ST[t][r-pw[t]+1]);}
}ST[5];
void init(){
	pw[0]=1,lg[0]=-1;
	for(int i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=25;++i)pw[i]=pw[i-1]<<1;
}
int ask(int l,int r){
	int res=0;
	for(int i=0;i<m;++i)res+=ST[i].ask(l,r);
	return res;
}
signed main(){
	n=read(),m=read(),k=read(),init();
	for(int i=1;i<=n;++i)
		for(int j=0;j<m;++j)ST[j].ST[0][i]=read();
	for(int i=0;i<m;++i)ST[i].init();
	for(int i=1;i<=n;++i){
		int l=1,r=i,res=n+1919810;
		while(l<=r){
			int mid=(l+r)>>1;
			if(ask(mid,i)<=k)res=mid,r=mid-1;
			else l=mid+1;
		}
		if(i-res+1>ans)ans=i-res+1,idl=res,idr=i;
	}
	if(!ans)for(int i=0;i<m;++i)printf("0 ");
	else for(int i=0;i<m;++i)printf("%d ",ST[i].ask(idl,idr));
	return 0;
}