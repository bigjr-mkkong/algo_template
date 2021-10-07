//p3384 
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2*1e6+10;
int MOD;
vector<int> gpe[maxn];
int a[maxn],n,m,r;
int size[maxn],dep[maxn],f[maxn],hson[maxn];
void dfs1(int u,int fa,int d){
	size[u]=1;
	f[u]=fa;
	dep[u]=d;
	int maxs=-1;
	for(int i=0;i<gpe[u].size();i++){
		int v=gpe[u][i];
		if(v==fa) continue;
		dfs1(v,u,d+1);
		size[u]+=size[v];
		if(size[v]>maxs) hson[u]=v,maxs=size[v];
	}
}
int id[maxn],wt[maxn],top[maxn],cnt=0;
void dfs2(int u,int tc){
	id[u]=++cnt;
	wt[cnt]=a[u];
	top[u]=tc;
	if(!hson[u]) return;
	dfs2(hson[u],tc);
	for(int i=0;i<gpe[u].size();i++){
		int v=gpe[u][i];
		if(v==f[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}
struct node{
	ll sum,tag;
}t[maxn*2];
ll ans=0;
void update(ll pos){
	t[pos].sum=(t[pos<<1].sum+t[pos<<1|1].sum)%MOD;
}
void build(ll l,ll r,ll pos){
	if(l==r){
		t[pos].sum=wt[l];
		return;
	}
	ll mid=(l+r)/2;
	build(l,mid,pos<<1);
	build(mid+1,r,pos<<1|1);
	update(pos);
}
void change(ll pos,ll l,ll r,ll k)
{
    t[pos].tag=(t[pos].tag+k)%MOD;
    t[pos].sum=(t[pos].sum+k*(r-l+1))%MOD;
}
void pushdown(ll l,ll r,ll pos){
	if(!t[pos].tag) return;
	ll mid=(l+r)/2;
	change(pos<<1,l,mid,t[pos].tag);
	change(pos<<1|1,mid+1,r,t[pos].tag);
	t[pos].tag=0;
}
void add(ll tl,ll tr,ll l,ll r,ll v,ll pos){
	if(tl<=l&&tr>=r){
		t[pos].sum+=v*(r-l+1);
		t[pos].tag+=v;
		return;
	}
	if(r<tl||l>tr){
		return;
	}
	ll mid=(l+r)/2;
	pushdown(l,r,pos);
	add(tl,tr,l,mid,v,pos<<1);
	add(tl,tr,mid+1,r,v,pos<<1|1);
	update(pos);
}
void query(ll tl,ll tr,ll l,ll r,ll pos){
	if(tl<=l&&tr>=r){
		ans+=t[pos].sum;
		ans%=MOD;
		return;
	}
	if(r<tl||l>tr){
		return;
	}
	ll mid=(l+r)/2;
	pushdown(l,r,pos);
	query(tl,tr,l,mid,pos<<1);
	query(tl,tr,mid+1,r,pos<<1|1);
	return;
}
int c_ask(int x,int y){
	int ret=0;
	ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		query(id[top[x]],id[x],1,n,1);
		ret=(ret+ans)%MOD;
		ans=0;
		x=f[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	query(id[x],id[y],1,n,1);
	ret=(ret+ans)%MOD;
	ans=0;
	return ret;
}
void c_add(int x,int y,int val){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		add(id[top[x]],id[x],1,n,val,1);
		x=f[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	add(id[x],id[y],1,n,val,1);
}
int main(void){
	scanf("%d %d %d %d",&n,&m,&r,&MOD);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n-1;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		gpe[u].push_back(v);
		gpe[v].push_back(u);
	}
	dfs1(r,r,1);
	dfs2(r,r);
	build(1,n,1);
	while(m--){
		int opt,x,y,v;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d %d %d",&x,&y,&v);
			c_add(x,y,v);
		}else if(opt==2){
			scanf("%d %d",&x,&y);
			printf("%d\n",c_ask(x,y));
		}else if(opt==3){
			scanf("%d %d",&x,&v);
			add(id[x],id[x]+size[x]-1,1,n,v%MOD,1);
		}else{
			scanf("%d",&x);
			query(id[x],id[x]+size[x]-1,1,n,1);
			printf("%d\n",ans);
			ans=0;
		}
	}
}
