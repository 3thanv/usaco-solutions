#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
using namespace std;
bool can(vector<vector<int>>&grid,int i,int j,int c){
  int q=0;
  if(i-1>=0&&j-1>=0){
    int l=0;
    int r=0;
    if(grid[i][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i-1][j-1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i-1][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j-1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j]==1){
      if(l-1==3||r+1==3){
        return false;
      }
    }
    else {
      if(l+1==3||r-1==3){
        return false;
      }
    }
    if(l==3||r==3){
      ++q;
    }
  }
  if(i+1<grid.size()&&j-1>=0){
    int l=0;
    int r=0;
    if(grid[i][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i+1][j-1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i+1][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j-1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j]==1){
      if(l-1==3||r+1==3){
        return false;
      }
    }
    else {
      if(l+1==3||r-1==3){
        return false;
      }
    }
    if(l==3||r==3){
      ++q;
    }
  }
  if(i+1<grid.size()&&j+1<grid.size()){
    int l=0;
    int r=0;
    if(grid[i][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i+1][j+1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i+1][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j+1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j]==1){
      if(l-1==3||r+1==3){
        return false;
      }
    }
    else {
      if(l+1==3||r-1==3){
        return false;
      }
    }
    if(l==3||r==3){
      ++q;
    }
  }
  if(i-1>=0&&j+1<grid.size()){
    int l=0;
    int r=0;
    if(grid[i][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i-1][j+1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i-1][j]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j+1]==1){
      ++l;
    }
    else {
      ++r;
    }
    if(grid[i][j]==1){
      if(l-1==3||r+1==3){
        return false;
      }
    }
    else {
      if(l+1==3||r-1==3){
        return false;
      }
    }
    if(l==3||r==3){
      ++q;
    }
  }
  if(q==c){
    return true;
  }
  return false;
}
int main (){
  ifstream read("leftout.in");
  ofstream out("leftout.out");
  int n;
  int c=0;
  read>>n;
  vector<string> p;
  vector<vector<int>>grid(n,vector<int>(n,0));
  for(int i=0;i<n;++i){
    string s;read>>s;p.push_back(s);
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      if(p[i][j]=='L'){
        grid[i][j]=1;
      }
    }
  }
  //look for subgrids w/ 3 ones or 3 zeroes
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      if(i+1<n&&j+1<n){
        int l=0;
        int r=0;
        if(grid[i][j]==1){
          ++l;
        }
        else {
          ++r;
        }
        if(grid[i+1][j]==1){
          ++l;
        }
        else {
          ++r;
        }
        if(grid[i][j+1]==1){
          ++l;
        }
        else {
          ++r;
        }
        if(grid[i+1][j+1]==1){
          ++l;
        }
        else {
          ++r;
        }
        if(l==3||r==3){
          ++c;
        }
      }
    }
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      if(can(grid,i,j,c)){
        out<<i+1<<' '<<j+1;
        return 0;;
      }
    }
  }
  out<<-1;
}