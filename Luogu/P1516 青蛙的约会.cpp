#include<bits/stdc++.h>
using namespace std;
int x,y,m,n,l,a,b,d,X,Y;
void exgcd(int a,int b,int &d,int &x,int &y) {
	if(!b) {
		d=a,x=1,y=0;return;
	}
	exgcd(b,a%b,d,y,x);
	y-=a/b*x;
}
signed main() {
	scanf("%d%d%d%d%d",&x,&y,&m,&n,&l);
	a=x-y,b=n-m;
	if(b<0)a*=-1,b*=-1;
	exgcd(b,l,d,X,Y);
	if(a%d)return puts("Impossible"),0;
	printf("%lld\n",(1ll*X*(a/d)%(l/d)+(l/d))%(l/d));
	return 0;
} 