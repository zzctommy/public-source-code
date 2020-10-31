#include<bits/stdc++.h>
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
char rdc(){
	char ch=getchar();
	while(ch!='A'&&ch!='D')ch=getchar();
	return ch;
}
#define pb push_back
#define sz(v) (int)v.size()
const int N=105;
int n,m,ans;
bool vis[N];
std::vector<int>A,D,V;
int solve1(){//不打完
	int res=0;
	for(int i=sz(V)-1,j=0;i>=0&&j<sz(A)&&V[i]>=A[j];--i,++j)res+=V[i]-A[j];
	return res;
}
int solve2(){//打完
	memset(vis,0,sizeof(vis));
	int i,j,res=0;
	for(i=0,j=0;j<sz(D);++i,++j){
		while(i<sz(V)&&(V[i]<=D[j]||vis[i]))++i;
		if(i>=sz(V))return 0;
		vis[i]=1;
	}
	for(i=0,j=0;j<sz(A);++i,++j){
		while(i<sz(V)&&(V[i]<A[j]||vis[i]))++i;
		if(i>=sz(V))return 0;
		vis[i]=1,res+=V[i]-A[j];
	}
	for(i=0;i<sz(V);++i)if(!vis[i])res+=V[i];
	return res;
}
signed main(){
	n=read(),m=read();
	for(int i=0;i<n;++i)
		if(rdc()=='A')A.pb(read());
		else D.pb(read());
	for(int i=0;i<m;++i)V.pb(read());
	std::sort(V.begin(),V.end());
	std::sort(A.begin(),A.end());
	std::sort(D.begin(),D.end());
	printf("%d\n",std::max(solve1(),solve2()));
}//