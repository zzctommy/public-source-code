#include<bits/stdc++.h>
using namespace std;
const int M=100005;
const int N=20005;
int n,m,num_edge,head[N],ans,l,r;
struct edge {
    int to,nxt,val;
} e[M<<1];
void add(int from,int to,int val) {
    ++num_edge;
    e[num_edge].val=val;
    e[num_edge].to=to;
    e[num_edge].nxt=head[from];
    head[from]=num_edge;
}
bool pd(int mid) {
    queue<int>q;
    int col[N];
    memset(col,0,sizeof(col));
    for(int i=1; i<=n; ++i) {
        if(col[i])continue;
        col[i]=1;
        q.push(i);
        while(!q.empty()) {
            int u=q.front();
            q.pop();
            for(int i=head[u]; i; i=e[i].nxt) {
                int v=e[i].to,w=e[i].val;
                if(w>mid) {
                    if(!col[v]) {
                        col[v]=col[u]^3;
                        q.push(v);
                    } else if(col[v]==col[u])return false;
                }
            }
        }
    }
    return true;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,a,b,c; i<=m; ++i) {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);add(b,a,c);r=max(r,c);
    }
    while(l<=r) {
        int mid=(l+r)>>1;
        if(pd(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
