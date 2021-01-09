#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
typedef double db;
typedef unsigned long long ull;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
#define int long long
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=200009;
int n,f,ans,sg[N];
bool vis[N];
int pri[N],cnt;
bitset<N>bs,bg,a[80];
int SG(int x) {
    for(int i=0;i<114514;++i)if(!a[i][x])return i;
    return 1919810;
}
void init() {
    for(int i=2;i<N;++i) {
        if(!vis[i])pri[++cnt]=i;
        for(int j=1;j<=cnt&&i*pri[j]<N;++j) {
            vis[i*pri[j]]=1;
            if(i%pri[j]==0)break;
        }
    }
    for(int i=1;i<=cnt;++i) {
        bs[pri[i]]=1;
        for(int j=i;j<=cnt;++j) {
            int t=pri[i]*pri[j];
            if(t>N) break;
            bs[t]=1;
        }
    }
    bs[f]=0;
    for(int i=0;i<N;++i)
        sg[i]=SG(i),a[sg[i]]|=bs<<i;
}
signed main() {
    n=rd(),f=rd();
    init();
    for(int i=1;i<=n;++i) {
        int x=rd(),y=rd(),z=rd();
        ans^=sg[z-y-1]^sg[y-x-1];
    }
    puts(ans?"Alice\nBob":"Bob\nAlice");
    return 0;
}