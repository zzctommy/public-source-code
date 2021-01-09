//调用手写随机数

struct Hash{

static const int O=1001000;
int mod,hed[O],tot,to[O],cnt[O],nxt[O],tag[O],id;
Hash(){
	static const int Mod[8]={1000003,1000033,1000037,1000039,1000081,1000099,1000117,1000121};
	static Rand maker;
	mod=Mod[maker.rand()&7];
	tot=0,id=1;
	memset(hed,0,sizeof(hed));
	memset(tag,0,sizeof(tag));
}
void clear(){++id,tot=0;}
void insert(int t,int val=1){
	int x=t%mod;
	if(tag[x]!=id){
		tag[x]=id,to[++tot]=t,nxt[tot]=0,hed[x]=tot,cnt[tot]=val;
		return;
	}
	for(int i=hed[x];i;i=nxt[i])
		if(to[i]==t){cnt[i]+=val;return;}
	to[++tot]=t,nxt[tot]=hed[x],hed[x]=tot,cnt[tot]=val;
}
int query(int t){
	int x=t%mod;
	if(tag[x]!=id)return 0;
	for(int i=hed[x];i;i=nxt[i])
		if(to[i]==t)return cnt[i];
	return 0;
}

};