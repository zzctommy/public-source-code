#include<bits/stdc++.h>
int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=35;
int n,m,v[N][N],r[N][N],ans=-114514;
#define get(x,y) (r[x][y]?-v[x][y]:v[x][y])
int h(int x,int y,int d){
	r[x][y]=d;
	r[x+m][y]=r[m][y]^d;
	r[x][y+m]=r[x][m]^d;
	r[x+m][y+m]=r[m][y+m]^r[x][y+m];
	return get(x,y)+get(x+m,y)+get(x,y+m)+get(x+m,y+m);
}
int g(int y,int d){
	int res=0;
	r[m][y]=d;
	r[m][y+m]=r[m][m]^d;
	res+=get(m,y)+get(m,y+m);
	for(int i=1;i<m;++i)res+=std::max(h(i,y,0),h(i,y,1));
	return res;
}
int f(int msk){
	for(int i=0;i<m;++i)r[i+1][m]=msk>>i&1;
	for(int i=1;i<m;++i)r[i+m][m]=r[m][m]^r[i][m];
	int res=0;
	for(int i=1;i<=n;++i)res+=get(i,m);
	for(int i=1;i<m;++i)res+=std::max(g(i,0),g(i,1));
	return res;
}
signed main(){
    n=read(),m=(n+1)/2;
    for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			v[i][j]=read();
	for(int msk=0;msk<1<<m;++msk)ans=std::max(ans,f(msk));
	printf("%d\n",ans);
}