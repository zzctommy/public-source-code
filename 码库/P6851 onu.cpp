#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
int n,m,c,ans[N];
LL sum;
vector<pair<int,int> >v[N],p[N];
bool book[N];
#define X(v) (v).first
#define Y(v) (v).second
signed main(){
	n=read(),m=read(),c=read(),sum=read();
	for(int i=1;i<=n;++i){
		int a=read(),b=read();
		v[a].pb(mkp(b,i));
	}
	for(int i=1;i<=m;++i){
		int a=read(),b=read();
		p[a].pb(mkp(b,i));
	}
	for(int i=1;i<N;++i){
		if(!p[i].size())continue;
		sort(v[i].begin(),v[i].end()),reverse(v[i].begin(),v[i].end());
		sort(p[i].begin(),p[i].end()),reverse(p[i].begin(),p[i].end());
		int j=0,k=0;
		while(j<v[i].size()&&k<p[i].size()){
			if(X(v[i][j])>=X(p[i][k]))sum+=X(v[i][j])+c,book[Y(p[i][k])]=1,ans[Y(p[i][k])]=Y(v[i][j]),++j;
			++k;
		}
		k=0;
		while(j<v[i].size()&&k<p[i].size()){
			while(k<p[i].size()&&book[Y(p[i][k])])++k;
			if(j==p[i].size())break;
			sum+=X(v[i][j])-c,ans[Y(p[i][k])]=Y(v[i][j]),book[Y(p[i][k])]=1;
			++j,++k;
		}
		for(k=0;k<p[i].size();++k)if(!book[Y(p[i][k])])ans[Y(p[i][k])]=-1,sum-=c;
	}
	printf("%lld\n",sum);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}