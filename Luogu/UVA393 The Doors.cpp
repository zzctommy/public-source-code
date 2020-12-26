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
const int N=85;
const db eps=1e-9;
const db inf=1e12;
int n;
db x[N],a[4][N],mp[N][N];
int id(int x,int y){return (x-1)*4+y+1;}
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
db dis(db a1,db b1,db a2,db b2){return sqrt((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2));}
void Main(){
	n=read();
	if(!~n)exit(0);
	rep(i,0,n*4+1)rep(j,0,n*4+1)mp[i][j]=inf;
	rep(i,1,n){
		scanf("%lf%lf%lf%lf%lf",&x[i],&a[0][i],&a[1][i],&a[2][i],&a[3][i]);
		rep(j,1,i-1){
			rep(o,0,3)rep(p,0,3){
				db k=(a[o][i]-a[p][j])/(x[i]-x[j]),b=a[o][i]-k*x[i];bool flg=1;
				rep(l,j+1,i-1){
					db tmp=k*x[l]+b;
					if(tmp<a[0][l]||(a[1][l]<tmp&&tmp<a[2][l])||(tmp>a[3][l])){flg=0;break;}
				}
				if(flg)mp[id(i,o)][id(j,p)]=dis(x[i],a[o][i],x[j],a[p][j]),mp[id(j,p)][id(i,o)]=dis(x[i],a[o][i],x[j],a[p][j]);
				// cerr<<id(j,p)<<' '<<id(i,o)<<' '<<dis(x[i],a[o][i],x[j],a[p][j])<<'\n';
			}
		}
	}
	bool fyyyyds=1;
	rep(i,1,n)
		if(5<a[0][i]||(a[1][i]<5&&5<a[2][i])||5>a[3][i]){fyyyyds=0;break;}
	if(fyyyyds)return puts("10.00"),void();
	rep(i,1,n){
		rep(o,0,3){
			db k=(a[o][i]-5)/(x[i]-0),b=a[o][i]-k*x[i];bool flg=1;
			rep(l,1,i-1){
				db tmp=k*x[l]+b;
				if(tmp<a[0][l]||(a[1][l]<tmp&&tmp<a[2][l])||(tmp>a[3][l])){flg=0;break;}
			}
			if(flg)mp[0][id(i,o)]=dis(0,5,x[i],a[o][i]),mp[id(i,o)][0]=dis(x[i],a[o][i],0,5);
			// cerr<<0<<' '<<id(i,o)<<' '<<dis(x[i],a[o][i],0,5)<<'\n';
		}
	}
	rep(i,1,n){
		rep(o,0,3){
			db k=(a[o][i]-5)/(x[i]-10),b=a[o][i]-k*x[i];bool flg=1;
			rep(l,i+1,n){
				db tmp=k*x[l]+b;
				if(tmp<a[0][l]||(a[1][l]<tmp&&tmp<a[2][l])||(tmp>a[3][l])){flg=0;break;}
			}
			if(flg)mp[n*4+1][id(i,o)]=dis(10,5,x[i],a[o][i]),mp[id(i,o)][n*4+1]=dis(x[i],a[o][i],10,5);
			// cerr<<n*4+1<<' '<<id(i,o)<<' '<<dis(x[i],a[o][i],10,5)<<'\n';
		}
	}
	rep(k,0,4*n+1)rep(i,0,4*n+1)rep(j,0,4*n+1)ckmin(mp[i][j],mp[i][k]+mp[k][j]);
	printf("%.2lf\n",mp[0][4*n+1]);
}
signed main(){
	while("fyy AK IOI")Main();
}