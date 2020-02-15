#include <bits/stdc++.h>
using namespace std;
const int maxn=192608;
struct node{
	double x,y;
}point[maxn];
int n,top=2,st[maxn];
inline double dis(int a,int b){
	return sqrt((point[a].x-point[b].x)*(point[a].x-point[b].x)+(point[a].y-point[b].y)*(point[a].y-point[b].y));
}
inline bool judge(int a,int b,int c){
    return (point[a].y-point[b].y)*(point[b].x-point[c].x)>(point[a].x-point[b].x)*(point[b].y-point[c].y);
}
inline bool cmp(node a,node b){
	return (a.y==b.y)?(a.x<b.x):(a.y<b.y);
}
double graham(){
	double ans=0;
	sort(point+1,point+n+1,cmp);
    st[1]=1,st[2]=2;
    for(int i=3;i<=n;i++){
        while(top>1&&!judge(i,st[top],st[top-1]))top--;
        st[++top]=i;
    }
    for(int i=1;i<=top-1;i++){
    	ans+=dis(st[i],st[i+1]);
    }
    top=2;
    memset(st,0,sizeof(st));
    st[1]=1,st[2]=2;
    for(int i=3;i<=n;i++){
        while(top>1&&judge(i,st[top],st[top-1]))top--;
        st[++top]=i;
    }
    for(int i=1;i<=top-1;i++){
    	ans+=dis(st[i],st[i+1]);
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&point[i].x,&point[i].y);
    }
    printf("%.2lf",graham());
    return 0;
}
