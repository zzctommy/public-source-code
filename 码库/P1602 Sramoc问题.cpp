#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = 0; c = getchar();}
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return f ? x : -x;
}
#define N 1000005
#define M 5000005
#define mkp(x,y) make_pair(x,y)
#define fi first
#define se second
bool vis[N];
int k,m;
int trie[M][10],fa[M],tot;
void print(int u){
    static int d[M];
    d[0]=0;
    while(u){
        for(int i=0;i<k;++i)if(trie[fa[u]][i]==u){d[++d[0]]=i;break;}
        u=fa[u];
    }
    for(int i=d[0];i>=1;--i)printf("%d",d[i]);
    puts("");
}
void bfs(){
    queue<pair<int,int> >q;
    for(int i=1;i<k;++i){
        int c=i%m;
        if(vis[c])continue;
        vis[c]=1,trie[0][i]=++tot,fa[tot]=0;
        if(!c)return print(tot),void();
        q.push(mkp(c,tot));
    }
    while(!q.empty()){
        pair<int,int>u=q.front();q.pop();
        for(int i=0;i<k;++i){
            int c=(u.fi*10+i)%m;
            if(vis[c])continue;
            vis[c]=1,trie[u.se][i]=++tot,fa[tot]=u.se;
            if(!c)return print(tot),void();
            q.push(mkp(c,tot));
        }
    }
}
signed main(){
    scanf("%d%d",&k,&m);
    bfs();
}