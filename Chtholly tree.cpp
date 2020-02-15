//Chtholly tree
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
    int l, r;
    mutable ll val;
    node(int l_ = -1, int r_ = -1, ll val_ = 0){
        l = l_, r = r_, val = val_;
    }
    bool operator < (const node &a) const{
        return l < a.l;
    }
};
typedef set<node>::iterator IT;
set<node> st;
IT split(int pos){
    IT it = st.lower_bound(node(pos));
    if (it != st.end() && it->l == pos) return it;
    --it; 
    node tmp = *it; 
    st.erase(it);
    st.insert(node(tmp.l, pos - 1, tmp.val));
    return st.insert(node(pos, tmp.r, tmp.val)).first; 
}

void assign(int l, int r, ll val){
    IT itr = split(r + 1), itl = split(l);
    st.erase(itl, itr);
    st.insert(node(l, r, val));
}

void add(int l, int r, ll val){
    IT itr = split(r + 1), itl = split(l);
    for (IT it = itl; it != itr; ++it){
        it->val += val;
    }
}

ll querySum(int l, int r){
    IT itr = split(r + 1), itl = split(l); 
    ll res = 0;
    for (IT it = itl; it != itr; ++it){
        res += (it->r - it->l + 1) * it->val;
    }
    return res;
}

ll queryKth(int l, int r, int k){
    vector< pair<ll, int> > vec(0);
    IT itr = split(r + 1), itl = split(l);
    for (IT it = itl; it != itr; ++it){
        vec.push_back(make_pair(it->val, it->r - it->l + 1));
    }
    sort(vec.begin(), vec.end());
    for (vector< pair<ll, int> >::iterator it = vec.begin(); it != vec.end(); ++it){
        if ((k -= it->second) <= 0) return it->first;
    }
    return -1; 
}

int main(void){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int aa;
        scanf("%d",&aa);
        st.insert(node(i,i,aa));
    }
    printf("%d",querySum(0,4,3));
}
