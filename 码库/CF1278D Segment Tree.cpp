#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int fa[N],n,flag=1,sum,mp[N<<1],c[N];
struct node{
	int op,id;
}a[N<<1];
set<int>s;
int find(int x) {
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=1,x,y;i<=n;++i) {
		scanf("%d%d",&x,&y);
		a[x].op=1,a[x].id=i;
		a[y].op=0,a[y].id=i;
		mp[x]=mp[y]=i;c[i]=y;
	}
	for(int i=1;i<=n*2;++i) {
		if(!a[i].op){
			s.erase(c[a[i].id]);
			continue;
		}
		for(set<int>::iterator it=s.begin();it!=s.end()&&*it<=c[a[i].id];++it) {
			int x=find(a[i].id),y=find(mp[*it]);
			if(x==y)return puts("NO"),0;
			fa[x]=y,++sum;
			if(sum>=n)return puts("NO"),0;
		}
		s.insert(c[a[i].id]);
	}
	if(sum<n-1)return puts("NO"),0;
	return puts("YES"),0;
}