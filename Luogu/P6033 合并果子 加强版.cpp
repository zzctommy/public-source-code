#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb(x) push_back(x)
#define mkp(x,y) make_pair(x,y)
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const LL inf=1e15; 
int n,bin[100005];
LL ans;
struct QUEUE{
	queue<LL>q[2];
	void push(LL x,int o){q[o].push(x);}
	LL front(){
		assert(!q[0].empty()||!q[1].empty());
		LL res=inf;
		if(!q[0].empty())res=min(res,q[0].front());
		if(!q[1].empty())res=min(res,q[1].front());
		return res;
	}
	void pop(){
		assert(!q[0].empty()||!q[1].empty());
		if(q[0].empty())q[1].pop();
		else if(q[1].empty())q[0].pop();
		else if(q[0].front()<q[1].front())q[0].pop();
		else q[1].pop();
	}
	int size(){return q[0].size()+q[1].size();}
}q;
signed main(){
	n=read();
	for(int i=1;i<=n;++i)++bin[read()];
	for(int i=1;i<=100000;++i)for(int j=1;j<=bin[i];++j)q.push(i,0);
	while(q.size()>1){
		LL x=q.front();q.pop();
		LL y=q.front();q.pop();
		q.push(x+y,1),ans+=x+y;
	}
	printf("%lld\n",ans);
	return 0;
}