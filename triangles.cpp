#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
long long mod=1e9+7;
long long calculate(long long idxx,long long idxy,long long x,long long y,vector<vector<long long>>&prefixx,vector<vector<long long>>&prefixy){
  long long convpxl=prefixx[y][idxx]-1e4*(idxx+1);
  long long convpyl=prefixy[x][idxy]-1e4*(idxy+1);
  long long convpyu=prefixy[x][prefixy[x].size()-1]-1e4*(prefixy[x].size()-idxy-1)-prefixy[x][idxy];
  long long convpxu=prefixx[y][prefixx[y].size()-1]-1e4*(prefixx[y].size()-idxx-1)-prefixx[y][idxx];
  long long convx=x-1e4;
  long long convy=y-1e4;
  long long arealower=convx*(idxx+1)-convpxl+convpxu-convx*(prefixx[y].size()-idxx-1);
  long long areahigh=convy*(idxy+1)-convpyl+convpyu-convy*(prefixy[x].size()-idxy-1);
  long long res=(arealower*areahigh)%mod;
  return abs(res);
}
int main(){
  ifstream read("triangles.in");
  ofstream out("triangles.out");
  int n;read>>n;
  long long res=0;
  vector<vector<long long>>sumx(2e4+1);
  vector<vector<long long>>sumy(2e4+1);
  vector<vector<long long>>prefixx(2e4+1);
  vector<vector<long long>>prefixy(2e4+1);
  vector<pair<int,int>>coords;
  for(int i=0;i<n;++i){
    int x,y;read>>x>>y;coords.push_back({x+1e4,y+1e4});
    sumx[y+1e4].push_back(x+1e4);
    sumy[x+1e4].push_back(y+1e4);
  }
  for(int i=0;i<2e4+1;++i){
    sort(sumx[i].begin(),sumx[i].end());
    sort(sumy[i].begin(),sumy[i].end());
    prefixx[i]=sumx[i];
    prefixy[i]=sumy[i];
  }
  for(int i=0;i<2e4+1;++i){
    for(int j=1;j<prefixx[i].size();++j){
      prefixx[i][j]+=prefixx[i][j-1];
    }
    for(int j=1;j<prefixy[i].size();++j){
      prefixy[i][j]+=prefixy[i][j-1];
    }
  }
  for(int i=0;i<coords.size();++i){
    long long x=coords[i].first;long long y=coords[i].second;
    long long idxx=lower_bound(sumx[y].begin(),sumx[y].end(),x)-sumx[y].begin();
    long long idxy=lower_bound(sumy[x].begin(),sumy[x].end(),y)-sumy[x].begin();
    res=(calculate(idxx,idxy,x,y,prefixx,prefixy)+res)%mod;
  }
  out<<res<<'\n';
}