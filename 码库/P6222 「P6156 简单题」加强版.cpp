#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double db;
typedef unsigned int unt;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline unt read() {
	unt x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x;
}
const int N=20000005;
unt T,n,k;
unt pw[N],f[N], pri[1270610], cnt;
bool vis[N];
unt qpow(unt n,unt k,unt res=1){
	for(;k;k>>=1,n=n*n)if(k&1)res=res*n;
	return res;
}
void init(const unt&N){
	pw[1]=1,f[1]=1;
	for(unt i=2;i<=N;++i){
		if (!vis[i]) pri[++cnt] = i, pw[i] = qpow(i, k), f[i] = i - 1;
		for (unt j = 1; j <= cnt && i * pri[j] <= N; ++ j) {
			vis[i * pri[j]] = 1, pw[i * pri[j]] = pw[i] * pw[pri[j]];
			if (i % pri[j] == 0) {
				if(i / pri[j] % pri[j]) f[i * pri[j]] = - f[i / pri[j]] * pri[j];
				break;
			}
			pw[i * pri[j]] = pw[i] * pw[pri[j]], f [i * pri[j]] = f[i] * f[pri[j]];
		}
	}
	for(unt i=1;i<=N;++i)f[i]=pw[i]*f[i]+f[i-1],pw[i]=pw[i]+pw[i-1];
	for(unt i=1;i<=N;++i)pw[i]=pw[i-1]+pw[i];
}
unt query(unt n){
	unt res=0;
	for(unt l=1,r;l<=n;l=r+1)
		r=n/(n/l),res=(res+(pw[(n/l)<<1]-(pw[n/l]<<1))*(f[r]-f[l-1]));
	return res;
}
signed main(){
	T = read(), n=read(), k = read(),init(n<<1);
	while(T--)printf("%u\n",query(read()));
}