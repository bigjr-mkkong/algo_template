#include <bits/stdc++.h>
using namespace std;
const int maxn=100010;
const int inf=0x7f;
struct edge{
	int to,flow,rev;
	edge(int to_,int flow_,int rev_){
		to=to_;
		flow=flow_;
		rev=rev_;
	}
};
vector<edge> gpe[maxn];
int dep[maxn];
bool vis[maxn];
bool bfs(int st,int ed) {
    memset(dep, 0, sizeof dep);
    queue<int> q;
    q.push(st);
    dep[st] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i=0;i<gpe[u].size();i++) {
            int v = gpe[u][i].to;
            if( dep[v] || gpe[u][i].flow <= 0) continue;
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }
    return dep[ed];
}
int dfs(int u,int flow,int ed){
    if(u == ed) return flow;
    int add = 0;
    for(int i=0;i<gpe[u].size();i++) {
        int v = gpe[u][i].to;
        if(dep[v] != dep[u] + 1) continue;
        if(!gpe[u][i].flow) continue;
        int tmpadd = dfs(v, min(gpe[u][i].flow, flow - add),ed);
        gpe[u][i].flow -= tmpadd;
        gpe[v][gpe[u][i].rev].flow+=tmpadd;
        add += tmpadd;
    }
    return add;
}
int dinic(int st,int ed){
    int max_flow = 0;
    while (bfs(st,ed)){
        max_flow += dfs(st,inf,ed);
    }
    return max_flow;
}
void addedge(int u,int v,int w){
	gpe[u].push_back(edge(v,w,gpe[v].size()));
	gpe[v].push_back(edge(u,0,gpe[u].size()-1));
}
int main(void){
	int n,m,s,t;
	scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		addedge(u,v,w);
	}
	printf("%d",dinic(s,t));
}
