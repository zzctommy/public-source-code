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

#define N 1000005

int n,q,ma[N<<1];
char str[N];

struct Merge_Segment_Tree{

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

#define S (N<<1)

int trans[S][26],tot,mxlen[S],link[S],mr[S];
int q[S],t[S],rt[S],to[S];

int New(){++tot;memset(trans[tot],0,sizeof(trans[tot]));mxlen[tot]=link[tot]=0;return tot;}

Suffix_Automation(){tot=0,New();}
void clear(){tot=0;New();}

int extend(int c,int lst,int id=0){
	int p=lst,np=New();mxlen[np]=mxlen[p]+1,mr[np]=mxlen[np];
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1,mr[nq]=mr[q];
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	if(id)seg.update(rt[np],id,1);
	return np;
}
void insert(char*str,int op=0){
	int len=strlen(str);
	for(int i=0,lst=1;i<len;++i)lst=extend(str[i]-'a',lst,op?i+1:0);
}
void rsort(){
	for(int i=1;i<=tot;++i)t[i]=0;
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
#undef S

}sam;

bool ckmax(int&x,int y){return x<y?x=y,1:0;}
bool ckmin(int&x,int y){return x>y?x=y,1:0;}

signed main(){
	scanf("%s",str),n=strlen(str),sam.insert(str,1),sam.merge_endpos();
	q=read();
	for(int t=1;t<=q;++t){
		static char S[N];
		static int l,r,m,p,now;
		static LL res;
		static Suffix_Automation SAM;
		scanf("%s%d%d",S+1,&l,&r),m=strlen(S+1),p=1,now=0,res=0;
		SAM.clear(),SAM.insert(S+1);
		for(int i=1;i<=m;++i){
			int c=S[i]-'a';
			while("fyytxdy"){
				if(sam.trans[p][c]&&seg.query(sam.rt[sam.trans[p][c]],l+now,r)){++now,p=sam.trans[p][c];break;}
				if(!now)break;
				if(--now==sam.mxlen[sam.link[p]])p=sam.link[p];
			}
			ma[i]=now;
		}
		for(int i=1;i<=SAM.tot;++i)res+=max(0,SAM.mxlen[i]-max(SAM.mxlen[SAM.link[i]],ma[SAM.mr[i]]));
		printf("%lld\n",res);
	}
	return 0;
}
/*
scbamgepe
3
smape 2 7
sbape 3 8
sgepe 1 9

                       
P4770_2.in
*/