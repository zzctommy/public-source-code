#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
typedef long long LL;
typedef double db;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=0;ch=getchar();}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return f?x:-x;
}

#define N 200005

int n,ans,dp[N<<1],tp[N<<1];
char str[N];

struct Merge_Segment_Tree{

/*
Hint 

can use with Suffix Automation to calculate the endpos set,the name of it should be "seg"

you should let the length of array n is positive and less than N which is the length of array

if N > 1000000 then you have to change "20" to log(n). At most time 20 is enough.

update(p,pos,k) : add k to the pos_th element of root p

merge(x,y) : merge root x and root y

query(p,ql,qr) : return the sum of [ql,qr] of root p

*/

#define T ((N<<1)*20)

int ls[T],rs[T],val[T],tot;

Merge_Segment_Tree(){tot=0;}

void update(int&p,int pos,int k,int l=1,int r=n){
	if(!p)p=++tot;
	val[p]+=k;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],pos,k,l,mid);
	else update(rs[p],pos,k,mid+1,r);
}
int merge(int x,int y,int l=1,int r=n){
	if(!x||!y)return x|y;
	if(l==r)return val[x]+=val[y],x;
	int p=++tot,mid=(l+r)>>1;
	ls[p]=merge(ls[x],ls[y],l,mid);
	rs[p]=merge(rs[x],rs[y],mid+1,r);
	return val[p]=val[ls[p]]+val[rs[p]],p;
}
int query(int p,int ql,int qr,int l=1,int r=n){
	if(!p)return 0;
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ls[p],ql,qr,l,mid);
	if(mid<qr)res+=query(rs[p],ql,qr,mid+1,r);
	return res;
}

#undef T

}seg;

struct Suffix_Automation{

/*
Hint

This is Generalized Suffix Automation!!!

N is the sumlength of strings

extend(c,lst,id) : if you need Segment Tree to find endpos, you must give the id which is the position of c in string,
                   this function will add a new char

insert(str,op) : insert a string into the Suffix Automation. if op = 1 then will update the Segment Tree.

rsort : find the topo rank of every node

merge endpos : get the endpos of every node. you should define a Merge_Segment_Tree called seg.

diffrent_substring : return the sum of different substrings of all the strings(you can inserted more than one)
                     instered into the Suffix Automation.


*/

#define S (N<<1)

int trans[S][26],tot,mxlen[S],link[S],rev[S];
int q[S],t[S],rt[S];

int New(){++tot;memset(trans[tot],0,sizeof(trans[tot]));mxlen[tot]=link[tot]=0;return tot;}

Suffix_Automation(){tot=0,New();}
void clear(){tot=0;New();}

int extend(int c,int lst,int id=0){
	int p=lst,np=New();mxlen[np]=mxlen[p]+1,rev[np]=id;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1,rev[nq]=rev[q];
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	if(id)seg.update(rt[np],id,1);
	return np;
}
void insert(char*str,int op=0){
	int n=strlen(str);
	for(int i=0,lst=1;i<n;++i)lst=extend(str[i]-'a',lst,op?i+1:0);
}
void rsort(){
	for(int i=1;i<=tot;++i)++t[mxlen[i]];
	for(int i=1;i<=tot;++i)t[i]+=t[i-1];
	for(int i=1;i<=tot;++i)q[t[mxlen[i]]--]=i;
}
void merge_endpos(){
	rsort();
	for(int i=tot;i>=2;--i)rt[link[q[i]]]=seg.merge(rt[link[q[i]]],rt[q[i]]);
}
LL diffrent_substring(){
	LL res=0;
	for(int i=1;i<=tot;++i)res+=mxlen[i]-mxlen[link[i]];
	return res;
}

}sam;

signed main(){
	scanf("%d%s",&n,str),sam.insert(str,1),sam.merge_endpos();
	for(int i=2;i<=sam.tot;++i){
		int u=sam.q[i],f=sam.link[u];
		if(f==1)dp[u]=1,tp[u]=u;
		else if(seg.query(sam.rt[tp[f]],sam.rev[u]-sam.mxlen[u]+sam.mxlen[tp[f]],sam.rev[u]-1))dp[u]=dp[f]+1,tp[u]=u;
		else dp[u]=dp[f],tp[u]=tp[f];
		ans=max(ans,dp[u]);
	}
	printf("%d\n",ans);
}
/*
21
abcaaaaabbcbacbabcbcb

10
aaabaabaab

*/