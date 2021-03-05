#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
#define sz(v) (int)(v).size()
typedef long long LL;
typedef double db;
template<class T>bool ckmax(T&x,T y){return x<y?x=y,1:0;}
template<class T>bool ckmin(T&x,T y){return x>y?x=y,1:0;}
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define per(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}
int win[1<<16],mp[4][4];
int rds(){
	const static int 
		d[16]={0,4,1,8,5,2,12,9,6,3,13,10,7,14,11,15};
	int res=0,cnt=0;
	char ch=getchar();
	while(cnt<16){
		while(ch!='*'&&ch!='.')ch=getchar();
		if(ch=='*')res|=1<<d[cnt];
		++cnt,ch=getchar();
	}
	return res;
}
void print(int msk){
	for(int i=0;i<4;++i){
		for(int j=0;j<4;++j)
			cout<<((msk>>(4*i+j))&1)<<' ';
		cout<<endl;
	}
	cout<<"-----------\n";
}
int hsh(){
	int res=0;
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			if(mp[i][j])res|=1<<(4*i+j);
//	print(res);
	return res;
}
int kz(int msk){
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j)
			mp[i][j]=(msk>>(4*i+j))&1;
	for(int i=0;i<4;++i){
		for(int j=0;j<4;++j){
			if(!mp[i][j]){
				mp[i][j]=1;
				if(!win[hsh()])return 1;
				if(j+1<4&&!mp[i][j+1]){
					mp[i][j+1]=1;
					if(!win[hsh()])return 1;
					if(j+2<4&&!mp[i][j+2]){
						mp[i][j+2]=1;
						if(!win[hsh()])return 1;
						mp[i][j+2]=0;
					}
					mp[i][j+1]=0;
				}
				if(i+1<4&&!mp[i+1][j]){
					mp[i+1][j]=1;
					if(!win[hsh()])return 1;
					if(i+2<4&&!mp[i+2][j]){
						mp[i+2][j]=1;
						if(!win[hsh()])return 1;
						mp[i+2][j]=0;
					}
					mp[i+1][j]=0;
				}
				if(i+1<4&&j+1<4&&!mp[i+1][j+1]){
					mp[i+1][j+1]=1;
					if(!win[hsh()])return 1;
					if(i+2<4&&j+2<4&&!mp[i+2][j+2]){
						mp[i+2][j+2]=1;
						if(!win[hsh()])return 1;
						mp[i+2][j+2]=0;
					}
					mp[i+1][j+1]=0;
				}
				if(j+1<4&&i>=1&&!mp[i-1][j+1]){
					mp[i-1][j+1]=1;
					if(!win[hsh()])return 1;
					if(j+2<4&&i>=2&&!mp[i-2][j+2]){
						mp[i-2][j+2]=1;
						if(!win[hsh()])return 1;
						mp[i-2][j+2]=0;
					}
					mp[i-1][j+1]=0;
				}
				mp[i][j]=0;
			}
		}
	}
	return 0;
}
void init(){
	win[(1<<16)-1]=0;
	for(int i=(1<<16)-2;i>=0;--i)win[i]=kz(i);
}
signed main(){
	init();
	for(int T=read();T;--T)
		puts(win[rds()]?"Possible.":"Impossible.");
}