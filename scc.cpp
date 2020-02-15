//luogu p2341
#include <bits/stdc++.h>
using namespace std;
const int maxn=10010;
struct edge{
	int to;
	edge(int to_){
		to=to_;
	}
};
vector<edge> gpe[maxn];
int dfn[maxn],low[maxn],ins[maxn],scc[maxn],size[maxn],cnt=0,sccn=0;
stack<int> s;
void tarjan(int u){
	dfn[u]=low[u]=++cnt;
	s.push(u);
	ins[u]=1;
	for(int i=0;i<gpe[u].size();i++){
		int v=gpe[u][i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(ins[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		ins[u]=0;
		scc[u]=++sccn;
		size[sccn]=1;
		while(s.top()!=u){
			scc[s.top()]=sccn;
			ins[s.top()]=0;
			size[sccn]+=1;
			s.pop();
		}
		s.pop();
	}
	return;
}
int n,m,oud[maxn];
int main(void){
	scanf("%d %d",&n,&m);
	memset(low,0x3f,sizeof(low));
	memset(ins,0,sizeof(ins));
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		gpe[u].push_back(edge(v));
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			cnt=0;
			tarjan(i);
		}
	}
	for(int u=1;u<=n;u++){
		for(int i=0;i<gpe[u].size();i++){
			int v=gpe[u][i].to;
			if(scc[u]!=scc[v]) oud[scc[u]]++;
		}
	}
	int cont=0,ans=0;
	for(int i=1;i<=sccn;i++){
		if(oud[i]==0){
			cont++;
			ans+=size[i];
		}
	}
	if(cont==1){
		printf("%d",ans);
	}else{
		printf("0");
	}
	return 0;
}
