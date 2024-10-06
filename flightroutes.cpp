#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;cin>>n;
    int res=0;
    vector<vector<int>>p(n,vector<int>(n));
    vector<vector<int>>adj(n);
    vector<vector<int>>dp(n,vector<int>(n));
    for(int i=0;i<n-1;++i){
        for(int j=i+1;j<n;++j){
            char c;cin>>c;
            p[i][j]=(c=='1');
        }
    }
    for(int s=1;s<=n-1;++s){
        for(int j=0;j+s<n;++j){
            ll sum=0;
            for(auto&l:adj[j+s]){
                sum+=p[j][l]%2;
            }
            if(sum%2!=p[j][j+s]){
                res++;
                adj[j+s].push_back(j);
            }
        }
    }
    cout<<res;
}