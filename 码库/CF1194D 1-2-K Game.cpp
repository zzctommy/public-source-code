#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define db double
#define N 1005

inline bool down(int&x,const int y){
	return x>y?x=y,1:0;
}

int T,n,k,sg[300];

int main(){
	std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
	std::cin>>T;
	while(T--){
		std::cin>>n>>k;
		if(k%3)puts(n%3==0?"Bob":"Alice");
		else{
			n=(n-1)%(k+1)+1;
			if(n==k+1)puts("Bob");
			else if(n==k)puts("Alice");
			else if(n%3==0)puts("Bob");
			else puts("Alice");
		}
		// rep(i,1,40){
		// 	sg[i]=0;
		// 	if(i>=1)sg[i]|=!sg[i-1];
		// 	if(i>=2)sg[i]|=!sg[i-2];
		// 	if(i>=k)sg[i]|=!sg[i-k];
		// 	std::cout<<sg[i]<<' ';
		// }
		// std::cout<<std::endl;
	}
}