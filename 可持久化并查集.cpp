#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
struct node {
	int l,r,sum;
} t[maxn*40*2];
int n,m,tot,cnt,rootfa[maxn],rootdep[maxn];
void build(int l,int r,int &now) {
	now=++cnt;
	if(l==r) {
		t[now].sum=++tot;
		return;
	}
	int mid=(l+r)/2;
	build(l,mid,t[now].l);
	build(mid+1,r,t[now].r);
}
void modify(int l,int r,int ver,int &now,int pos,int num) {
	t[now=++cnt]=t[ver];
	if(l==r) {
		t[now].sum=num;
		return;
	}
	int mid=(l+r)/2;
	if(pos<=mid) modify(l,mid,t[ver].l,t[now].l,pos,num);
	else modify(mid+1,r,t[ver].r,t[now].r,pos,num);
}
int query(int l,int r,int now,int pos) {
	if(l==r) return t[now].sum;
	int mid=(l+r)/2;
	if(pos<=mid) return query(l,mid,t[now].l,pos);
	else return query(mid+1,r,t[now].r,pos);
}
int find(int ver,int x) {
	int fx=query(1,n,rootfa[ver],x);
	return fx==x?x:find(ver,fx);
}
void merge(int ver,int x,int y) {
	x=find(ver-1,x);
	y=find(ver-1,y);
	if(x==y) {
		rootfa[ver]=rootfa[ver-1];
		rootdep[ver]=rootdep[ver-1];
	}else{
		int depx=query(1,n,rootdep[ver-1],x);
		int depy=query(1,n,rootdep[ver-1],y);
		if(depx<depy){
			modify(1,n,rootfa[ver-1],rootfa[ver],x,y);
			rootdep[ver]=rootdep[ver-1];
		}else if(depx>depy){
			modify(1,n,rootfa[ver-1],rootfa[ver],y,x);
			rootdep[ver]=rootdep[ver-1];
		}else{
			modify(1,n,rootfa[ver-1],rootfa[ver],x,y);
			modify(1,n,rootdep[ver-1],rootdep[ver],y,depy+1);
		}
	}
}
int main(void) {
	scanf("%d %d",&n,&m);
	build(1,n,rootfa[0]);
	for(int ver=1; ver<=m; ver++) {
		int opt,x,y;
		scanf("%d",&opt);
		if(opt==1) {
			scanf("%d %d",&x,&y);
			merge(ver,x,y);
		} else if(opt==2) {
			scanf("%d",&x);
			rootfa[ver]=rootfa[x];
			rootdep[ver]=rootdep[x];
		} else {
			scanf("%d %d",&x,&y);
			rootfa[ver]=rootfa[ver-1];
			rootdep[ver]=rootdep[ver-1];
			int fx=find(ver,x),fy=find(ver,y);
			printf("%d\n",fx==fy?1:0);
		}
	}
}
