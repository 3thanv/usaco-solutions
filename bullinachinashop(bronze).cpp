#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
bool can(vector<int>&bull,vector<vector<int>>&pieces,int p1,int p2){
  int n=bull.size();
  for(int i=-n+1;i<n;++i){
    for(int j=-n+1;j<n;++j){
      for(int k=-n+1;k<n;++k){
        for(int l=-n+1;l<n;++l){
          vector<int> temp(n,0);
          bool can=true;
          for(int q=0;q<n;++q){
            for(int o=0;o<n;++o){
              if(i+q>=n||j+o>=n||i+q<0||j+o<0){
                if(pieces[p1][q]&(1<<o)){
                  can=false;
                }
              }
              else if(pieces[p1][q]&(1<<o)){
                temp[i+q]|=1<<(o+j);
              }
            }
          }
          for(int q=0;q<n;++q){
            for(int o=0;o<n;++o){
              if(k+q>=n||l+o>=n||k+q<0||l+o<0){
                if(pieces[p2][q]&(1<<o)){
                  can=false;
                }
              }
              else if(pieces[p2][q]&(1<<o)){
                temp[k+q]|=1<<(l+o);
              }
            }
          }
          if(can&&temp==bull){
            return true;
          }
        }
      }
    }
  }
  return false;
}
int main() {
  ifstream read("bcs.in");
  ofstream out("bcs.out");
  int n,k;read>>n>>k;
  vector<string>bt(n);
  vector<vector<string>>pt(k);
  vector<int>bull(n);
  vector<vector<int>>pieces(k);
  for(int i=0;i<n;++i){
    string s;read>>s;
    bt[i]=s;
  }
  for(int i=0;i<k;++i){
    for(int j=0;j<n;++j){
      string s;read>>s;
      pt[i].push_back(s);
    }
  }
  for(int i=0;i<n;++i){
    int mask=0;
    for(int j=0;j<n;++j){
      if(bt[i][j]=='#'){
        mask|=(1<<j);
      }
    }
    bull[i]=mask;
  }
  for(int i=0;i<k;++i){
    for(int j=0;j<n;++j){
      int mask=0;
      for(int p=0;p<n;++p){
        if(pt[i][j][p]=='#'){
          mask|=(1<<p);
        }
      }
      pieces[i].push_back(mask);
    }
  }
  for(int i=0;i<k;++i){
    for(int j=i+1;j<k;++j){
      if(can(bull,pieces,i,j)){
        out<<i+1<<' '<<j+1;
        break;
      }
    }
  }
  return 0;
}