#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define db double
#define N 100005

inline bool down(int&x,const int y){
	return x>y?x=y,1:0;
}

int n,a[N],cnt,ans;

int main(){
	std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
	std::cin>>n;
	rep(i,1,n)std::cin>>a[i];
	std::sort(a+1,a+n+1);
	rep(i,1,n-1)
		if(a[i]==a[i+1]){
			if(a[i])++cnt,--a[i];
			else return std::cout<<"cslnb\n",0;
		}
	if(cnt>1)return std::cout<<"cslnb\n",0;
	rep(i,1,n-1)if(a[i]==a[i+1])return std::cout<<"cslnb\n",0;
	rep(i,1,n)cnt+=a[i]-i+1;
	if(cnt&1)std::cout<<"sjfnb\n";
	else std::cout<<"cslnb\n";
}