//luogu p4782
#include <bits/stdc++.h>
using namespace std;
const int maxn=2000050;
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
		int a,va,b,vb;
		scanf("%d %d %d %d",&a,&va,&b,&vb);
    	gpe[a+n*(va&1)].push_back(b+n*(vb^1));
    	gpe[b+n*(vb&1)].push_back(a+n*(va^1));
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(scc[i]==scc[i+n]){
			printf("IMPOSSIBLE");
			return 0;
		}
	}
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++){
		printf("%d ",scc[i]<scc[i+n]);
	}
	return 0;
}
