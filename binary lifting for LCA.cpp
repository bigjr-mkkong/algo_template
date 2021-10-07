#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
inline int read()
{
    register int o = 0;
    register char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >='0' && c <='9') o = (o<<3)+(o<<1)+(c&15), c = getchar();
    return o;
}
int ml;
struct edge{
	int to;
	edge(int to_){
		to=to_;
	}
}; 
vector<edge> gpe[maxn];
int f[maxn][64],dep[maxn],n,q,indeg[maxn],root;
bool vis[maxn];
void dfs(int u){
	vis[u]=true;
	for(int i=1;i<=ml;i++) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=0;i<gpe[u].size();i++){
		int v=gpe[u][i].to;
		if(vis[v]) continue;
		f[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v);
	}
}
int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=ml;i>=0;i--){
		if(dep[f[y][i]]>=dep[x]){
			y=f[y][i];
		}
	}
	if(x==y) return x;
	for(int i=ml;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
int main(void){
	memset(vis,false,sizeof(vis));
	n=read();q=read();
	ml=(int)(log(n)/log(2))+1;
	for(int i=1;i<n;i++){
		int aa,bb;
		aa=read();bb=read();
		gpe[aa].push_back(edge(bb));
		gpe[bb].push_back(edge(aa));
		indeg[bb]+=1;
	}
	for(int i=1;i<=n;i++){
		if(indeg[i]==0){
			root=i;
			break;
		}
	}
	dep[root]=1;
	dfs(root);
	int x,y;
	x=read();y=read();
	printf("%d",lca(x,y));
}
