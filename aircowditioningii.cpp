#include <iostream>
#include <vector>
using namespace std;
//constraints are very small so can be solved by brute force
//it takes 2^m time for all subsets, then o(n) to sum subsets on array
//it takes at most o(100) to verify the validity of a subset
//so it take 100*2^m time
int main() {
  int n,m;cin>>n>>m;
  int res=1e9;
  vector<vector<int>>cows;
  vector<vector<int>>conditioners;
  for(int i=0;i<n;++i){
    int l,r,c;cin>>l>>r>>c;cows.push_back({l,r,c});
  }
  for(int i=0;i<m;++i){
    int a,b,p,m;cin>>a>>b>>p>>m;conditioners.push_back({a,b,p,m});
  }
  for(int i=0;i<(1<<m);++i){
    vector<int>cool(101,0);
    int c=0;
    bool can=true;
    for(int j=0;j<10;++j){
      if(i&(1<<j)){
        //find the amount an individual stall is cooled fast with prefix sum
        c+=conditioners[j][3];
        cool[conditioners[j][0]]+=conditioners[j][2];
        if(conditioners[j][1]+1<=100){
          cool[conditioners[j][1]+1]+=-conditioners[j][2];
        }
      }
    }
    for(int i=1;i<cool.size();++i){
      cool[i]+=cool[i-1];
    }
    for(int i=0;i<cows.size();++i){
      for(int j=cows[i][0];j<=cows[i][1];++j){
        if(cows[i][2]>cool[j]){
          can=false;
        }
      }
    }
    if(can){
      res=min(res,c);
    }
  }
  cout<<res<<'\n';
}