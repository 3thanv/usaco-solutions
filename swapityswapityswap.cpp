#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
void findcyc(int i,vector<int>&disp,vector<vector<int>>&cyc,vector<bool>&vis,int j){
  if(!vis[i]){
    vis[i]=true;
    findcyc(disp[i],disp,cyc,vis,j);
    cyc[j].push_back(i);
  }
}
int main() {
  ifstream read("swap.in");
  ofstream out("swap.out");
  int n,m,k;read>>n>>m>>k;
  vector<int> arr(n);
  vector<int> disp(n);
  vector<bool> vis(n,false);
  vector<vector<int>> cyc;
  vector<vector<int>> swaps;
  vector<int> end(n);
  for(int i=0;i<m;++i){
    int p,l;read>>p>>l;swaps.push_back({p,l});
  }
  for(int i=0;i<n;++i){
    arr[i]=i;
  }
  for(int i=0;i<m;++i){
    reverse(arr.begin()+swaps[i][0]-1,arr.begin()+swaps[i][1]);
  }
  for(int i=0;i<arr.size();++i){
    disp[arr[i]]=i;
  }
  //after simulating the swaps one, we know that cow at position i will always then go to position j
  //thus rather than directly simulating the k swaps, we can take advantage of the previous statement
  //we can recursively find all the cycles in o(n) time and then for each cow i in cycle j of length x, find cow at position i+k%x
  int comp=0;
  for(int i=0;i<n;++i){
    if(!vis[i]){
      cyc.push_back({});
      findcyc(i,disp,cyc,vis,comp);
      ++comp;
    }
  }
  for(int i=0;i<comp;++i){
    int p = cyc[i].size();
    for(int j=0;j<cyc[i].size();++j){
      end[cyc[i][j]]=cyc[i][(j+(k%p))%p];
    }
  }
  for(int i:end){
    out<<i+1<<'\n';
  }
}