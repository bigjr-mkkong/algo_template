#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct edge {
	int to, val;
	edge(int to_, int val_) {
		to = to_;
		val = val_;
	}
};
struct node
{
	int dis;
	int pos;
	bool operator <(const node &x)const
	{
		return x.dis < dis;
	}
};
vector<edge> gpe[maxn];
int dis[maxn], ans[maxn], rut[maxn]; //ans用来存储最短路数量,rut用来存储最短路
bool vis[maxn];
void dij(int s) {
	memset(vis, false, sizeof(vis));
	priority_queue<node> q;
	memset(dis,0x7fffffff,sizeof(dis));
	dis[s] = 0;
	q.push((node) {0, s});
	while (!q.empty()) {
		node tmp = q.top();
		q.pop();
		int u = tmp.pos, d = tmp.dis;
		if (vis[u])
			continue;
		vis[u] = 1;
		for (int i = 0; i < gpe[u].size(); i++) {
			int v = gpe[u][i].to, val = gpe[u][i].val;
			/*if(dis[v] ==dis[u]+val){
			    ans[v]+=ans[u];
			}*/
			if (dis[v] > dis[u] + gpe[u][i].val) {
				dis[v] = dis[u] + gpe[u][i].val;
				//rut[u]=v;
				//ans[v]=ans[u];
				if (!vis[v]) {
					q.push((node) {dis[v], v});
				}
			}
		}
	}
}
void show_way(int s) {
	int p=s;
	printf("%d-->",s);
	while (rut[p]!=-1) {
		printf("%d-->",rut[p]);
		p=rut[p];
	}
}
int main() {
	int n,m,s;
	scanf("%d %d %d",&n,&m,&s);
	for (int i=0;i<m;++i) {
		int u, v, d;
		scanf("%d%d%d",&u,&v,&d);
		gpe[u].push_back(edge(v,d));
		//gpe[v].push_back(edge(u,d));
	}
	dij(s);
	for (int i=1;i<=n;i++)
		printf("%d ",dis[i]);
	return 0;
}
