#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
//h->s
//s->p
//p->h
int main(){
  ifstream read("hps.in");
  ofstream out("hps.out");
  int n,k;read>>n>>k;
  vector<int> moves(n);
  vector<vector<vector<int>>> dp(n,vector<vector<int>>(k+1,vector<int>(3,0)));
  for(int i=0;i<n;++i){
    char c;read>>c;
    if(c=='H'){
      moves[i]=0;
    }
    else if (c=='P'){
      moves[i]=1;
    }
    else {
      moves[i]=2;
    }
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<=k;++j){
      if(i>0){
        dp[i][j][0]=max(dp[i-1][j][0],dp[i][j][0]);
        dp[i][j][1]=max(dp[i-1][j][1],dp[i][j][1]);
        dp[i][j][2]=max(dp[i-1][j][2],dp[i][j][2]);
      }
      if(moves[i]==0){
        dp[i][j][1]++;
      }
      else if (moves[i]==1){
        dp[i][j][2]++;
      }
      else {
        dp[i][j][0]++;
      }
      if(i+1<n&&j+1<=k){
        dp[i+1][j+1][0]+=max(dp[i][j][1],dp[i][j][2]);
        dp[i+1][j+1][1]+=max(dp[i][j][2],dp[i][j][0]);
        dp[i+1][j+1][2]+=max(dp[i][j][0],dp[i][j][1]);
      }
    }
  }
  int res=0;
  for(int i=0;i<=k;++i){
    res=max(dp[n-1][i][0],max(dp[n-1][i][1],dp[n-1][i][2]));
  }
  out<<res<<'\n';
}