//luogu p3377
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct node{
	int val,l,r,dis,fa;
}ltt[maxn];
int n,m;
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(ltt[x].val>ltt[y].val||(ltt[x].val==ltt[y].val&&x>y)) swap(x,y);
	ltt[x].r=merge(ltt[x].r,y);
	ltt[ltt[x].r].fa=x;
	if(ltt[ltt[x].l].dis<ltt[ltt[x].r].dis) swap(ltt[x].l,ltt[x].r);
	ltt[x].dis=ltt[ltt[x].r].dis+1;
	return x;
}
int find(int x){
	return ltt[x].fa==x?x:ltt[x].fa=find(ltt[x].fa);
}
void pop(int x){
	ltt[x].val=-1;
	ltt[ltt[x].l].fa=ltt[x].l;
	ltt[ltt[x].r].fa=ltt[x].r;
	ltt[x].fa=merge(ltt[x].l,ltt[x].r);
}
int main(void){
	scanf("%d %d",&n,&m);
	ltt[0].dis=-1;
	for(int i=1;i<=n;i++){
		scanf("%d",&ltt[i].val);
		ltt[i].fa=i;
	}
	while(m--){
		int opt,x,y;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d %d",&x,&y);
			if(ltt[x].val==-1||ltt[y].val==-1) continue;
			int x1=find(x),y1=find(y);
			if(x1==y1) continue;
			ltt[x1].fa=ltt[y1].fa=merge(x1,y1);
		}else{
			scanf("%d",&x);
			if(ltt[x].val==-1){
				printf("-1\n");
			}else{
				int x1=find(x);
				printf("%d\n",ltt[x1].val);
				pop(x1);
			}
		}
	}
}
