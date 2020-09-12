#include<bits/stdc++.h>
using namespace std;
#define rint register int
typedef long long LL;
inline int rd(){
   int x=0,f=1;
   char ch=getchar();
   while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
   while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
   return x*f;
}
const int N=500010;
const int L=720;
int n=N-10,m,len,a[N],blo[L][L];
void change(int x,int y) {
	for(rint i=1;i<=len;++i)blo[i][x%i]+=y;
	a[x]+=y;
}
int query(int x,int y) {
	if(x>len) {
		int res=0;
		for(rint i=y;i<=n;i+=x)res+=a[i];
		return res;
	} else return blo[x][y];
}
signed main() {
	m=rd();len=710;
	while(m--) {
		int opt=rd(),x=rd(),y=rd();
		if(opt==1) change(x,y);
		else printf("%d\n",query(x,y));
	}
	return 0;
}