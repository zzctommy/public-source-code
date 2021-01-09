//Orz cyn2006
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
const int N=10005;
const db eps=1e-7;
const db pi=acos(-1.0);
int n,tot,stk[N],top;
db a,b,r,ans;
struct vec{
	db x,y;
	vec(){x=y=0;}
	vec(db x_,db y_){x=x_,y=y_;}
	vec operator + (const vec&t)const{return vec(x+t.x,y+t.y);}
	vec operator - (const vec&t)const{return vec(x-t.x,y-t.y);}
	db operator * (const vec&t){return x*t.x+y*t.y;}
	db operator & (const vec&t){return x*t.y-y*t.x;}
	friend db dis(const vec&a,const vec&b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
}p[N<<2];
inline bool cmp(const vec&a,const vec&b){
	db tmp=(a-p[1])&(b-p[1]);
	if(tmp>0)return 1;
	if(fabs(tmp)<eps)return dis(p[0],a)<dis(p[0],b);
	return 0;
}
signed main(){
	scanf("%d%lf%lf%lf",&n,&a,&b,&r),a-=2*r,b-=2*r;
	rep(i,1,n){
		db x,y,k,X,Y;scanf("%lf%lf%lf",&x,&y,&k);
		X=-b/2,Y=-a/2,p[++tot]=vec(x+X*cos(k)-Y*sin(k),y+X*sin(k)+Y*cos(k));
		X=-b/2,Y=a/2,p[++tot]=vec(x+X*cos(k)-Y*sin(k),y+X*sin(k)+Y*cos(k));
		X=b/2,Y=-a/2,p[++tot]=vec(x+X*cos(k)-Y*sin(k),y+X*sin(k)+Y*cos(k));
		X=b/2,Y=a/2,p[++tot]=vec(x+X*cos(k)-Y*sin(k),y+X*sin(k)+Y*cos(k));
	}
	//rep(i,1,tot)cerr<<p[i].x<<' '<<p[i].y<<'\n';
	//puts("--------------------");
	int tmp=1;
	rep(i,2,tot){
		if(p[i].x<p[tmp].x)tmp=i;
		else if(fabs(p[i].x-p[tmp].x)<eps&&p[i].y<p[tmp].y)tmp=i;
	}
	swap(p[1],p[tmp]),sort(p+2,p+tot+1,cmp);
	for(int i=1;i<=tot;++i){
		while(top>1&&((p[stk[top]]-p[stk[top-1]])&(p[i]-p[stk[top-1]]))<eps)--top;
		stk[++top]=i;
	}
	//rep(i,1,top)cerr<<p[stk[i]].x<<' '<<p[stk[i]].y<<'\n';
	ans=2*pi*r;
	//cerr<<ans<<'\n';
	rep(i,1,top)ans+=dis(p[stk[i]],p[stk[i%top+1]]);
	printf("%.2lf\n",ans);
	return 0;
}