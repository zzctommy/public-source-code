const int N=1100005;
int n,m,rt,tot,ans;
int siz[N],ch[N][2],val[N],rnd[N];
inline void pushup(int u) {
	siz[u]=siz[ch[u][0]]+siz[ch[u][1]]+1;
}
inline int newnode(int x) {
	++tot,rnd[tot]=rand(),val[tot]=x,siz[tot]=1;
	return tot;
}
int merge(int x,int y) {
	if(!x||!y)return x|y;
	if(rnd[x]<rnd[y]){
		ch[x][1]=merge(ch[x][1],y);
		return pushup(x),x;
	}else{
		ch[y][0]=merge(x,ch[y][0]);
		return pushup(y),y;
	}
}
void split(int u,int k,int &x,int &y) {
	if(!u)return x=y=0,void();
	if(val[u]<=k)x=u,split(ch[u][1],k,ch[u][1],y);
	else y=u,split(ch[u][0],k,x,ch[u][0]);
	pushup(u);
}
inline void insert(int x) {
	int a,b;
	split(rt,x,a,b);
	rt=merge(merge(a,newnode(x)),b);
}
inline void del(int x) {
	int a,b,c;
	split(rt,x,a,b);
	split(a,x-1,a,c);
	c=merge(ch[c][0],ch[c][1]);
	rt=merge(merge(a,c),b);
}
inline int rk(int x) {
	int a,b;
	split(rt,x-1,a,b);
	int res=siz[a]+1;
	rt=merge(a,b);
	return res;
}
inline int kth(int u,int k) {
	while(true) {
		if(k<=siz[ch[u][0]])u=ch[u][0];
		else if(k==siz[ch[u][0]]+1)return val[u];
		else k-=siz[ch[u][0]]+1,u=ch[u][1];
	}
}
inline int lowerbound(int x) {
	int a,b;
	split(rt,x-1,a,b);
	int res=kth(a,siz[a]);
	rt=merge(a,b);
	return res;
}
inline int upperbound(int x) {
	int a,b;
	split(rt,x,a,b);
	int res=kth(b,1);
	rt=merge(a,b);
	return res;
}