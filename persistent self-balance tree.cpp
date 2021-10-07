#include<cstdio>
#include<iostream>
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int n,root[maxn],cnt;

struct Node {
	int ch[2];
	int rnd,sz,v;
} t[maxn*50];

inline int read() {
	int x=0,t=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*t;
}

inline int copynode(int x) {
	t[++cnt]=t[x];
	return cnt;
}
inline int newnode(int x) {
	t[++cnt].v=x;
	t[cnt].sz=1;
	t[cnt].rnd=rand();
	return cnt;
}
inline void update(int k) {
	if(k)
		t[k].sz=t[t[k].ch[0]].sz+t[t[k].ch[1]].sz+1;
}

inline void split(int now,int k,int &x,int &y) {
	if(!now) {
		x=0;
		y=0;
		return;
	}
	if(t[now].v<=k) {
		x=copynode(now);
		split(t[x].ch[1],k,t[x].ch[1],y);
	} else {
		y=copynode(now);
		split(t[y].ch[0],k,x,t[y].ch[0]);
	}
	update(x);
	update(y);
}
inline int merge(int x,int y) {
	if(!x || !y) return x+y;
	if(t[x].rnd<t[y].rnd) {
		int z=copynode(x);
		t[z].ch[1]=merge(t[z].ch[1],y);
		update(z);
		return z;
	} else {
		int z=copynode(y);
		t[z].ch[0]=merge(x,t[z].ch[0]);
		update(z);
		return z;
	}
}
inline void insert(int now,int k) {
	int x=0,y=0,z=0;
	split(root[now],k,x,y);
	z=newnode(k);
	root[now]=merge(merge(x,z),y);
}

inline void del(int now,int k) {
	int x=0,y=0,z=0;
	split(root[now],k,x,y);
	split(x,k-1,x,z);
	z=merge(t[z].ch[0],t[z].ch[1]);
	root[now]=merge(merge(x,z),y);
}

inline int rnk(int now,int k) {
	int x=0,y=0;
	split(root[now],k-1,x,y);
	return t[x].sz+1;
}

inline int kth(int x,int k) {
	while(1) {
		if(t[t[x].ch[0]].sz+1 ==k) return t[x].v;
		else if(t[t[x].ch[0]].sz>=k) x=t[x].ch[0];
		else {
			k-=(t[t[x].ch[0]].sz+1);
			x=t[x].ch[1];
		}
	}
}
inline int pre(int now,int k) {
	int x=0,y=0,z=0;
	split(root[now],k-1,x,y);
	if(!x) return -2147483647;
	return kth(x,t[x].sz);
}

inline int suf(int now,int k) {
	int x=0,y=0,z=0;
	split(root[now],k,x,y);
	if(!y) return 2147483647;
	return kth(y,1);
}

int main() {
	srand(time(0));
	n=read();
	for(int i=1; i<=n; i++) {
		int ver=read(),op=read();
		root[i]=root[ver];
		if(op==1) insert(i,read());
		else if(op==2) del(i,read());
		else if(op==3) printf("%d\n",rnk(i,read()));
		else if(op==4) printf("%d\n",kth(root[i],read()));
		else if(op==5) printf("%d\n",pre(i,read()));
		else
			printf("%d\n",suf(i,read()));
	}
	return 0;
}
