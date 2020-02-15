#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2;
const int inf = 1e9;
struct edge{
int val,to;
edge(int to_,int val_){
val = val_;
to = to_;
}
};
vector<edge> gpe[maxn];
vector<int> ans;
int indeg[maxn];
queue<int> q;
bool topu(int n){
for(int i=0;i<n;i++){
    if(indeg[i] == 0) q.push(i);
}
while(q.empty()!= true){
    int u = q.front();
    q.pop();
    for(int k=0;k<gpe[u].size();k++){
            int v = gpe[u][k].to;
            indeg[v]-=1;
        if(indeg[v] == 0) q.push(v);
    }
    ans.push_back(u);
}
if(ans.size() == n){
    for(int i=0;i<n;i++){
        printf("%d",ans[i]);
    }
    return true;
    }else{
    return false;
    }
}
int main(void){
int m,n;
scanf("%d %d",&m,&n);
for(int i=0;i<n;i++){
    int aa,bb,cc;
    scanf("%d %d %d",&aa,&bb,&cc);
    gpe[aa].push_back(edge(bb,cc));
    indeg[bb]+=1;
}
printf("%d   false:%d",topu(n),false);
}
