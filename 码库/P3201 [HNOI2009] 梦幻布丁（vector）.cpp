#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define pb push_back
#define mkp(x,y) make_pair(x,y)
#define db double
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
const int M=1000005;
int n,m,a[N],F[M],ans,num[M<<1],cnt;
vector<int>v[M<<1];
void update(int x,int y){
	int x_=F[x],y_=F[y];
	if(x_==y_)return;
	if(v[x_].size()>v[y_].size())F[y]=x_,F[x]=0,swap(x_,y_);
	else F[x]=0;
	swap(x,x_),swap(y,y_);
	if(!x||!y||!v[x].size())return;
	int i=0,j=0;
	vector<int>fyyAKIOI;
	++cnt;
	v[cnt].push_back(v[x][i]<v[y][j]?v[x][i++]:v[y][j++]);
	ans-=num[x]+num[y];
	num[cnt]=1;
	while(i<v[x].size()&&j<v[y].size()){
		v[cnt].push_back(v[x][i]<v[y][j]?v[x][i++]:v[y][j++]);
		if(v[cnt][i+j-1]>v[cnt][i+j-2]+1)++num[cnt];
	}
	while(i<v[x].size()){
		v[cnt].push_back(v[x][i++]);
		if(v[cnt][i+j-1]>v[cnt][i+j-2]+1)++num[cnt];
	}
	while(j<v[y].size()){
		v[cnt].push_back(v[y][j++]);
		if(v[cnt][i+j-1]>v[cnt][i+j-2]+1)++num[cnt];
	}
	v[x].swap(fyyAKIOI),F[y_]=cnt,ans+=num[cnt];
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)v[a[i]=read()].push_back(i);
	for(int i=1;i<M;++i)F[i]=i;
	cnt=M+1;
	for(int i=1;i<M;++i){
		if(!v[i].size())continue;
		num[i]=1;
		for(int j=1;j<v[i].size();++j)if(v[i][j]>v[i][j-1]+1)++num[i];
		ans+=num[i];
	}
	while(m--){
		int opt=read(),x,y;
		if(opt==1){x=read(),y=read(),update(x,y);}
		else printf("%d\n",ans);
	}
	return 0;
}
