#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define sz(v) (int)v.size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f?x:-x;
}
const int N=55;
int n,w[N][N],mch[N<<1],kth[N<<1],rk[N<<1][N<<1],ID;
vector<int>e[N<<1];
bool cmp1(const int&a,const int&b){return w[ID][a-n]>w[ID][b-n];}
bool cmp2(const int&a,const int&b){return w[a][ID-n]<w[b][ID-n];}
void init(){//稳定婚姻问题模板
	fill(mch+1,mch+n*2+1,0),fill(kth+1,kth+n*2+1,0);
    queue<int>q;
	rep(i,1,n){
		e[i].resize(n+1),e[i+n].resize(n+1);//每一个点的匹配边大小是 n
		rep(j,1,n)e[i][j]=j+n,e[i+n][j]=j;//拉边
		ID=i,sort(e[i].begin()+1,e[i].begin()+n+1,cmp1);
		ID=i+n,sort(e[i+n].begin()+1,e[i+n].begin()+n+1,cmp2);//两边的点对于“优”的定义不同
		rep(j,1,n)rk[i][e[i][j]]=j,rk[i+n][e[i+n][j]]=j;//处理对于 i 这个节点的所有可能的匹配 j 在 i 看来的优秀程度
        q.push(i);
	}
	while(!q.empty()){
		bool flg=0;
        int u=q.front();q.pop();
		int v=e[u][++kth[u]];//kth 是 u 当前最优的匹配排名
		if(!mch[v])mch[u]=v,mch[v]=u;//v 还没有匹配
		else if(rk[v][u]<rk[v][mch[v]]){
            if(mch[v]<=n)q.push(mch[v]);
            mch[mch[v]]=0,mch[v]=u,mch[u]=v;//v 认为 u 更优
        }else q.push(u);
	}
}
void Main(){
	scanf("%d",&n);
	rep(i,1,n)rep(j,1,n)w[i][j]=read();
	printf("B\n"),fflush(stdout);
	char fyyAK[5];int x;
	scanf("%s%d",fyyAK,&x);
	if((fyyAK[0]=='I')^(x>n))rep(i,1,n)rep(j,1,n)w[i][j]*=-1;
	init();
	while("fyy txdy"){//只能膜拜！
		printf("%d\n",mch[x]),fflush(stdout);
		scanf("%d",&x);if(!~x)break;
	}
}
signed main(){for(int T=read();T;--T)Main();}