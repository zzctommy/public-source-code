#include<bits/stdc++.h>
#define ll long long
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define mod 1000000007
typedef std::pair<int,int> pii;
inline int upd(const int x){return x+(x>>31&mod);}
inline void reduce(int&x){x-=mod,x+=x>>31&mod;}
inline void add(int&x,const int y){x=upd((x+y)%mod);}
#define N 2005

const int inf=0x3f3f3f3f;
int n,m,T,mxv,ans,dis[N][N];
std::pair<int,int>li[N];
int et,hed[N];
struct edge{int nx,to,vl;}e[N<<1];
struct node{
	int x,y,z;
	node(int x_,int y_,int z_){x=x_,y=y_,z=z_;}
};
std::vector<node>E;
void adde(int u,int v,int d){e[++et].nx=hed[u],e[et].to=v,e[et].vl=d,hed[u]=et;}
void Dij(){
	static bool vis[N][N];
	memset(vis,0,sizeof(vis));
	memset(dis,-1,sizeof(dis));
	std::queue<std::pair<int,int> >q;
	q.push(std::make_pair(1,dis[1][0]=0)),vis[1][0]=1;
	while(!q.empty()){
		std::pair<int,int>now=q.front();q.pop();
		int u=now.first,t=now.second;
		if(t==n)continue;
		for(int i=hed[u];i;i=e[i].nx){
			int v=e[i].to;
			if(dis[v][t+1]<dis[u][t]+e[i].vl){
				dis[v][t+1]=dis[u][t]+e[i].vl;
				if(!vis[v][t+1])q.push(std::make_pair(v,t+1)),vis[v][t+1]=1;
			}
		}
	}
}
int calc(ll a1,ll d,ll n){
	static const int iv2=(mod+1)>>1;
	return 1ll*(a1+a1+(n-1)*d)%mod*n%mod*iv2%mod;
}
signed main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0),std::cout.tie(0);
	std::cin>>n>>m>>T;
	E.push_back(node(114,514,1919810));
	rep(i,1,m){
		int x,y,z;
		std::cin>>x>>y>>z;
		adde(x,y,z),adde(y,x,z),E.push_back(node(x,y,z)),mxv=std::max(mxv,z);
	}
	Dij();
	rep(i,1,m)li[i].second=-2e9-5,li[i].first=E[i].z;
	rep(i,1,std::min(n,T)){
		rep(j,1,m){
			int x=E[j].x,y=E[j].y,z=E[j].z;
			if(~dis[x][i])li[j].second=std::max(dis[x][i]-i*z,li[j].second);
			if(~dis[y][i])li[j].second=std::max(dis[y][i]-i*z,li[j].second);
		}
		ll res=0;
		rep(j,1,m)res=std::max(res,1ll*li[j].first*i+li[j].second);
		reduce(ans+=res%mod);
	}
	rep(i,1,m){
		int L=n+1,R=T;
		rep(j,1,m){
			if(i==j)continue;
			if(L>R)break;
			if(li[i].first==li[j].first){
				if(li[i].second<li[j].second){R=114514,L=1919810;break;}
				else if(li[i].second==li[j].second&&i>j){R=114514,L=1919810;break;}
				else continue;
			}
			if(li[i].first>li[j].first)L=std::max(L,(li[j].second-li[i].second)/(li[i].first-li[j].first)+1);
			else R=std::min(R,(li[j].second-li[i].second)/(li[i].first-li[j].first));
		}
		if(L>R)continue;
		reduce(ans+=calc(1ll*li[i].first*L%mod+li[i].second,li[i].first,R-L+1));
	}
	std::cout<<ans<<'\n';
	return 0;
}