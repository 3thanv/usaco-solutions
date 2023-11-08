#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void bfs(vector<int>&dist,vector<int>&masks,int c){
  queue<int> q;
  for(int i=0;i<masks.size();++i){
    q.push(masks[i]);
    dist[masks[i]]=0;
  }
  while(!q.empty()){
    int k = q.front();
    q.pop();
    for(int i=0;i<c;++i){
      int p = k;
      if(p&(1<<i)){
        p=(p&(~(1<<i)));
      }
      else {
        p|=(1<<i);
      }
      if(dist[p]>dist[k]+1){
        dist[p]=dist[k]+1;
        q.push(p);
      }
    }
  }
}
int main() {
  int n,c;
  cin>>c>>n;
  vector<string> team;
  vector<int> masks;
  vector<int> invmasks;
  vector<int> dist(1<<c,INT32_MAX);
  for(int i=0;i<n;++i){
    string s;cin>>s;team.push_back(s);
  }
  //n is normal, k is inverted
  for(int i=0;i<n;++i){
    int p=0;int k=0;
    for(int j=0;j<c;++j){
      if(team[i][j]=='G') {
        p|=(1<<j);
      }
      else {
        k|=(1<<j);
      }
    }
    masks.push_back(p);
    invmasks.push_back(k);
  }
  bfs(dist,masks,c);
  for(int i=0;i<n;++i){
    cout<<c-dist[invmasks[i]]<<'\n';
  }
  return 0;
}