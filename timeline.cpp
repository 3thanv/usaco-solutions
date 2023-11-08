#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
int main() {
  ifstream read("timeline.in");
  ofstream out("timeline.out");
  int n,m,c;read>>n>>m>>c;
  vector<int> b(n);
  vector<int> dist(n,0);
  vector<int> ind(n,0);
  vector<vector<pair<int,int>>> adj(n);
  queue<int>q;
  for(int i=0;i<n;++i){
    int k;read>>k;b[i]=k;
  }
  for(int i=0;i<c;++i){
    int a,b,x;read>>a>>b>>x;
    a--;b--;
    adj[a].push_back({b,x});
    ++ind[b];
  }
  for(int i=0;i<n;++i){
    if(ind[i]==0){
      q.push(i);
      dist[i]=b[i];
    }
  }
  while(!q.empty()){
    int p=q.front();
    q.pop();
    for(int i=0;i<adj[p].size();++i){
      if(dist[adj[p][i].first]<dist[p]+adj[p][i].second){
        if(dist[p]+adj[p][i].second<b[adj[p][i].first]){
          q.push(adj[p][i].first);
          --ind[adj[p][i].first];
          dist[adj[p][i].first]=b[adj[p][i].first];
        }
        else {
          q.push(adj[p][i].first);
          --ind[adj[p][i].first];
          dist[adj[p][i].first]=dist[p]+adj[p][i].second;
        }
      }
    }
  }
  for(int u:dist){
    out<<u<<'\n';
  }
}