template<int L>
struct Suffix_Automation{

#define N (L+5)

struct Merge_Segment_Tree{

static const int T=N*(log(N)+1);

int ls[T],rs[T],val[T],tot;

Merge_Segment_Tree(){tot=0;}

void update(int&p,int pos,int k,int l=1,int r=L){
	if(!p)p=++tot;
	val[p]+=k;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls[p],pos,k,l,mid);
	else update(rs[p],pos,k,mid+1,r);
}
int merge(int x,int y,int l=1,int r=L){
	if(!x||!y)return x|y;
	if(l==r)return val[x]+=val[y],x;
	int p=++tot,mid=(l+r)>>1;
	ls[p]=merge(ls[x],ls[y],l,mid);
	rs[p]=merge(rs[x],rs[y],mid+1,r);
	return val[p]=val[ls[p]]+val[rs[p]],p;
}
int query(int p,int ql,int qr,int l=1,int r=L){
	if(!p)return 0;
	if(ql<=l&&r<=qr)return val[p];
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(ls[p],ql,qr,l,mid);
	if(mid<qr)res+=query(rs[p],ql,qr,mid+1,r);
	return res;
}


}seg;

#define S (N<<1)

int trans[S][26],tot,mxlen[S],link[S];
int q[S],t[S],rt[S];

int New(){++tot;memset(trans[tot],0,sizeof(trans[tot]));mxlen[tot]=link[tot]=0;return tot;}

Suffix_Automation(){tot=0,New();}
void clear(){tot=0;New();}

int extend(int c,int lst,int id,int op=0){
	if(trans[lst][c]){
		int p=lst,q=trans[p][c];
		if(mxlen[p]+1==mxlen[q]){if(op)seg.update(rt[q],id,1);return q;}
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
			if(op)seg.update(rt[nq],id,1);
			return nq;
		}
	}
	int p=lst,np=New();mxlen[np]=mxlen[p]+1;
	for(;p&&!trans[p][c];p=link[p])trans[p][c]=np;
	if(!p)link[np]=1;
	else{
		int q=trans[p][c];
		if(mxlen[p]+1==mxlen[q])link[np]=q;
		else{
			int nq=New();mxlen[nq]=mxlen[p]+1;
			for(int i=0;i<26;++i)trans[nq][i]=trans[q][i];
			link[nq]=link[q],link[q]=link[np]=nq;
			for(;p&&trans[p][c]==q;p=link[p])trans[p][c]=nq;
		}
	}
	if(op)seg.update(rt[np],id,1);
	return np;
}
void insert(char*str,int op=0){
	int n=strlen(str);
	for(int i=0,lst=1;i<n;++i)lst=extend(str[i]-'a',lst,i+1);
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
LL distinct_substring(){
	LL res=0;
	for(int i=1;i<=tot;++i)res+=mxlen[i]-mxlen[link[i]];
	return res;
}
#undef S
#undef N

};