#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define db double
#define N 100005

inline bool down(int&x,const int y){
	return x>y?x=y,1:0;
}

int a,b;
signed main(){
	std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
	std::cin>>a>>b;
	if(a>b)std::swap(a,b);
	int k=b-a;
	int t=1.*k*(sqrt(5)+1)/2;
	if(t==a)puts("0");
	else puts("1");
}