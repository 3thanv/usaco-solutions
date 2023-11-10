#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n,m;cin>>n>>m;
  vector<int> lay(n);
  vector<vector<vector<int>>> adj(n);
  vector<int>dist(n,INT32_MAX);
  queue<int>q;
  for(int i=0;i<m;++i){
    int c,r,d,s;
    cin>>c>>r>>d>>s;
    c--;d--;
    adj[c].push_back({r,d,s});
  }
  for(int i=0;i<n;++i){
    int c;cin>>c;lay[i]=c;
  }
  lay[0]=0;
  dist[0]=0;
  for(int i=0;i<n;++i){
    sort(adj[i].begin(),adj[i].end());
  }
  vector<int> idx(n,0);
  for(int i=0;i<n;++i){
    idx[i]=adj[i].size()-1;
  }
  q.push(0);
  while(!q.empty()){
    int k=q.front();
    q.pop();
    while(idx[k]>=0&&lay[k]+dist[k]<=adj[k][idx[k]][0]){
      if(min(dist[adj[k][idx[k]][1]],adj[k][idx[k]][2])==adj[k][idx[k]][2]){
        dist[adj[k][idx[k]][1]]=adj[k][idx[k]][2];
        q.push(adj[k][idx[k]][1]);
      }
      --idx[k];
    }
  }
  for(int i=0;i<dist.size();++i){
    dist[i]==INT32_MAX?cout<<-1<<'\n':cout<<dist[i]<<'\n';
  }
  return 0;
}