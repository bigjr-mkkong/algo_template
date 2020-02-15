#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2;
const int inf = 19260817;
struct edge{
int target,value;
edge(int target_,int value_){
target = target_;
value = value_;
}
bool operator < (const edge & a) const {
        return a.value < value;
    }
};
struct node{
	int f,now,len;
	bool operator < (const node &rhs) const {//Ð¡¸ù¶Ñ 
        return f > rhs.f;
    }
};
vector<edge> graphic[maxn+10];
vector<edge> gpe[maxn+10];
bool vis[maxn+10],vis2[maxn];
int dis[maxn+10],cnt;
// int ans[maxn];
//int rut[maxn];
priority_queue<edge> que;
int dij(int s,int t,int m){
    for(int  i=1;i<=m;i++){
        dis[i] = inf;
    }
    dis[s] = 0;
    memset(vis,false,sizeof(vis));
    que.push(edge(s,dis[s]));
    while(que.empty()!=true){
        int u = que.top().target;
        que.pop();
        if(vis[u] == true){
            continue;
        }
        vis[u] = true;
        for(int i=0;i<(int)graphic[u].size();i++){
            int v = graphic[u][i].target,val = graphic[u][i].value;
            /*if(dis[v] ==dis[u]+val){
                ans[v]+=ans[u];
            }*/
            if(dis[v]>dis[u]+val){
                dis[v] = dis[u]+val;
                //rut[u]=v;
                // ans[v]=ans[u];
                que.push(edge(v,dis[v]));
            }
        }
    }
    return dis[t];
}
int a_star(int st,int ed,int k){
	priority_queue<node> q; 
	node a;
	a.len=0;
	a.now=st;
	a.f=0+dis[st];
	q.push(a);
	while(q.empty()!=true){
		node u=q.top();
		q.pop();
		if(u.now==ed){
			cnt+=1;
			if(cnt==k) return u.len;
		}
		for(int i=0;i<gpe[u.now].size();i++){
			int v=gpe[u.now][i].target,val=gpe[u.now][i].value;
				node tmp;
				tmp.f=u.len+dis[v]+val;
				tmp.now=v;
				tmp.len=u.len+val;
				q.push(tmp);
		}
	}
}
int main(void){
	int m,n,k;
	scanf("%d %d %d",&m,&n,&k);
	for(int i=0;i<n;i++){
		int aa,bb,cc;
		scanf("%d %d %d",&aa,&bb,&cc);
		graphic[bb].push_back(edge(aa,cc));
		gpe[aa].push_back(edge(bb,cc));
	}
	int st,ed;
	scanf("%d %d",&st,&ed);
	memset(vis2,false,sizeof(vis2));
	dij(ed,st,m); 
	memset(vis,false,sizeof(vis));
	printf("%d",a_star(st,ed,k));
} 
