#include<bits/stdc++.h>
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
const int N=200005;
const int M=530005;
const int mod=998244353;
int qpow(int n,int k){
	int res=1;
	for(;k;k>>=1,n=1ll*n*n%mod)if(k&1)res=1ll*n*res%mod;
	return res;
}
const int G=3;
const int IG=qpow(G,mod-2);
int n,m,k,sum[N],ans,A[M],B[M];
char s1[N],s2[N];
int lim,lg,rev[M];
void init(int n){
	for(lg=0,lim=1;lim<n;lim<<=1,++lg);
	for(int i=0;i<lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
}
void NTT(int*a,int g,int op=0){
	for(int i=0;i<lim;++i)if(i>rev[i])std::swap(a[i],a[rev[i]]);
	for(int i=1;i<lim;i<<=1){
		int wn=qpow(g,(mod-1)/(i<<1));
		for(int j=0;j<lim;j+=i<<1){
			int w0=1;
			for(int k=0;k<i;++k,w0=1ll*w0*wn%mod){
				int X=a[j+k],Y=1ll*w0*a[i+j+k]%mod;
				a[j+k]=(X+Y)%mod,a[i+j+k]=(X-Y+mod)%mod;
			}
		}
	}
	if(!op)return;int ilim=qpow(lim,mod-2);
	for(int i=0;i<lim;++i)a[i]=1ll*a[i]*ilim%mod;
}
void calc(char ch){
	memset(A,0,sizeof(A)),memset(B,0,sizeof(B));
	for(int i=0;i<n;++i){
		if(s1[i]==ch){
			A[i]=1;
			for(int j=i-1;j>=i-k&&j>=0&&!A[j];--j)A[j]=1;
			for(int j=std::min(n-1,i+k);j>=i+1&&!A[j];--j)A[j]=1;
		}
	}
	for(int i=0;i<m;++i)B[i]=s2[m-i-1]==ch;
	NTT(A,G),NTT(B,G);
	for(int i=0;i<lim;++i)A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,IG,1);
	for(int i=0;i<n;++i)sum[i]+=A[i];
}
signed main(){
	n=read(),m=read(),k=read(),scanf("%s%s",s1,s2);
	init(n+m);
	calc('A'),calc('G'),calc('C'),calc('T');
	for(int i=0;i<n;++i)if(sum[i]==m)++ans;
	printf("%d\n",ans);
}