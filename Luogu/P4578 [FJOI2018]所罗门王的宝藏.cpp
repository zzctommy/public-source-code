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
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int N=2009;
const int M=N*2;
const int inf=1000000007;
int n,m,k;
int num_edge,head[N];
struct edge {
    int nxt,to,val;
}e[M];
int dis[N],num[N],inq[N];
void addedge(int fr,int to,int val) {
    ++num_edge;
    e[num_edge].val=val;
    e[num_edge].to=to;
    e[num_edge].nxt=head[fr];
    head[fr]=num_edge;
}
void clear() {
    num_edge=0;
    memset(head,0,sizeof(head));
}
bool spfa() {
    for(int i=0;i<=n+m;++i)dis[i]=inf,num[i]=0,inq[i]=0;
    queue<int>q;
    q.push(0),dis[0]=0,num[0]=1;
    while(!q.empty()){
        int u=q.front();q.pop(),inq[u]=0;
        for(int i=head[u];i;i=e[i].nxt) {
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].val) {
                dis[v]=dis[u]+e[i].val,++num[v];
                if(num[v]>n+m)return 0;
                if(!inq[v])inq[v]=1,q.push(v);
            }
        }
    }
    return 1;
}
void Main() {
    clear();
    n=rd(),m=rd(),k=rd();
    for(int i=1;i<=k;++i) {
        int x=rd(),y=rd(),z=rd();
        addedge(x,y+n,z),addedge(y+n,x,-z);
    }
    for(int i=1;i<=n+m;++i)addedge(0,i,0);
    puts(spfa()?"Yes":"No");
}
signed main(){for(int T=rd();T;--T)Main();}