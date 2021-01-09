const int M=2000005;
int fail[M],dp[M];
int n,tot,ch[M][26],ed[M];
void ins(char*s,int id) {
	int u=0,len=strlen(s);
	for(int i=0;i<len;++i) {
		int c=s[i]-'a';
		if(!ch[u][c])ch[u][c]=++tot;
		u=ch[u][c];
	}
	ed[id]=u;
}
void make_fail() {
	queue<int>q;
	for(int i=0;i<26;++i)if(ch[0][i])q.push(ch[0][i]),fail[ch[0][i]]=0;
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<26;++i)
			if(ch[u][i])q.push(ch[u][i]),fail[ch[u][i]]=ch[fail[u]][i];
			else ch[u][i]=ch[fail[u]][i];
	}
}