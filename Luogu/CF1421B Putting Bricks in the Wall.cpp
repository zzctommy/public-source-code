#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int rdc() {
	char ch=getchar();
	while(ch!='0'&&ch!='1'&&ch!='S'&&ch!='F')ch=getchar();
	if(ch=='0')return 0;
	if(ch=='1')return 1;
	return -1;
}
const int N=205;
int n,mp[N][N];
void Main(){
	n=read();
	vector<int>X,Y;
	int cnt[2][2];
	cnt[0][1]=cnt[0][0]=cnt[1][1]=cnt[1][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			mp[i][j]=rdc();
	++cnt[0][mp[1][2]],++cnt[0][mp[2][1]],++cnt[1][mp[n][n-1]],++cnt[1][mp[n-1][n]];
	if(2-cnt[0][1]+2-cnt[1][0]<=2){
		if(mp[1][2]!=1)X.push_back(1),Y.push_back(2);
		if(mp[2][1]!=1)X.push_back(2),Y.push_back(1);
		if(mp[n-1][n]!=0)X.push_back(n-1),Y.push_back(n);
		if(mp[n][n-1]!=0)X.push_back(n),Y.push_back(n-1);
	} else{
		if(mp[1][2]!=0)X.push_back(1),Y.push_back(2);
		if(mp[2][1]!=0)X.push_back(2),Y.push_back(1);
		if(mp[n-1][n]!=1)X.push_back(n-1),Y.push_back(n);
		if(mp[n][n-1]!=1)X.push_back(n),Y.push_back(n-1);
	}
	printf("%d\n",(int)X.size());
	for(int i=0;i<X.size();++i)printf("%d %d\n",X[i],Y[i]);
}
signed main(){
	for(int T=read();T;--T)Main();
}
/*
3
4
S010
0001
1000
111F
3
S10
101
01F
5
S0101
00000
01111
11111
0001F

*/