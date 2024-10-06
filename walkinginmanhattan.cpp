#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
using namespace std;
#define ll long long
ll b1[200010][20];
ll n,q;
vector<pair<int,int>>vertodd;
vector<pair<int,int>>verteven;
vector<pair<int,int>>horizodd;
vector<pair<int,int>>horizeven;
vector<vector<ll>>quer;
unordered_map<int,int>vid;
unordered_map<int,int>hid;
unordered_map<int,int>idtox;
unordered_map<int,int>idtoy;
void bjump(){//for each road, store nearest road with opposite parity
    for(ll i=0;i<=n+5;++i){
        for(ll j=0;j<20;++j){
            b1[i][j]=-1;
        }
    }
    for(ll i=0;i<vertodd.size()-1;++i){
        vector<pair<int,int>>::iterator k=upper_bound(verteven.begin(),verteven.end(),vertodd[i]);
        b1[vertodd[i].second][0]=(*k).second;
    }
    for(ll i=0;i<verteven.size()-1;++i){
        vector<pair<int,int>>::iterator k=upper_bound(vertodd.begin(),vertodd.end(),verteven[i]);
        b1[verteven[i].second][0]=(*k).second;
    }
    for(ll i=0;i<horizodd.size()-1;++i){
        vector<pair<int,int>>::iterator k=upper_bound(horizeven.begin(),horizeven.end(),horizodd[i]);
        b1[horizodd[i].second][0]=(*k).second;
    }
    for(ll i=0;i<horizeven.size()-1;++i){
        vector<pair<int,int>>::iterator k=upper_bound(horizodd.begin(),horizodd.end(),horizeven[i]);
        b1[horizeven[i].second][0]=(*k).second;
    }
    for(ll j=1;j<20;++j){
        for(ll i=0;i<=n+5;++i){
            if(b1[i][j-1]!=-1){
                b1[i][j]=b1[b1[i][j-1]][j-1];
            }
        }
    }
}
vector<ll> findllersection(int x,int y){//dir=0 means going north, dir=1 means going east
    if(hid.find(y)!=hid.end()&&vid.find(x)!=vid.end()){
        return {x,y,0};
    }
    else if(hid.find(y)!=hid.end()){
        if(x&1){
            vector<pair<int,int>>::iterator k=upper_bound(vertodd.begin(),vertodd.end(),make_pair(x,-1));
            return {(*k).first,y,0};
        }
        else{
            vector<pair<int,int>>::iterator k=upper_bound(verteven.begin(),verteven.end(),make_pair(x,-1));
            return {(*k).first,y,0};
        }
    }
    else{
        if(y&1){
            vector<pair<int,int>>::iterator k=upper_bound(horizeven.begin(),horizeven.end(),make_pair(y,-1));
            return {x,(*k).first,1};
        }
        else{
            vector<pair<int,int>>::iterator k=upper_bound(horizodd.begin(),horizodd.end(),make_pair(y,-1));
            return {x,(*k).first,1};
        }
    }
}
bool checkpair(pair<ll,ll>p,ll x,ll y,ll d){
    if(p.first==-1||p.second==-1){
        return false;
    }
    if(idtox[p.first]-x+idtoy[p.second]-y>d){
        return false;
    }
    return true;
}
pair<ll,ll> ansquer2(ll x,ll y,ll d){
    vector<ll>ller=findllersection(x,y);
    if(abs(ller[1]-y)+abs(ller[0]-x)>=d){
        if(ller[0]==x){
            return {x,y+d};
        }
        else{
            return {x+d,y};
        }
    }
    ll nx,ny;
    d-=(abs(ller[1]-y)+abs(ller[0]-x));nx=ller[0];ny=ller[1];
    ll dir=ller[2];
    pair<ll,ll>res;
    int node2=hid[ny];
    int node1=vid[nx];
    bool can=false;
    for(int i=19;i>=0;i--){
        if(i==0){
            if(dir){
                int tmp1=b1[node1][i];
                if(checkpair(make_pair(tmp1,node2),nx,ny,d)){
                    node1=tmp1;
                    can=true;
                }
            }
            else{
                int tmp2=b1[node2][i];
                if(checkpair(make_pair(node1,tmp2),nx,ny,d)){
                    node2=tmp2;
                    can=true;
                }
            }
        }
        else{
            int tmp1=b1[node1][i-1];
            int tmp2=b1[node2][i-1];
            if(checkpair(make_pair(tmp1,tmp2),nx,ny,d)){
                node1=tmp1;
                node2=tmp2;
            }
        }
    }
    ll dx=idtox[node1];
    ll dy=idtoy[node2];
    if(dir){
        if(can){
            dy+=(d-abs(dx-nx)-abs(dy-ny));
        }
        else{
            dx+=(d-abs(dx-nx)-abs(dy-ny));
        }
    }
    else{
        if(can){
            dx+=(d-abs(dx-nx)-abs(dy-ny));
        }
        else{
            dy+=(d-abs(dx-nx)-abs(dy-ny));
        }
    }
    return {dx,dy};
}
void ansquer1(){
    for(ll i=0;i<q;++i){
        pair<ll,ll>r=ansquer2(quer[i][0],quer[i][1],quer[i][2]);
        cout<<r.first<<' '<<r.second<<'\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>q;
    for(ll i=0;i<n;++i){
        char c;cin>>c;
        if(c=='H'){
            ll k;cin>>k;
            hid[k]=i;
            idtoy[i]=k;
            if(k&1){
                horizodd.push_back({k,i});
            }
            else{
                horizeven.push_back({k,i});
            }
        }
        else{
            ll k;cin>>k;
            vid[k]=i;
            idtox[i]=k;
            if(k&1){
                vertodd.push_back({k,i});
            }
            else{
                verteven.push_back({k,i});
            }
        }
    }
    for(ll i=0;i<q;++i){
        ll x,y,d;cin>>x>>y>>d;
        quer.push_back({x,y,d});
    }
    idtox[n+1]=2e9;
    idtoy[n+2]=2e9;
    vertodd.push_back({2e9,n+1});
    verteven.push_back({2e9,n+1});
    horizodd.push_back({2e9,n+2});
    horizeven.push_back({2e9,n+2});
    sort(horizodd.begin(),horizodd.end());
    sort(horizeven.begin(),horizeven.end());
    sort(vertodd.begin(),vertodd.end());
    sort(verteven.begin(),verteven.end());
    bjump();
    ansquer1();
}