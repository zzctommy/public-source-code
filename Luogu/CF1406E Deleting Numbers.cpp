#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,x=1,a[N],now;
int pri[N/10],cnt,vis[N];
vector<int>f;
void Sieve(int n) {
	for(int i=2; i<=n; ++i) {
		if(!vis[i])pri[++cnt]=i;
		for(int j=1; j<=cnt&&i*pri[j]<=n; ++j) {
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
}
signed main() {
	scanf("%d",&n),now=n;
	for(int i=1;i<=n;++i)a[i]=1;
	Sieve(n);
	int p=sqrt(n),it=1,t;
	while(pri[it]<=p)++it;
	for(int i=it,flg=0; i<=cnt; i+=100) {
		for(int j=i,mx=min(i+99,cnt); j<=mx; ++j) {
			printf("B %d\n",pri[j]);
			fflush(stdout);
			scanf("%d",&t);
			for(int k=1; k*pri[j]<=n; ++k)if(a[k*pri[j]])a[k*pri[j]]=0,--now;
		}
		printf("A 1\n");
		fflush(stdout);
		scanf("%d",&t);
		if(t!=now) {
			for(int j=i,mx=min(i+99,cnt); j<=mx; ++j) {
				printf("A %d\n",pri[j]);
				fflush(stdout);
				scanf("%d",&t);
				if(t){x*=pri[j];flg=1;break;}
			}
		}
		if(flg)break;
	}
	it=1;
	while(it<=cnt&&pri[it]<=p) {
		printf("B %d\n",pri[it]);
		fflush(stdout);
		scanf("%d",&t);
		printf("A %d\n",pri[it]);
		fflush(stdout);
		scanf("%d",&t);
		if(t)f.push_back(pri[it]);
		++it;
	}
	for(int i:f) {
		x*=i;
		int r=i*i;
		while(r<=n) {
			printf("A %d\n",r);
			fflush(stdout);
			scanf("%d",&t);
			if(t)x*=i;
			else break;
			r*=i;
		}
	}
	printf("C %d\n",x);
	fflush(stdout);
}
