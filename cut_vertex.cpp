#include <bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
vector<int> gpe[maxn];
int dfn[maxn],low[maxn],vpt[maxn],cnt;
int n,m;
void tarjan(int u,int root) {
	dfn[u]=low[u]=++cnt;
	int chd=0;
	for(int i=0;i<gpe[u].size();i++){
		int v=gpe[u][i];
		if(!dfn[v]){
			tarjan(v,root);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]&&u!=root){
				vpt[u]=1;
			}
			if(u==root){
				chd++;
			}
		}
		low[u]=min(low[u],dfn[v]);
	}
	if(chd>=2&&u==root){
		vpt[u]=1;
	}
}
int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int aa,bb;
		scanf("%d%d",&aa,&bb);
		gpe[aa].push_back(bb);
		gpe[bb].push_back(aa);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i,i);
		}
	}
	int num=0;
	for(int i=1;i<=n;i++){
		if(vpt[i]) num++;
	}
	printf("%d\n",num);
	for(int i=1;i<=n;i++){
		if(vpt[i]) printf("%d ",i);
	}
}
