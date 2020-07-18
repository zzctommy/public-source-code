#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned int uint;
#define rint register int
#define pb push_back
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2) EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int rd() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
int T,bin[100],fz,fm;
map<char,int>level;
struct card {
	int suit,hand;
	card(){suit=hand=0;}
	card(int a,int b) {suit=a,hand=b;}
	void read() {
		char s[4];
		scanf("%s",s);
		suit=level[s[0]];
		hand=level[s[1]];
	}
}a[5],b[5],c[5],rep[100];
#define S(x) v[x].suit
#define H(x) v[x].hand
#define F(x) (H(x)==1?14:H(x))
int operator < (const card &a,const card &b) {
	return a.hand<b.hand;
}
int operator !=(const card &a,const card &b) {
	return a.hand!=b.hand;
}
int sasitu(card*v,int a,int b,int c,int d,int e) {
	return H(0)==a&&H(1)==b&&H(2)==c&&H(3)==d&&H(4)==e;
}
int sasuit(card*v) {
	return S(0)==S(1)&&S(0)==S(2)&&S(0)==S(3)&&S(0)==S(4);
}
int sahand(card*v,int l,int r) {
	for(rint i=l;i<r;++i)if(H(r)!=H(i))return 0;
	return 1;
}
int cmp(int a,int b) {return a>b;}
int any_two_same(card*v,int *w) {
	for(rint i=0;i<5;++i)
		for(rint j=i+1;j<5;++j)
			if(H(i)==H(j)) {
				w[0]=F(i);
				for(rint k=0,l=0;k<5;++k)
					if(k!=i&&k!=j)w[++l]=F(k);
				sort(w+1,w+5,cmp);
				return 1;
			}
	return 0;
}
struct node {
	card v[6];int type;
	int w[6];
	node(){memset(w,0,sizeof(w));type=11;}
	node(card a,card b,card c,card d,card e) {
		memset(w,0,sizeof(w));
		v[0]=a,v[1]=b,v[2]=c,v[3]=d,v[4]=e;sort(v,v+5);
		if(sasuit(v)&&sasitu(v,1,10,11,12,13))type=1,w[0]=14;
		else if(sasuit(v)&&sasitu(v,H(0),H(0)+1,H(0)+2,H(0)+3,H(0)+4))type=2,w[0]=F(4);
		else if(sahand(v,0,3))type=3,w[0]=F(0),w[1]=F(4);
		else if(sahand(v,1,4))type=3,w[0]=F(1),w[1]=F(0);
		else if(sahand(v,0,2)&&sahand(v,3,4))type=4,w[0]=F(0),w[1]=F(3);
		else if(sahand(v,0,1)&&sahand(v,2,4))type=4,w[0]=F(2),w[1]=F(0);
		else if(sasuit(v))type=5,w[0]=F(4),w[1]=F(3),w[2]=F(2),w[3]=F(1),w[4]=F(0),sort(w,w+5,cmp);
		else if(sasitu(v,1,10,11,12,13))type=6,w[0]=14;
		else if(sasitu(v,H(0),H(0)+1,H(0)+2,H(0)+3,H(0)+4))type=6,w[0]=F(4);
		else if(sahand(v,0,2))type=7,w[0]=F(0),w[1]=F(4),w[2]=F(3),sort(w+1,w+3,cmp);
		else if(sahand(v,1,3))type=7,w[0]=F(1),w[1]=F(4),w[2]=F(0),sort(w+1,w+3,cmp);
		else if(sahand(v,2,4))type=7,w[0]=F(2),w[1]=F(1),w[2]=F(0),sort(w+1,w+3,cmp);
		else if(sasitu(v,H(0),H(1),H(1),H(3),H(3)))type=8,w[0]=F(3),w[1]=F(1),w[2]=F(0),sort(w,w+2,cmp);
		else if(sasitu(v,H(0),H(0),H(2),H(3),H(3)))type=8,w[0]=F(3),w[1]=F(0),w[2]=F(2),sort(w,w+2,cmp);
		else if(sasitu(v,H(0),H(0),H(2),H(2),H(4)))type=8,w[0]=F(2),w[1]=F(0),w[2]=F(4),sort(w,w+2,cmp);
		else if(any_two_same(v,w))type=9;
		else type=10,w[0]=F(4),w[1]=F(3),w[2]=F(2),w[3]=F(1),w[4]=F(0),sort(w,w+5,cmp);
	}
};
int operator < (node a,node b) {
	if(a.type!=b.type)return a.type>b.type;
	for(rint i=0;i<5;++i)if(a.w[i]!=b.w[i])return a.w[i]<b.w[i];
	return 0;
}
node maxsitu(card a,card b,card c,card d,card e,card f,card g) {
	card v[10];node res;
	int mrk[10];memset(mrk,0,sizeof(mrk));
	v[0]=a,v[1]=b,v[2]=c,v[3]=d,v[4]=e,v[5]=f,v[6]=g;
	vector<card>t;
	for(rint i=0;i<7;++i) {
		mrk[i]=1;
		for(rint j=i+1;j<7;++j) {
			mrk[j]=1;t.clear();
			for(rint k=0;k<7;++k)
				if(!mrk[k])t.pb(v[k]);
			node tmp=node(t[0],t[1],t[2],t[3],t[4]);
			if(res<tmp)res=tmp;
			mrk[j]=0;
		}
		mrk[i]=0;
	}
	return res;
}
void init() {
	level['2']=2,level['3']=3,level['4']=4,level['5']=5,level['6']=6,level['7']=7,level['8']=8,level['9']=9,level['T']=10;
	level['J']=11,level['Q']=12,level['K']=13,level['A']=1;
	level['D']=20,level['C']=21,level['H']=22,level['S']=23;
	for(rint i=20;i<24;++i)
		for(rint j=1;j<=13;++j)
			rep[(i-20)*13+j]=card(i,j);
}
int val(card x) {return (x.suit-20)*13+x.hand;}
void clear(){
	memset(bin,0,sizeof(bin));
	fz=fm=0;
}
int GCD(int x,int y) {return !y?x:GCD(y,x%y);}
signed main() {
	init();
	T=rd();
	while(T--) {
		clear();
		a[0].read(),a[1].read(),bin[val(a[0])]=bin[val(a[1])]=1;
		b[0].read(),b[1].read(),bin[val(b[0])]=bin[val(b[1])]=1;
		c[0].read(),c[1].read(),c[2].read(),bin[val(c[0])]=bin[val(c[1])]=bin[val(c[2])]=1;
		for(rint i=1;i<=52;++i) {
			if(bin[i])continue;
			for(rint j=i+1;j<=52;++j) {
				if(bin[j])continue;++fm;
				if(maxsitu(b[0],b[1],c[0],c[1],c[2],rep[i],rep[j])<maxsitu(a[0],a[1],c[0],c[1],c[2],rep[i],rep[j]))++fz;
			}
		}
		int gcd=GCD(fz,fm);
		fz/=gcd,fm/=gcd;
		printf("%d/%d\n",fz,fm);
	}
	return 0;
}
