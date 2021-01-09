#include<bits/stdc++.h>
using namespace std;
const int N=51;
int n,mp[N][N],cans,cnum[N];
inline int read()
{
	char ch=getchar();
	while(ch!='1'&&ch!='0')ch=getchar();
	return ch-'0';
}
bool dfs(int step,int *e,int nume){
	if(step>cans){cans=step;return true;}
	int e1[N],nume1=0;
	for(int i=1;i<=nume;++i){
		if(step+nume-i+1<=cans)break;
		if(step+cnum[e[i]]<=cans)break;
		nume1=0;
		for(int j=i+1;j<=nume;++j)
		if(mp[e[i]][e[j]])e1[++nume1]=e[j];
		if(dfs(step+1,e1,nume1))return true;
	}
	return false;
}
inline void maxclique(){
	int e[N],nume;
	cnum[n]=1;cans=1;
	for(int i=n-1;i>=1;--i){
		nume=0;cnum[i]=1;
		for(int j=i+1;j<=n;j++)
			if(mp[i][j])e[++nume]=j;
		dfs(1,e,nume);
		cnum[i]=cans;
	}
}//cans为最大团大小