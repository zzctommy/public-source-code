#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return x*f;
}
const int N=2010;
const double eps=1e-9;
double randeps() {return (rand()/(double)RAND_MAX-0.5)*eps;}
struct vec {
	double x,y,z;
	vec(){x=y=z=0;}
	vec(double x_,double y_,double z_){x=x_,y=y_,z=z_;}
	void shake() {x+=randeps(),y+=randeps(),z+=randeps();}
	double len() {return sqrt(x*x+y*y+z*z);}
	vec operator + (const vec &t) {return vec(x+t.x,y+t.y,z+t.z);}
	vec operator - (const vec &t) {return vec(x-t.x,y-t.y,z-t.z);}
}p[N];
double dot(const vec &a,const vec &b) {return a.x*b.x+a.y*b.y+a.z*b.z;}
vec crs(const vec &a,const vec &b) {return vec(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
struct face {
	int v[3];
	face(){v[0]=v[1]=v[2]=0;}
	face(int a,int b,int c) {v[0]=a,v[1]=b,v[2]=c;}
	vec normal() {return crs(p[v[1]]-p[v[0]],p[v[2]]-p[v[0]]);}
	double area() {return normal().len()/2.0;}
}cv[N],h[N];
int cansee(face A,vec b) {return dot(b-p[A.v[0]],A.normal())>0;}
int n,th,cnt,vis[N][N];
double ans;
void convex() {
	cnt=th=0;
	cv[++cnt]=face(1,2,3);
	cv[++cnt]=face(3,2,1);
	for(rint i=4;i<=n;++i) {
		for(rint j=1,v;j<=cnt;++j) {
			if(!(v=cansee(cv[j],p[i])))h[++th]=cv[j];
			for(rint k=0;k<3;++k) 
				vis[cv[j].v[k]][cv[j].v[k>1?0:k+1]]=v;
		}
		for(rint j=1;j<=cnt;++j)
			for(rint k=0;k<3;++k) {
				int x=cv[j].v[k],y=cv[j].v[k>1?0:k+1];
				if(vis[x][y]&&!vis[y][x])h[++th]=face(x,y,i);
			}
		for(rint j=1;j<=th;++j)cv[j]=h[j];
		cnt=th,th=0;
	}
}
void calc() {for(rint i=1;i<=cnt;++i)ans+=cv[i].area();}
signed main() {
	srand(time(0));
	n=rd();
	for(rint i=1;i<=n;++i)
		scanf("%lf%lf%lf",&p[i].x,&p[i].y,&p[i].z),p[i].shake();
	convex();calc();
	printf("%.3lf\n",ans);
	return 0;
}
