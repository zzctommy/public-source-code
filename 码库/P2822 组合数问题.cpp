#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=2005;
int T,k,n,m,C[N][N];
void init(const int N=2000){
	C[0][0]=1;
	for(int i=1;i<=N;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j)C[i][j]=(C[i-1][j]+C[i-1][j-1])%k;
	}
	// for(int i=0;i<=10;++i){
	// 	for(int j=0;j<=10;++j)std::cerr<<C[i][j]<<' ';
	// 	std::cerr<<'\n';
	// }
	// std::cerr<<'\n';
	for(int i=0;i<=N;++i)
		for(int j=0;j<=i;++j)C[i][j]=!C[i][j];
	// for(int i=0;i<=10;++i){
	// 	for(int j=0;j<=10;++j)std::cerr<<C[i][j]<<' ';
	// 	std::cerr<<'\n';
	// }
	// std::cerr<<'\n';
	for(int i=0;i<=N;++i)
		for(int j=0;j<=N;++j){
			if(i)C[i][j]+=C[i-1][j];
			if(j)C[i][j]+=C[i][j-1];
			if(i&&j)C[i][j]-=C[i-1][j-1];
		}
	// for(int i=0;i<=10;++i){
	// 	for(int j=0;j<=10;++j)std::cerr<<C[i][j]<<' ';
	// 	std::cerr<<'\n';
	// }
}
signed main(){
	T=read(),k=read();
	init();
	while(T--)n=read(),m=read(),printf("%d\n",C[n][m]);
	return 0;
}
/*
2 5
4 5
6 7

*/