#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 1e2;
int sum=0,cnt=0;
struct edge{
    int value,target;
    edge(int target_,int value_){
        value = value_;
        target = target_;
    }
};
vector<edge> graphic[maxn+10];
int dis[maxn+10];
bool vis[maxn+10];
int spfa(int s,int t,int n){
    for(int i=1;i<=n;i++){
        dis[i] = inf;
    }
    dis[s] = 0;
    memset(vis,false,sizeof(vis));
    deque<int> point;
    vis[s] = true;
    point.push_back(s);
    cnt=1;
    while(point.empty()!=true){
        int u = point.front();
        while(dis[u]*cnt>sum){
            point.pop_back();
            point.push_back(u);
            u=point.front();
        }
        cnt--;
        sum-=dis[u];
        for(int i=0;i<(int)graphic[u].size();i++){
            int to = graphic[u][i].target,value = graphic[u][i].value;
            if(dis[to]>dis[u]+value){
                dis[to] = dis[u]+value;
                if(vis[to] == false){
                   if(dis[to]<dis[point.front()]){
                    point.push_front(to);
                   }else{
                   point.push_back(to);
                   }
                    vis[to] = true;
                    sum+=dis[to];
                    cnt+=1;
                }
            }
        }
        point.pop_front();
    }
    return dis[t];
}
int main(void){
    int m,n;
    scanf("%d %d",&m,&n);
    for(int i=0;i<n;i++){
        int aa,bb,cc;
        scanf("%d %d %d",&aa,&bb,&cc);
        graphic[aa].push_back(edge(bb,cc));
        graphic[bb].push_back(edge(aa,cc));
    }
    int s,t;
    scanf("%d %d",&s,&t);
    printf("%d\n",spfa(s,t,n));
}
