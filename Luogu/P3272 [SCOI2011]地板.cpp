#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(a) push_back(a)
#define mkp(a,y) make_pair(a,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
    int a=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))a=a*10+(ch^48),ch=getchar();
    return a*f;
}
int rdc() {
	char ch=getchar();
	while(ch!='_'&&ch!='*')ch=getchar();
	return ch=='_';
} 
const int mod=20110520;
const int hash_mod=1999999;
int n,m,a[114][514],edx,edy,inc[22],ans;
int cnt[1<<21],val[2][1<<21],sum[2][1<<21],head[hash_mod],nxt[1<<21],now,lst;
void turn() {
	int b[114][514];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			b[j][i]=a[i][j];
	n^=m^=n^=m;
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=b[i][j];
}
void insert(int mask,int num) {
	int u=mask%hash_mod;
	for(int i=head[u];i;i=nxt[i])
		if(val[now][i]==mask)return sum[now][i]=(sum[now][i]+num)%mod,void();
	++cnt[now];
	nxt[cnt[now]]=head[u];
	head[u]=cnt[now];
	val[now][cnt[now]]=mask;
	sum[now][cnt[now]]=num%mod;
}
signed main() {
	n=rd(),m=rd();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=rdc();
	if(n<m)turn();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j])edx=i,edy=j;
	inc[0]=1;
	for(int i=1;i<=20;++i)inc[i]=inc[i-1]<<2;
	now=1,lst=0,cnt[1]=1,val[1][1]=0,sum[1][1]=1;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=cnt[now];++j)val[now][j]<<=2;
		for(int j=1;j<=m;++j) {
			memset(head,0,sizeof(head)),lst^=1,now^=1,cnt[now]=0;
			for(int k=1;k<=cnt[lst];++k) {
				int mask=val[lst][k],num=sum[lst][k];
				int b1=(mask>>((j-1)*2))%4,b2=(mask>>(j*2))%4;//right;down
				if(!a[i][j]) {
					if(!b1&&!b2)insert(mask,num);
				} else if(!b1&&!b2) {
					if(a[i+1][j]&&a[i][j+1])insert(mask+inc[j-1]*2+inc[j]*2,num);
					if(a[i+1][j])insert(mask+inc[j-1],num);
					if(a[i][j+1])insert(mask+inc[j],num);
				} else if(b1==1&&!b2) {
					if(a[i+1][j])insert(mask+inc[j-1],num);
					if(a[i][j+1])insert(mask-inc[j-1]+inc[j],num);
				} else if(!b1&&b2==1){
					if(a[i+1][j])insert(mask-inc[j]+inc[j-1],num);
					if(a[i][j+1])insert(mask+inc[j],num);
				} else if(b1==2&&!b2) {
					if(i==edx&&j==edy)ans=(ans+num)%mod;
					insert(mask-inc[j-1]*2,num);
					if(a[i][j+1])insert(mask-inc[j-1]*2+inc[j]*2,num);
				} else if(!b1&&b2==2) {
					if(i==edx&&j==edy)ans=(ans+num)%mod;
					insert(mask-inc[j]*2,num);
					if(a[i+1][j])insert(mask-inc[j]*2+inc[j-1]*2,num);
				} else if(b1==1&&b2==1) {
					if(i==edx&&j==edy)ans=(ans+num)%mod;
					insert(mask-inc[j]-inc[j-1],num);
				}
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
} 