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
const int N=1e5+10;
struct vec {
	double x,y;
	vec(){x=y=0;}
	vec(double _x,double _y){x=_x,y=_y;}
	vec operator + (const vec &t)const{return vec(x+t.x,y+t.y);}
	vec operator - (const vec &t)const{return vec(x-t.x,y-t.y);}
	vec operator * (const double &t)const{return vec(x*t,y*t);}
	vec operator / (const double &t)const{return vec(x/t,y/t);}
	vec rot_90() {return vec(y,-x);}
	double len2() {return x*x+y*y;}
}p[N],O;
int n;
double R;
double cross(const vec &x,const vec &y) {return x.x*y.y-x.y*y.x;}
vec intersection(const vec &a1,const vec &a2,const vec &b1,const vec &b2) {
	double t=cross(b1-a1,b2)/cross(a2,b2);
	return a1+a2*t;
}
vec circle(const vec &a,const vec &b,const vec &c) {
	return intersection((a+b)/2,(b-a).rot_90(),(b+c)/2,(c-b).rot_90());
}
void min_circle() {
	random_shuffle(p+1,p+n+1);
	R=0;
	for(rint i=1;i<=n;++i) {
		if((p[i]-O).len2()>R) {
			O=p[i],R=0;
			for(rint j=1;j<i;++j) {
				if((p[j]-O).len2()>R) {
					O=(p[i]+p[j])/2,R=(p[j]-O).len2();
					for(rint k=1;k<j;++k) {
						if((p[k]-O).len2()>R) {
							O=circle(p[i],p[j],p[k]),R=(p[k]-O).len2();
						}
					}
				}
			}
		}
	}
}
signed main() {
	srand('f'*'f'*'y'*' '*'A'*'K'*' '*'I'*'O'*'I');n=rd();
	for(rint i=1;i<=n;++i)scanf("%lf%lf",&p[i].x,&p[i].y);
	min_circle();
	printf("%.10lf\n%.10lf %.10lf",sqrt(R),O.x,O.y);
	return 0;
} 
