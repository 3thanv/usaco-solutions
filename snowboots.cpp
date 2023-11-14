#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
//analysis here
//it is always possible for a pair of boots to make it from 0 to n-1 if the following condition holds true
//if the length of the longest contiguous subarray of fi>si is less than d then it is possible for the boots to make it
//to find this we answer the queries in decreasing order, and find the longest subarray quickly using dsu
// time complexity is O(na(n)+blog(b)+nlog(n))
struct dsu{
  vector<int>p,s;
  dsu(int n){
    p.resize(n,-1);
    s.resize(n,1);
  }
  int find(int u){
    return p[u]==-1?u:p[u]=find(p[u]);
  }
  bool unite(int u,int v){
    int pu,pv;pu=find(u);pv=find(v);
    if(pu==pv){return false;}
    if(s[pu]>s[pv]){p[pv]=pu;s[pu]+=s[pv];return true;}
    p[pu]=pv;s[pv]+=s[pu];return true;
  }
};
int main(){
  ifstream read("snowboots.in");
  ofstream out("snowboots.out");
  int n,b;read>>n>>b;
  vector<pair<int,int>> arr(n);
  vector<vector<int>> queries;
  vector<int> ans(b);
  vector<int> comp(n,0);
  dsu sets(n);
  for(int i=0;i<n;++i){
    int c;read>>c;arr[i]={c,i};
  }
  for(int i=0;i<b;++i){
    int s,d;read>>s>>d;queries.push_back({s,d,i});
  }
  sort(queries.begin(),queries.end(),greater<vector<int>>());
  sort(arr.begin(),arr.end(),greater<pair<int,int>>());
  int idx=0;
  int longest=0;
  for(int i=0;i<queries.size();++i){
    int s=queries[i][0];int d=queries[i][1];int j=queries[i][2];
    while(arr[idx].first>s){
      int k=arr[idx].second;
      comp[k]=1;
      if(k+1<n&&comp[k+1]==1){
        sets.unite(k,k+1);
      }
      if(k-1>0&&comp[k-1]==1){
        sets.unite(k,k-1);
      }
      longest=max(longest,sets.s[sets.find(k)]);
      ++idx;
    }
    if(longest<d){
      ans[j]=1;
    }
  }
  for(int i=0;i<ans.size();++i){
    out<<ans[i]<<'\n';
  }
}