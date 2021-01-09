#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
#define N 4500
int n,mod;
map<int,int>A;
vector<int>ans;
signed main(){
	n=read(),mod=read();
	ans.pb(1),A[-1]=0,A[0]=2;
	int k=0,e=1;
	for(int i=0;i<=n;++i){
		int am=0;A[k+e]=0,e=-e;
		for(int j=0;j<=i;++j)(am+=A[k])%=mod,A[k]=am,k+=e;
		if(i>1)i%2==0?ans.pb(A[-i/2]):ans.pb(A[i/2]);
	}
	printf("%d\n",ans[n-1]);
}