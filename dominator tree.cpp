#include <bits/stdc++.h>
#define MAXN    300003
using namespace std;

int m,n;
vector<int> G[MAXN],rG[MAXN],sT[MAXN];//Graph, reversed Graph, semi-dominator tree

int dfn[MAXN],fa[MAXN],id[MAXN],_cnt=0;
void dfs(int u){
    dfn[u]=++_cnt;
    id[_cnt]=u;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(dfn[v]) continue;
        fa[v]=u;
        dfs(v);
    }
}
#define min_dfn(x,y) (dfn[x]<dfn[y]?x:y)

int f[MAXN],sdom[MAXN],idom[MAXN],mn[MAXN];

void dsu_init(){
    for(int i=1;i<=n;i++){
        f[i]=i;
    }
}

int dsu_find(int x){
    if(f[x]==x) return x;
    int tmp=f[x];
    f[x]=dsu_find(f[x]);
    if(dfn[sdom[mn[x]]]>dfn[sdom[mn[tmp]]]){
        mn[x]=mn[tmp];
    }
    return f[x];
}

void dsu_merge(int x,int y){
    x=dsu_find(x);y=dsu_find(y);
    f[y]=x;
}

void LT(){
    dfs(1);
    dfn[0]=n+1;
    dsu_init();

    for(int i=n;i>=1;i--){
        int x=id[i],y;
        for(int j=0;j<rG[x].size();j++){
            y=rG[x][j];
            if(dfn[y]<dfn[x]){
                sdom[x]=min_dfn(sdom[x],y);
            }else{
                dsu_find(y);
                sdom[x]=min_dfn(sdom[x],sdom[mn[y]]);
            }
        }
        for(int j=0;j<sT[x].size();j++){
            y=sT[x][j];
            dsu_find(y);
            int z=mn[y];
            if(dfn[sdom[z]]==dfn[x]){
                idom[y]=x;
            }else{
                idom[y]=z;
            }
        }
        mn[x]=x;
        dsu_merge(fa[x],x);
        sT[sdom[x]].push_back(x);
    }

    int u;
    for(int i=2;i<=n;i++){
        u=id[i];
        if(idom[u]!=sdom[u]) idom[u]=idom[idom[u]];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    int xx,yy;
    for(int i=0;i<m;i++){
        cin>>xx>>yy;
        G[xx].push_back(yy);
        rG[yy].push_back(xx);
    }
    
    LT();

    for(int i=1;i<=n;i++){
        printf("node: %d father:%d\n",i,idom[i]);
    }
}
