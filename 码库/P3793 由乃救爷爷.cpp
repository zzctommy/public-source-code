#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
namespace GenHelper {
	unsigned z1,z2,z3,z4,b;
	unsigned rand_() {
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
	}
}
void srand(unsigned x) {
	using namespace GenHelper;
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}
int read() {
	using namespace GenHelper;
	int a=rand_()&32767;
	int b=rand_()&32767;
	return a*32768+b;
}
const int N=20000010;
const int B=N/30;
int n,m,s,S,num,bel[N],L[B],R[B],a[N];
int st[21][B],suf[N],pre[N];
int bin[21],lg[N];
LL ans;
int query(int l,int r) {
	if(bel[l]==bel[r]) {
		int res=0;
		for(int i=l;i<=r;++i)res=res>a[i]?res:a[i];
		return res;
	}
	int res=max(suf[l],pre[r]);
	if(bel[l]+1==bel[r])return res;
	int x=lg[bel[r]-1-bel[l]];
	res=max(res,max(st[x][bel[l]+1],st[x][bel[r]-bin[x]]));
	return res;
}
signed main() {
	cin>>n>>m>>s;
	srand(s);
	S=4500,num=(n-1)/S+1;
	bin[0]=1;for(int i=1;i<=20;++i)bin[i]=bin[i-1]<<1;
	for(int i=1;i<=n;++i)a[i]=read(),bel[i]=(i-1)/S+1;
	lg[0]=-1;for(int i=1;i<=num;++i)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=num;++i)L[i]=(i-1)*S+1,R[i]=i*S;
	R[num]=n;
	for(int i=1;i<=num;++i) {
		pre[L[i]]=a[L[i]];for(int j=L[i]+1;j<=R[i];++j)pre[j]=max(pre[j-1],a[j]);
		suf[R[i]]=a[R[i]];for(int j=R[i]-1;j>=L[i];--j)suf[j]=max(suf[j+1],a[j]);
		st[0][i]=suf[L[i]];
	}
	for(int i=1;i<=lg[num];++i)
		for(int j=1;j+bin[i]-1<=num;++j)
			st[i][j]=max(st[i-1][j],st[i-1][j+bin[i-1]]);
	while(m--) {
		int l=read()%n+1,r=read()%n+1;
		if(l>r)l^=r^=l^=r;
		ans+=query(l,r);
	}
	cout<<ans<<endl;
	return 0;
}
/*
20000000 20000000 13249
*/