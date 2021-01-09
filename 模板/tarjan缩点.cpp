int low[N],dfn[N],tmr,stk[N],top;
void tarjan(int u) {
	low[u]=dfn[u]=++tmr,stk[++top]=u;
	for(int i=hed[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		scc[u]=++C;
		while(stk[top]!=u)scc[stk[top--]]=C;
		--top;
	}
}