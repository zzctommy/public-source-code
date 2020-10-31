#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#pragma GCC optimize(3,"Ofast","inline")
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cmath>
using std::cout;
using std::endl;
using std::vector;
using std::lower_bound;
using std::unique;
using std::sort;
using std::max;
using std::min;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))f=(ch=='-'?0:f),ch=getchar();
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 200009
#define M 800
#define zky 1000000007
int n,a[N],m;
int s[M][M],sum[M];
int S,num,L[M],R[M],bl[N];

void inc(int&x,const int&v) {(x+=v)>=zky?x-=zky:114514;}

void init(){
	S=sqrt(n/3)+1,num=(n-1)/S+1;
	for(int i=1;i<=num;++i)L[i]=R[i-1]+1,R[i]=i*S;
	R[num]=n;
	for(int i=1;i<=num;++i)
		for(int j=L[i];j<=R[i];++j)
			bl[j]=i;
}

void update(int x,int y,int z){
	if(x>=S)for(int i=y;i<=n;i+=x)inc(a[i],z),inc(sum[bl[i]],z);
	else for(int i=y;i<=x;++i)inc(s[x][i],z);
}

int query(int x){
	int res=0;
	for(int i=1;i<S;++i)
		inc(res,1ll*(x/i)*s[i][i]%zky),inc(res,s[i][x%i]);
	return res;
}

int query(int l,int r){
	int res=0;
	if(bl[l]+2>bl[r]){
		for(int i=l;i<=r;++i)inc(res,a[i]);
		return res;
	}else {
		for(int i=l;i<=R[bl[l]];++i)inc(res,a[i]);
		for(int i=L[bl[r]];i<=r;++i)inc(res,a[i]);
		for(int i=bl[l]+1;i<bl[r];++i)inc(res,sum[i]);
		return res;
	}
}

signed main(){
	n=rd(),m=rd(),init();
	for(int i=1;i<=n;++i)a[i]=rd()%zky,sum[bl[i]]=(sum[bl[i]]+a[i])%zky;
	while(m--){
		int opt=rd(),x=rd(),y=rd();
		if(opt&1)update(x,y,rd()%zky);
		else printf("%d\n",((query(y)-query(x-1)+query(x,y))%zky+zky)%zky);
	}
	return 0;
}