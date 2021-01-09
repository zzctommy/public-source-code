#define int long long
const int N=5e5+10;
const int inf=1e18;
int n,ans;
int cv[N],top;
struct point {
	int x,y;
	point(){x=y=0;}
	point(int x_,int y_){x=x_,y=y_;}
}p[N];
int crs(const point &a,const point &b,const point &c,const point &d) {
	point x=point(b.x-a.x,b.y-a.y),y=point(d.x-c.x,d.y-c.y);
	return x.x*y.y-x.y*y.x;
}
int crs(const point &a,const point &b,const point &c) {
	return crs(a,b,a,c);
}
int dis(const point &a,const point &b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool cmp(const point &a,const point &b) {
	double k=crs(p[1],a,b);
	if(k>0)return 1;
	if(k==0&&dis(p[1],a)<dis(p[1],b))return 1;
	return 0;
}
void convex() {
	int k=1;
	for(rint i=2;i<=n;++i)
		if(p[i].x<p[k].x||(p[i].x==p[k].x&&p[i].y<p[k].y))k=i;
	swap(p[1],p[k]),sort(p+2,p+n+1,cmp),cv[++top]=1;
	for(rint i=1;i<=n;++i) {
		while(top>1&&crs(p[cv[top-1]],p[cv[top]],p[i])<=0)--top;
		cv[++top]=i;
	}
}
void rotating() {
	ans=0;
	if(top==2){ans=dis(p[cv[1]],p[cv[2]]);return;}
	cv[top+1]=1;
	for(rint i=1,j=2;i<=top;++i) {
		while(crs(p[cv[i]],p[cv[i+1]],p[cv[j]])<crs(p[cv[i]],p[cv[i+1]],p[cv[j+1]]))j=(j+1>=top?1:j+1);
		ans=max(ans,max(dis(p[cv[i]],p[cv[j]]),dis(p[cv[i+1]],p[cv[j]])));
	}
}