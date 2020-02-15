#include <bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
struct edge{
    int to;
    edge(int to_){
        to=to_;
    }
};
vector<edge> gpe[maxn];
int cy[maxn],cx[maxn];
bool used[maxn]={false};
bool find(int x){
    for(int i=0;i<gpe[x].size();i++){
        int tar=gpe[x][i].to;
        if(used[tar] == false){
            used[tar]=true;
            if(cy[tar] == 0||find(cy[tar])){
                cy[tar] = x;
                cx[x]=tar;
                return true;
            }
        }
}
return false;
}
int match(int n){
    int all=0;
    for(int i=1;i<=n;i++){
        memset(used,false,sizeof(used));
        if(find(i) == true) all+=1;
    }
    return all;
}
int main(void){
	//就建二分图就完了 
}
