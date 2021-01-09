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