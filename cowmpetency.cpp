#include <bits/stdc++.h>
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
using namespace std;
#define ll long long
int t[2000000];
int inf=2e9;
void build(vector<int>&a, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = max(t[v*2],t[v*2+1]);
    }
}
int query(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return -inf;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)),query(v*2+1, tm+1, tr, max(l, tm+1), r));
}
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = max(t[v*2],t[v*2+1]);
    }
}
void solve(){
    int n,q,c;cin>>n>>q>>c;
    vector<int>a(n);
    vector<pair<int,int>>qu;
    set<int>zero;
    bool can=true;
    for(int i=0;i<n;++i){
        cin>>a[i];
        if(a[i]==0){
            zero.insert(i);
        }
    }
    build(a,1,0,n-1);
    vector<int>idx;
    for(int i=0;i<q;++i){
        int b,h;cin>>b>>h;b--;h--;
        qu.push_back({b,h});
        idx.push_back(h);
    }
    sort(qu.begin(),qu.end());
    for(int i=0;i<q;++i){
        if(query(1,0,n-1,qu[i].first+1,qu[i].second-1)>query(1,0,n-1,0,qu[i].first)){
            auto k=zero.upper_bound(qu[i].first);
            if(k==zero.begin()){
                can=false;
            }
            else{
                k--;
                a[*k]=max(1,query(1,0,n-1,qu[i].first+1,qu[i].second-1));
                update(1,0,n-1,(*k),a[(*k)]);
                zero.erase(k);
            }
        }
    }
    sort(idx.begin(),idx.end());
    int mx=2;
    for(int i=0;i<idx.size();++i){
        mx=max(mx,query(1,0,n-1,0,idx[i]-1)+1);
        if(a[idx[i]]==0){
            update(1,0,n-1,idx[i],mx);
            a[idx[i]]=mx;
            zero.erase(idx[i]);
        }
        else if(a[idx[i]]<mx){
            can=false;
        }
    }
    for(int i=0;i<q;++i){
        if(query(1,0,n-1,qu[i].first+1,qu[i].second-1)>query(1,0,n-1,0,qu[i].first)){
            auto k=zero.upper_bound(qu[i].first);
            if(k==zero.begin()){
                can=false;
            }
            else{
                k--;
                a[*k]=max(1,query(1,0,n-1,qu[i].first+1,qu[i].second-1));
                update(1,0,n-1,(*k),a[(*k)]);
                zero.erase(k);
            }
        }
    }
    for(auto p:zero){
        a[p]=1;
    }
    for(int i=0;i<q;++i){
        if(query(1,0,n-1,qu[i].first+1,qu[i].second-1)>query(1,0,n-1,0,qu[i].first)){
            can=false;
        }
        if(a[qu[i].second]<=query(1,0,n-1,0,qu[i].first)){
            can=false;
        }
    }
    for(int i=0;i<n;++i){
        if(a[i]>c){
            can=false;
        }
    }
    if(!can){
        cout<<-1<<'\n';
    }
    else{
        for(int i=0;i<n;++i){
            cout<<a[i];
            if(i!=n-1){
                cout<<' ';
            }
        }
        cout<<'\n';
    }
}
int main() {
	int q;cin>>q;
    while(q--){
        solve();
    }
}
