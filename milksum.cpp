#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
int main(){
  int n;cin>>n;
  int q;
  long long profit=0;
  vector<long long> arr(n);
  vector<pair<int,int>> p;
  vector<long long> lookup(n);
  vector<long long> indiv(n);
  vector<long long> s(n);
  vector<pair<int,int>> query;
  for(int i=0;i<n;++i){
    cin>>arr[i];
    p.push_back({arr[i],i});
    indiv[i]=arr[i];
  }
  cin>>q;
  for(int i=0;i<q;++i){
    int j,k;cin>>j>>k;j--;query.push_back({j,k});
  }
  sort(p.begin(),p.end());
  for(int i=0;i<n;++i){
    lookup[p[i].second]=i;
  }
  for(int i=0;i<n;++i){
    s[i]=arr[i]=p[i].first;
  }
  for(int i=0;i<n;++i){
    profit+=arr[i]*(i+1);
  }
  for(int i=1;i<n;++i){
    arr[i]+=arr[i-1];
  }
  for(int i=0;i<q;++i){
    long long k=query[i].first;long long j=query[i].second;
    int idx=upper_bound(s.begin(),s.end(),j)-s.begin();
    if(idx<lookup[k]){
      cout<<profit+arr[lookup[k]-1]+s[idx]-arr[idx]-indiv[k]*(lookup[k]+1)+j*(idx+1)<<'\n';
    }
    else if(idx>lookup[k]){
      cout<<profit-arr[idx-1]+arr[lookup[k]]-indiv[k]*(lookup[k]+1)+j*(idx)<<'\n';
    }
    else if (idx==lookup[k]){
      cout<<profit-indiv[k]*(lookup[k]+1)+j*(idx+1)<<'\n';
    }
  }
  return 0;
}
