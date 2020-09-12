#include<bits/stdc++.h>
using namespace std;
inline int rd(){
	int f=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=200009;
int n,m,F[N],now;
int find(int x){return x==F[x]?x:F[x]=find(F[x]);}
signed main() {
	now=n=rd(),m=rd();
	for(int i=1;i<=n;++i)F[i]=i;
	while(m--) {
		int l=rd(),r=find(rd());
		while(l<=r) {
			F[find(r)]=find(r-1),r=find(r),--now;
		}
		printf("%d\n",now);
	}
	return 0;
}