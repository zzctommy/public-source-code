#include<bits/stdc++.h>
using namespace std;
const int N=200006;
int n,m,a[N],b[N],p[N],x[N],y[N],ans;
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&x[i]);
	for(int i=1;i<=m;++i)scanf("%d",&y[i]);
	for(int i=1;i<=n;++i)a[i]=x[i]-x[i+1];
	for(int i=1;i<m;++i)b[i]=y[i]-y[i+1];
	--m;
	int j=0;
	for(int i=2;i<=m;++i) {
		while(j&&b[j+1]!=b[i])j=p[j];
		if(b[j+1]==b[i])++j;
		p[i]=j;
	}
	j=0;
	for(int i=1;i<=n;++i) {
		while(j&&b[j+1]!=a[i])j=p[j];
		if(b[j+1]==a[i])++j;
		if(j==m)++ans,j=p[j];
	}
	printf("%d\n",ans);
	return 0;
}