#include<bits/stdc++.h>
using namespace std;
inline int rd(){
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int M=(1<<22)+5;
const int N=23;
int n,m,a[M],ans=0;
bool vis[M];
void dfs(int msk) {
	if(vis[msk])return;
	vis[msk]=1;
	for(int i=0;i<n;++i)if(msk>>i&1)dfs(msk^(1<<i));
	if(a[msk])dfs((1<<n)-1-msk);
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=m;++i)a[rd()]=1;
	for(int i=0;i<(1<<n);++i) {
		if(vis[i]||!a[i])continue;
		dfs((1<<n)-1-i),++ans;
	}
	cout<<ans<<endl;
	return 0;
}