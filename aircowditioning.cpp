#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n;cin>>n;
  vector<int>t(n);
  vector<int>p(n);
  int sum=0;
  for(int i=0;i<n;++i){cin>>t[i];}
  for(int i=0;i<n;++i){cin>>p[i];}
  vector<int>arr(n+2);
  for(int i=1;i<=n;++i){
    arr[i]=t[i-1]-p[i-1];
  }
  for(int i=1;i<=n+1;++i){
    sum+=abs(arr[i]-arr[i-1]);
  }
  cout<<sum/2<<'\n';
}