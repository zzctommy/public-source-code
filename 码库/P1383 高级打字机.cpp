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
char rdc() {
	char ch=getchar();
	while(!isalpha(ch))ch=getchar();
	return ch;
} 
const int N=100010;
const int M=22*N; 
int n,cnt,tot;
int root[N],len[N];
char val[M];
int ls[M],rs[M];
void update(int pre,int &now,int l,int r,int pos) {
	now=++tot;
	rs[now]=rs[pre],ls[now]=ls[pre];
	if(l==r){val[now]=rdc();return;}
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[pre],ls[now],l,mid,pos);
	else update(rs[pre],rs[now],mid+1,r,pos);
}
char query(int now,int l,int r,int k) {
	if(l==r)return val[now];
	int mid=(l+r)>>1;
	if(k<=mid)return query(ls[now],l,mid,k);
	else return query(rs[now],mid+1,r,k);
}
signed main() {
	n=rd();
	for(rint T=1;T<=n;++T){
		char ch=rdc();int x;
		if(ch=='T') {
			++cnt,len[cnt]=len[cnt-1]+1;
			update(root[cnt-1],root[cnt],1,n,len[cnt]);
		} else if(ch=='U') {
			++cnt,x=rd(),root[cnt]=root[cnt-x-1],len[cnt]=len[cnt-x-1];
		} else printf("%c\n",query(root[cnt],1,n,rd()));
	}
	return 0;
}
