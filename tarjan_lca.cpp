#include <bits/stdc++.h>
using namespace std;
const int maxn=1e2;
struct edge
{
    int to;
    edge(int to_)
    {
        to=to_;
    }
};
vector<int> qst[maxn];
vector<int> fin;
vector<edge> gpe[maxn];
bool vis[maxn]= {false};
int fa[maxn+10];
void init() {
    for (int i = 1; i <= maxn+10; ++i) {
        fa[i] = i;
    }
}
int get(int x) {
    if (fa[x] == x) {
        return x;
    }
    return fa[x] = get(fa[x]);
}
void merge_f(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
        fa[y] = x;
    }
}
int tarjan(int u)
{
    fa[u]=u;
    vis[u]=true;
    for(int i=0; i<gpe[u].size(); i++)
    {
        int v=gpe[u][i].to;
        if(vis[v]!=true)
        {
            tarjan(v);
            fa[v]=u;
        }
    }
    for(int i=0;i<qst[u].size();i++){
        int v=qst[u][i];
        if(vis[v] == true){
            fin.push_back(get(v));
        }
    }
}
void add_query(int x,int y){
	qst[x].push_back(y);
    qst[y].push_back(x);
}
int main(void){
	int m,n;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		gpe[u].push_back(edge(v));
		gpe[v].push_back(edge(u));
	}
	int q;scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		add_query(x,y);
	}
	tarjan(1);
	for(int i=0;i<q;i++){
		printf("%d\n",fin[i]);
	}
}
